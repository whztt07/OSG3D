#include "graphicsview.h"
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QPaintEngine>
#include <QtWidgets/QOpenGLWidget>

GraphicsView::GraphicsView(const QString& strFile, QWidget *parent)
{
	this->setScene(new QGraphicsScene);
	m_pSkyNode = nullptr;
	m_pMapNode = nullptr;
	init();
	setEarthFile(strFile);
}

GraphicsView::~GraphicsView()
{
	release();
}

void GraphicsView::release()
{
	if (m_pSkyNode)
	{
		m_pSkyNode->removeChildren(0, m_pSkyNode->getNumChildren());
	}
	if (m_pRoot)
	{
		m_pRoot->removeChildren(0, m_pRoot->getNumChildren());
		m_pSceneData->removeChildren(0, m_pSceneData->getNumChildren());
	}
	if (m_pMapNode)
	{
		m_pMapNode = nullptr;
		m_pMapSRS = nullptr;
	}
	m_pViewer = nullptr;
	m_pEarthManipulator = nullptr;
}

void GraphicsView::init()
{
	QOpenGLWidget* glViewPort = new QOpenGLWidget;
	glViewPort->setMouseTracking(true);
	glViewPort->setMaximumSize(2000, 2000);
	this->setViewport(glViewPort);
	this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	startTimer(10);
	m_pRoot = new osg::Group;
	m_pRoot->setName("root");

	m_pSceneData = new osg::Group;
	m_pSceneData->setName("SceneData");

	m_pRoot->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
	m_pRoot->addChild(m_pSceneData);
}

void GraphicsView::createSky()
{
	m_pSkyNode = osgEarth::Util::SkyNode::create(m_pMapNode);
	m_pSkyNode->setName("SkyNode");
	// 设置时间;
	osgEarth::DateTime dateTime(2015, 8, 15, 6);
	osgEarth::Util::Ephemeris* ephemeris = new osgEarth::Util::Ephemeris;
	m_pSkyNode->setEphemeris(ephemeris);
	m_pSkyNode->setDateTime(dateTime);
	m_pSkyNode->attach(m_pViewer, 0);
	m_pSkyNode->setLighting(true);
	m_pSkyNode->addChild(m_pMapNode);
	m_pRoot->addChild(m_pSkyNode);
}

void GraphicsView::timerEvent(QTimerEvent *event)
{
	this->scene()->update();
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF& rect)
{
	if (painter->paintEngine()->type() != QPaintEngine::OpenGL2)
	{
		return;
	}

	// Save the painter state
	painter->save();
	painter->beginNativePainting();

	m_pViewer->frame();

	painter->endNativePainting();
	painter->restore();
}

void GraphicsView::setEarthFile(const QString& str)
{
	if (!str.isEmpty())
	{
		release();
		// 初始化地球数据;
		osg::Node* node = osgDB::readNodeFile(str.toLocal8Bit().data());
		if (node)
		{
			m_pMapNode = osgEarth::MapNode::findMapNode(node);
			m_pMapNode->setName("MapNode");
			m_pMapSRS = m_pMapNode->getMapSRS();

			m_pViewer = new osgViewer::Viewer;
			m_pEarthManipulator = new osgEarth::Util::EarthManipulator;
			m_pEarthManipulator->getSettings()->setMinMaxPitch(-90.0, -7.0);
			m_pViewer->setCameraManipulator(m_pEarthManipulator);
			m_pViewer->addEventHandler(new osgViewer::StatsHandler);
			m_pViewer->addEventHandler(new osgGA::StateSetManipulator(m_pViewer->getCamera()->getOrCreateStateSet()));
			m_pViewer->getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(m_pMapNode));
			m_pViewer->getCamera()->setNearFarRatio(0.0000002);
			m_pViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
			m_pViewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
			m_pViewer->setSceneData(m_pRoot);
			m_pGraphicsWindow = dynamic_cast<osgViewer::GraphicsWindow*>(
				m_pViewer->getCamera()->getGraphicsContext());
			m_pEarthManipulator->setViewpoint(osgEarth::Util::Viewpoint(105, 33, 0, 0, -90, 9000000));

			createSky();
		}
	}
}
