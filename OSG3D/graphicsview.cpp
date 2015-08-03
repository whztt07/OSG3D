#include "graphicsview.h"
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QPaintEngine>
#include <QtOpenGL/QGLWidget>
#include "fountain.h"

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

	m_pViewer = new osgViewer::Viewer;
	//m_pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
	//m_pViewer->addEventHandler(new osgViewer::StatsHandler);
	//m_pViewer->addEventHandler(new osgGA::StateSetManipulator(m_pViewer->getCamera()->getOrCreateStateSet()));
	//m_pViewer->getCamera()->setNearFarRatio(0.0000002);
	m_pViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
	m_pViewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
	m_pViewer->setSceneData(pRoot);
	m_pGraphicsWindow = dynamic_cast<osgViewer::GraphicsWindow*>(
		m_pViewer->getCamera()->getGraphicsContext());
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
