#include "areaanalysis.h"

AreaAnalysis::AreaAnalysis(GraphicsView* view)
: HandleAdapter(view)
{

}

AreaAnalysis::~AreaAnalysis()
{

}

void AreaAnalysis::slotPicked(osg::Vec3d pos)
{
	if (pos == osg::Vec3d())
	{
		return;
	}

	osgEarth::Util::RadialLineOfSightNode* pRLOSNode = 
		new osgEarth::Util::RadialLineOfSightNode(m_pMap3D->getMapNode());
	pRLOSNode->setCenter(osgEarth::GeoPoint::GeoPoint(
		m_pMap3D->getSRS()->getGeographicSRS(),
		pos.x(), pos.y(), pos.z() + 8, osgEarth::AltitudeMode::ALTMODE_ABSOLUTE));
	pRLOSNode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	pRLOSNode->setRadius(5000);
	pRLOSNode->setBadColor(osg::Vec4(1, 0, 0, 0.3));
	pRLOSNode->setGoodColor(osg::Vec4(0, 1, 0, 0.3));
	pRLOSNode->setNumSpokes(60);
	osgEarth::Util::RadialLineOfSightEditor* pRLOSNodeEidt =
		new osgEarth::Util::RadialLineOfSightEditor(pRLOSNode);
	m_pMap3D->getMapNode()->addChild(pRLOSNode);
	m_pMap3D->getMapNode()->addChild(pRLOSNodeEidt);
}
