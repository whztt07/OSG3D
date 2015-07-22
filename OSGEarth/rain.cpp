#include "rain.h"

Rain::Rain(GraphicsView* view)
: m_pMap3D(view)
{
	m_pRainGroup = new osg::Group;
	m_pMap3D->getMapNode()->addChild(m_pRainGroup);
}

Rain::~Rain()
{

}

void Rain::run(int iLevel, double x, double y)
{
	stop();
	osg::Matrixd matrixEffect;
	matrixEffect.makeTranslate(getPostion(x, y));
	
	// 设置粒子位置
	osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
	trans->setMatrix(matrixEffect * osg::Matrixd::scale(100, 100, 100));

	// 创建雨粒子
	osg::ref_ptr<osgParticle::PrecipitationEffect> pe =
		new osgParticle::PrecipitationEffect;
	pe->rain(1.0);
	pe->setUseFarLineSegments(true);
	pe->setParticleSize(iLevel / 10.0);
	// 设置颜色
	pe->setParticleColor(osg::Vec4(1, 1, 1, 1));

	trans->addChild(pe);
	m_pRainGroup->addChild(trans);
}

void Rain::stop()
{
	m_pRainGroup->removeChildren(0, m_pRainGroup->getNumChildren());
}

osg::Vec3d Rain::getPostion(double x, double y)
{
	osg::Vec3d pos = osg::Vec3d(0, 0, 0);
	// 获取当前点
	osgUtil::LineSegmentIntersector::Intersections intersection;
	m_pMap3D->getOSGViewer()->computeIntersections(x, y, intersection);
	auto iter = intersection.begin();
	if (iter != intersection.end())
	{
		pos = iter->getWorldIntersectPoint();
	}
	return pos;
}
