#include "drawcircle.h"

DrawCircle::DrawCircle(GraphicsView* view)
	: HandleAdapter(view)
{
	m_centerPoint = osg::Vec3d();
	m_pLayerGroup->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	m_pCircleNode = NULL;
	m_pCircleEdit = NULL;
	
	m_circleStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()
		->fill()->color() = osgEarth::Symbology::Color::Yellow;
	m_circleStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_circleStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
	m_circleStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;
}

DrawCircle::~DrawCircle()
{

}

void DrawCircle::slotPicked(osg::Vec3d pos)
{
	if (m_centerPoint == osg::Vec3d() && pos == osg::Vec3d())
	{
		return;
	}
	else if (m_centerPoint == osg::Vec3d())
	{
		m_centerPoint = pos;
	}

	if (m_pCircleNode == NULL)
	{
		m_pCircleNode = new osgEarth::Annotation::CircleNode(
			m_pMap3D->getMapNode(),
			osgEarth::GeoPoint::GeoPoint(m_pMap3D->getSRS(),
			m_centerPoint, osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			osgEarth::Linear::Linear(50, osgEarth::Units::METERS),
			m_circleStyle,
			osgEarth::Angular::Angular(0.0, osgEarth::Units::DEGREES));

		m_pCircleEdit = new osgEarth::Annotation::CircleNodeEditor(m_pCircleNode);
		m_pLayerGroup->addChild(m_pCircleNode);
		m_pLayerGroup->addChild(m_pCircleEdit);
	}

	m_pCircleNode->setRadius(
		osgEarth::GeoMath::distance(m_centerPoint, pos, m_pMap3D->getSRS()));
}

void DrawCircle::slotMoveing(osg::Vec3d pos)
{
	if (m_pCircleNode != NULL && m_centerPoint != osg::Vec3d())
	{
		m_pCircleNode->setRadius(
			osgEarth::GeoMath::distance(m_centerPoint, pos, m_pMap3D->getSRS()));
	}
}

void DrawCircle::slotRightHandle()
{
	m_centerPoint = osg::Vec3d();
	m_pCircleNode = NULL;
}
