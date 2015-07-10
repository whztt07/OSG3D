#include "radarmap.h"

RadarMap::RadarMap(GraphicsView* view, QObject* parent/* = nullptr*/)
	: m_pOSGViewer(view), QObject(parent)
{
	m_pHUDCamera = nullptr;
	m_pGroup = new osg::Group;
	m_pOSGViewer->getRoot()->addChild(m_pGroup);
	m_pFrameHandle = new FrameHandle;
	m_pGeodeCross = nullptr;
	setGeomtry();
}

RadarMap::~RadarMap()
{

}

void RadarMap::enableMap()
{
	if (m_pHUDCamera == nullptr)
	{
		createMap();
	}
	m_pGroup->addChild(m_pHUDCamera);
	m_pOSGViewer->getOSGViewer()->addEventHandler(m_pFrameHandle);
	connect(m_pFrameHandle, SIGNAL(signalFrameViewport(const osg::Vec3d&)),
		this, SLOT(slotFrameViewport(const osg::Vec3d&)));
}

void RadarMap::disableMap()
{
	if (m_pHUDCamera)
	{
		m_pGroup->removeChild(m_pHUDCamera);
		m_pHUDCamera = nullptr;
		disconnect(m_pFrameHandle, SIGNAL(signalFrameViewport(const osg::Vec3d&)),
			this, SLOT(slotFrameViewport(const osg::Vec3d&)));
		m_pOSGViewer->getOSGViewer()->removeEventHandler(m_pFrameHandle);
	}
}

void RadarMap::slotFrameViewport(const osg::Vec3d& pos)
{
	if (m_pGeodeCross == nullptr)
	{
		m_pGeodeCross = new osg::Geode;
		osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;
		// 使用VBO，每帧实时的修改数据
		pGeometry->setUseVertexBufferObjects(true);
		m_pVertexCross = new osg::Vec3dArray;
		pGeometry->setVertexArray(m_pVertexCross);
		osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array;
		normal->push_back(osg::Vec3(0, 0, 1));
		pGeometry->setNormalArray(normal, osg::Array::BIND_OVERALL);
		osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
		color->push_back(osg::Vec4(0.8, 0.8, 0.8, 1));
		pGeometry->setColorArray(color, osg::Array::BIND_OVERALL);
		pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 4));

		m_pGeodeCross->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		m_pGeodeCross->getOrCreateStateSet()->setAttribute(
			new osg::LineWidth(0.5), osg::StateAttribute::ON);
		m_pGeodeCross->addDrawable(pGeometry);
		m_pHUDCamera->addChild(m_pGeodeCross);
	}
	osg::Vec3d mapPos = getLonLat(pos);
	// 经纬度是-180~180，-90~90，保证算出的是0~360和0~180
	double x = (mapPos.x() + 180.0) * m_iWidth / 360.0;
	double y = (mapPos.y() + 90.0) * m_iHeight / 180.0;

	// 更新缓冲区数据
	m_pVertexCross->clear();
	m_pVertexCross->push_back(osg::Vec3d(x, y - 5, 0));
	m_pVertexCross->push_back(osg::Vec3d(x, y + 5, 0));
	m_pVertexCross->push_back(osg::Vec3d(x - 5, y, 0));
	m_pVertexCross->push_back(osg::Vec3d(x + 5, y, 0));
	m_pVertexCross->dirty();
}

void RadarMap::createMap()
{
	m_pHUDCamera = new osg::Camera;

	// 设置投影矩阵
	m_pHUDCamera->setProjectionMatrixAsOrtho2D(m_iX, m_iWidth, m_iY, m_iHeight);

	// 设置视口矩阵
	m_pHUDCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	m_pHUDCamera->setViewMatrix(osg::Matrix::identity());

	// 只清除深度缓冲区
	m_pHUDCamera->setClearMask(GL_DEPTH_BUFFER_BIT);

	// 设置HUD相机在主相机之后渲染
	m_pHUDCamera->setRenderOrder(osg::Camera::POST_RENDER);

	// HUD相机不获取Event的焦点
	m_pHUDCamera->setAllowEventFocus(false);
	m_pHUDCamera->setViewport(m_iX, m_iY, m_iWidth, m_iHeight);

	// 增加HUD相机的渲染内容，即map
	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;

	// 创建纹理
	osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;
	{
		// 顶点
		osg::ref_ptr<osg::Vec3Array> verArray = new osg::Vec3Array;
		verArray->push_back(osg::Vec3(0, 0, -1));
		verArray->push_back(osg::Vec3(m_iWidth, 0, -1));
		verArray->push_back(osg::Vec3(m_iWidth, m_iHeight, -1));
		verArray->push_back(osg::Vec3(0, m_iHeight, -1));
		pGeometry->setVertexArray(verArray);
		// 纹理坐标
		osg::ref_ptr<osg::Vec2Array> textArray = new osg::Vec2Array;
		textArray->push_back(osg::Vec2(0, 0));
		textArray->push_back(osg::Vec2(1, 0));
		textArray->push_back(osg::Vec2(1, 1));
		textArray->push_back(osg::Vec2(0, 1));
		pGeometry->setTexCoordArray(0, textArray);
		// 法线，指向用户，即y轴
		osg::ref_ptr < osg::Vec3Array> normal = new osg::Vec3Array;
		normal->push_back(osg::Vec3(0, 1, 0));
		pGeometry->setNormalArray(normal);
		pGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
		// 指定绘制方式
		pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
		// 纹理图片
		osg::ref_ptr<osg::Image> image = osgDB::readImageFile(
			"E:/GreatMap/project/GM3ds/dev/trunk/bin/tms/world.png");
		if (image)
		{
			osg::ref_ptr<osg::Texture2D> text2D = new osg::Texture2D;
			text2D->setImage(image);
			text2D->setDataVariance(osg::Object::DYNAMIC);

			pGeometry->getOrCreateStateSet()->setTextureAttributeAndModes(
				0, text2D, osg::StateAttribute::ON);
		}
	}

	// 创建HUD相机的边框
	osg::ref_ptr<osg::Geometry> pGeoBorder = new osg::Geometry;
	{
		// 顶点
		osg::ref_ptr<osg::Vec3Array> verBorder = new osg::Vec3Array;
		verBorder->push_back(osg::Vec3(1.0, 1.0, 0));
		verBorder->push_back(osg::Vec3(m_iWidth - 1.0, 1.0, 0));
		verBorder->push_back(osg::Vec3(m_iWidth - 1.0, m_iHeight - 1.0, 0));
		verBorder->push_back(osg::Vec3(1.0, m_iHeight - 1.0, 0));
		pGeoBorder->setVertexArray(verBorder);
		// 法线
		osg::ref_ptr<osg::Vec3Array> normalBorder = new osg::Vec3Array;
		normalBorder->push_back(osg::Vec3(0.0, 0.0, 1.0));
		pGeoBorder->setNormalArray(normalBorder, osg::Array::BIND_OVERALL);
		// 颜色
		osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
		color->push_back(osg::Vec4(1, 0.8, 0, 1));
		pGeoBorder->setColorArray(color);
		pGeoBorder->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::LINE_LOOP, 0, 4));
		pGeoBorder->getOrCreateStateSet()->setAttribute(new osg::LineWidth(2), osg::StateAttribute::ON);
	}
	pGeode->addDrawable(pGeometry);
	pGeode->addDrawable(pGeoBorder);
	pGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	m_pHUDCamera->addChild(pGeode);
}

osg::Vec3d RadarMap::getLonLat(const osg::Vec3d& worldPos)
{
	osg::Vec3d vecPos = osg::Vec3d();
	if (m_pOSGViewer)
	{
		m_pOSGViewer->getSRS()->getEllipsoid()->convertXYZToLatLongHeight(
			worldPos.x(), worldPos.y(), worldPos.z(), vecPos.y(), vecPos.x(), vecPos.z());
		vecPos.x() = osg::RadiansToDegrees(vecPos.x());
		vecPos.y() = osg::RadiansToDegrees(vecPos.y());
	}
	return vecPos;
}
