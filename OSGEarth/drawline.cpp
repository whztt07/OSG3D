#include "drawline.h"

DrawLine::DrawLine(GraphicsView* view)
: HandleAdapter(view)
{
	m_pFeature = NULL;
	m_pFeatureNode = NULL;
	m_pStippleFeature = NULL;
	m_pStippleFeatureNode = NULL;

	m_vecPoint.clear();

	// init style
	m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Yellow;
	m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
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
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->stipple() = 255;
}

DrawLine::~DrawLine()
{

}

void DrawLine::slotPicked(osg::Vec3d pos)
{
	m_vecPoint.push_back(pos);
	if (m_vecPoint.size() <= 1)
	{
		return;
	}

	if (m_pFeatureNode == NULL)
	{
		m_pFeature = new osgEarth::Features::Feature(
			new osgEarth::Annotation::LineString,
			m_pMap3D->getMapNode()->getMapSRS(), m_lineStyle);
		m_pFeatureNode = new osgEarth::Annotation::FeatureNode(
			m_pMap3D->getMapNode(), m_pFeature);

		m_pLayerGroup->addChild(m_pFeatureNode);
	}

	m_pFeature->getGeometry()->clear();
	m_pFeatureNode->setStyle(m_lineStyle);
	for (int i = 0; i < m_vecPoint.size(); ++i)
	{
		m_pFeature->getGeometry()->push_back(m_vecPoint[i]);
	}

	m_pFeatureNode->init();

	if (m_pStippleFeatureNode != NULL)
	{
		m_pStippleFeature->getGeometry()->clear();
	}
}

void DrawLine::slotMoveing(osg::Vec3d pos)
{
	if (m_vecPoint.size() <= 0)
	{
		return;
	}
	if (m_pStippleFeatureNode == NULL)
	{
		m_pStippleFeature = new osgEarth::Features::Feature(
			new osgEarth::Annotation::LineString,
			m_pMap3D->getMapNode()->getMapSRS(), m_lineStyle);
		m_pStippleFeatureNode = new osgEarth::Annotation::FeatureNode(
			m_pMap3D->getMapNode(), m_pStippleFeature);

		m_pLayerGroup->addChild(m_pStippleFeatureNode);
	}

	m_pStippleFeature->getGeometry()->clear();
	m_pStippleFeatureNode->setStyle(m_stippleLineStyle);
	m_pStippleFeature->getGeometry()->push_back(m_vecPoint[m_vecPoint.size() - 1]);
	m_pStippleFeature->getGeometry()->push_back(pos);

	m_pStippleFeatureNode->init();
}

void DrawLine::slotRightHandle()
{
	m_vecPoint.clear();
	if (m_pStippleFeatureNode != NULL)
	{
		m_pStippleFeature->getGeometry()->clear();
	}
}
