#include "drawpolygon.h"

DrawPolygon::DrawPolygon(GraphicsView* view)
	: HandleAdapter(view)
{
	m_vecPoints.clear();
	m_pFeatureNode = NULL;
	m_pStippleFeatureNode = NULL;
	m_pPolygonEdit = NULL;

	m_polygonStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()
		->fill()->color() = osgEarth::Symbology::Color::Yellow;
	m_polygonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_polygonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
	m_polygonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;

	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Red;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->stipple() = 255;
}

DrawPolygon::~DrawPolygon()
{

}

void DrawPolygon::slotPicked(osg::Vec3d pos)
{
	m_vecPoints.push_back(pos);
	if (m_vecPoints.size() <= 2)
	{
		return;
	}

	if (m_pPolygonEdit != NULL)
	{
		m_pPolygonEdit->removeChildren(0, m_pPolygonEdit->getNumChildren());
		m_pPolygonEdit = NULL;
	}
	if (m_pFeatureNode == NULL)
	{
		osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(
			new osgEarth::Symbology::Polygon,
			m_pMap3D->getSRS(), m_polygonStyle);

		m_pFeatureNode = new osgEarth::Annotation::FeatureNode(
			m_pMap3D->getMapNode(), pFeature);

		m_pLayerGroup->addChild(m_pFeatureNode);
	}

	osgEarth::Symbology::Geometry* pGeometry = m_pFeatureNode->getFeature()->getGeometry();
	pGeometry->clear();
	m_pFeatureNode->setStyle(m_polygonStyle);
	for (auto& n : m_vecPoints)
	{
		pGeometry->push_back(n);
	}

	m_pFeatureNode->init();
	if (m_pStippleFeatureNode != NULL)
	{
		m_pStippleFeatureNode->getFeature()->getGeometry()->clear();
	}
	if (m_pPolygonEdit == NULL)
	{
		m_pPolygonEdit = new osgEarth::Annotation::FeatureEditor(m_pFeatureNode);
		m_pLayerGroup->addChild(m_pPolygonEdit);
	}
}

void DrawPolygon::slotMoveing(osg::Vec3d pos)
{
	if (m_vecPoints.size() < 2)
	{
		return;
	}
	if (m_pStippleFeatureNode == NULL)
	{
		osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(
			new osgEarth::Annotation::LineString,
			m_pMap3D->getSRS(), m_stippleLineStyle);
		m_pStippleFeatureNode = new osgEarth::Annotation::FeatureNode(
			m_pMap3D->getMapNode(), pFeature);

		m_pLayerGroup->addChild(m_pStippleFeatureNode);
	}

	osgEarth::Symbology::Geometry* pGeometry = m_pStippleFeatureNode->getFeature()->getGeometry();
	pGeometry->clear();
	m_pStippleFeatureNode->setStyle(m_stippleLineStyle);
	pGeometry->push_back(m_vecPoints[0]);
	pGeometry->push_back(pos);
	pGeometry->push_back(m_vecPoints[m_vecPoints.size() - 1]);

	m_pStippleFeatureNode->init();
}

void DrawPolygon::slotRightHandle()
{
	m_vecPoints.clear();
	if (m_pStippleFeatureNode != NULL)
	{
		m_pStippleFeatureNode->getFeature()->getGeometry()->clear();
	}
	m_pFeatureNode = nullptr;
}
