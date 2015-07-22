#include "snow.h"

Snow::Snow(GraphicsView* view)
: m_pMap3D(view)
{
	m_pSnowGroup = new osg::Group;
	m_pMap3D->getMapNode()->addChild(m_pSnowGroup);
}

Snow::~Snow()
{

}

void Snow::run(int iLevel, double x, double y)
{
	stop();
	osg::Matrixd mat;
	mat.makeTranslate(getPostion(x, y));

	// 设置粒子位置
	osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
	trans->setMatrix(mat * osg::Matrixd::scale(10, 10, 10));

	osg::ref_ptr<osgParticle::PrecipitationEffect> pe = new osgParticle::PrecipitationEffect;
	pe->snow(1.0);
	pe->setParticleSize(iLevel / 10.0);
	// 设置颜色
	pe->setParticleColor(osg::Vec4(1, 1, 1, 1));
	
	trans->addChild(pe);
	m_pSnowGroup->addChild(trans);
}

void Snow::stop()
{
	m_pSnowGroup->removeChildren(0, m_pSnowGroup->getNumChildren());
}

osg::Vec3d Snow::getPostion(double x, double y)
{
	osg::Vec3d pos = osg::Vec3d(0, 0, 0);
	osgUtil::LineSegmentIntersector::Intersections intersections;
	m_pMap3D->getOSGViewer()->computeIntersections(x, y, intersections);
	auto iter = intersections.begin();
	if (iter != intersections.end())
	{
		pos = iter->getWorldIntersectPoint();
	}

	return pos;
}
