#include "widget3d.h"

Widget3D::Widget3D(QWidget *parent)
	: EventAdapter(parent)
{
	init3D();
	this->setMouseTracking(true);
}

Widget3D::~Widget3D()
{

}

void Widget3D::init3D()
{
	m_pRoot = new osg::Group;
	m_pRoot->setName("Root");

	this->setCamera(createCamera(0, 0, width(), height()));
	this->addEventHandler(new osgViewer::StatsHandler);
	this->addEventHandler(new osgViewer::ThreadingHandler());
	this->addEventHandler(new osgViewer::HelpHandler);
	this->addEventHandler(new osgGA::StateSetManipulator(this->getCamera()->getOrCreateStateSet()));
	this->setThreadingModel(osgViewer::Viewer::SingleThreaded);
	
	m_pRoot->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
	m_pRoot->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
	this->setSceneData(m_pRoot);

	// test
#if 0
	osg::ref_ptr<osgGA::TrackballManipulator> pManipulator =
		new osgGA::TrackballManipulator;
	this->setCameraManipulator(pManipulator);

	osg::ref_ptr<osg::Node> pNode = osgDB::readNodeFile("E:/GreatMap/project/GM3ds/dev/trunk/ext/osg3.2.1_x86/Data/cow.osg");
	osg::ref_ptr<osg::MatrixTransform> matTrans = new osg::MatrixTransform;
	matTrans->addChild(pNode);
	matTrans->setMatrix(osg::Matrix::translate(osg::Vec3d(0, -15, 0)));
	//m_pRoot->addChild(matTrans);

	osg::Vec3d center;
	osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(
		new osg::Cylinder(osg::Vec3d(0, -5000, 0), 5, 3000));

	shape->setColor(osg::Vec4d(1, 0, 1, 1));
	shape->setSupportsDisplayList(false);

	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
	pGeode->addDrawable(shape);
	m_pRoot->addChild(pGeode);
#else
	addEarth("E:\\GreatMap\\project\\GM3ds\\dev\\trunk\\ext\\osg3.2.1_x86\\Data/Images/land_shallow_topo_2048.jpg");
#endif
	startTimer(10);
}

osg::ref_ptr<osg::Camera> Widget3D::createCamera(int x, int y, int w, int h)
{
	m_pGraphicsWindow = new osgViewer::GraphicsWindowEmbedded(x, y, w, h);
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowDecoration = true;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;

	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(m_pGraphicsWindow);
	camera->setClearColor(osg::Vec4(0.3, 0.3, 0.6, 0.8));
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->setProjectionMatrixAsPerspective(
		30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0f, 10000.0f);

	return camera.release();
}

void Widget3D::addEarth(const QString& strImage)
{
	this->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
	this->getCamera()->setNearFarRatio(0.00001f);

	osg::TessellationHints* hints = new osg::TessellationHints;
	hints->setDetailRatio(5.0f);

	osg::ShapeDrawable* sd = new osg::ShapeDrawable(
		new osg::Sphere(osg::Vec3(0.0, 0.0, 0.0), osg::WGS_84_RADIUS_POLAR), hints);

	osg::Geode* geode = new osg::Geode;
	geode->addDrawable(sd);

	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0,
		new osg::Texture2D(osgDB::readImageFile(strImage.toStdString())));

	osg::CoordinateSystemNode* csn = new osg::CoordinateSystemNode;
	csn->setEllipsoidModel(new osg::EllipsoidModel());
	csn->addChild(geode);

	m_pRoot->addChild(csn);

	this->setCameraManipulator(new osgGA::TerrainManipulator);
}
