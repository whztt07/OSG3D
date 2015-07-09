#include "graphicsview.h"
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QPaintEngine>
#include <QtOpenGL/QGLWidget>

GraphicsView::GraphicsView(QWidget *parent)
{
	this->setScene(new QGraphicsScene);
	init();
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::init()
{
	// test
	QGLWidget* glViewPort = new QGLWidget;
	glViewPort->setMouseTracking(true);
	glViewPort->setMaximumSize(2000, 2000);
	this->setViewport(glViewPort);
	this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	startTimer(0);

	osg::Group* pRoot = new osg::Group;
	pRoot->setName("root");

	m_pSceneData = new osg::Group;
	m_pSceneData->setName("SceneData");

	m_pStateSet = new osg::StateSet;
	m_pStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
	pRoot->setStateSet(m_pStateSet);
	pRoot->addChild(m_pSceneData);

	// 初始化地球数据;
	osg::Node* node = osgDB::readNodeFile("E:/GreatMap/project/GM3ds/dev/trunk/bin/Data/LiuPanShui.earth");
	if (node)
	{
		m_pMapNode = osgEarth::MapNode::findMapNode(node);
		m_pMapNode->setName("MapNode");
		m_pMap = m_pMapNode->getMap();
		m_pMapSRS = m_pMapNode->getMapSRS();
	}

	m_pViewer = new osgViewer::Viewer;
	m_pEarthManipulator = new osgEarth::Util::EarthManipulator;

	m_pEarthManipulator->getSettings()->setMinMaxPitch(-90.0, -7.0);
	m_pViewer->setCameraManipulator(m_pEarthManipulator);
	//m_pViewer->addEventHandler(new osgViewer::StatsHandler);
	//m_pViewer->addEventHandler(new osgGA::StateSetManipulator(m_pViewer->getCamera()->getOrCreateStateSet()));
	m_pViewer->getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(m_pMapNode));
	m_pViewer->getCamera()->setNearFarRatio(0.0000002);
	m_pViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
	m_pViewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
	m_pViewer->setSceneData(pRoot);
	m_pGraphicsWindow = dynamic_cast<osgViewer::GraphicsWindow*>(
		m_pViewer->getCamera()->getGraphicsContext());
	m_pEarthManipulator->setViewpoint(osgEarth::Util::Viewpoint(
		104.81443, 26.60379, 1811.2336, 0.0, -90.0, 5000));

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
	pRoot->addChild(m_pSkyNode);
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
