#include "height.h"

Height::Height(GraphicsView* view)
: HandleAdapter(view)
{
	m_pFeatureNode = NULL;
	m_pStippleFeature = NULL;
	m_pStippleFeatureNode = NULL;
	m_pPlaceNode = NULL;
	m_firstPoint = osg::Vec3d();

	init();
}

Height::~Height()
{

}

void Height::slotPicked(osg::Vec3d pos)
{
	if (m_firstPoint == osg::Vec3d())
	{
		m_firstPoint = pos;
	}
}

void Height::slotMoveing(osg::Vec3d pos)
{
	drawHeight(pos);
}

void Height::slotRightHandle()
{
	endHandle();
	m_pFeatureNode = nullptr;
}

void Height::init()
{
	// init style
	m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Yellow;
	m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_ABSOLUTE;
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
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_ABSOLUTE;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->stipple() = 255;

	m_textStyle.getOrCreate<osgEarth::Symbology::TextSymbol>()->alignment()
		= osgEarth::Symbology::TextSymbol::ALIGN_LEFT_TOP;
	m_textStyle.getOrCreate<osgEarth::Symbology::TextSymbol>()->encoding()
		= osgEarth::Symbology::TextSymbol::ENCODING_UTF8;
	m_textStyle.getOrCreate<osgEarth::Symbology::TextSymbol>()->declutter()
		= true;
	m_textStyle.getOrCreate<osgEarth::Symbology::TextSymbol>()->halo()
		= osgEarth::Symbology::Color::White;
	m_textStyle.getOrCreate<osgEarth::Symbology::TextSymbol>()->haloOffset() = 0.05;
	m_textStyle.getOrCreate<osgEarth::Symbology::TextSymbol>()->fill()->color()
		= osg::Vec4(1, 0.5, 0, 1);
	m_textStyle.getOrCreate<osgEarth::Symbology::RenderSymbol>()->lighting() = false;
	m_textStyle.getOrCreate<osgEarth::Symbology::TextSymbol>()->font() = "simhei.ttf";
	m_textStyle.getOrCreate<osgEarth::Symbology::TextSymbol>()->size() = 25.0;
}

void Height::drawHeight(osg::Vec3d pos /*= osg::Vec3d()*/)
{
	if (m_firstPoint == osg::Vec3d())
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

		m_pStippleFeature = new osgEarth::Features::Feature(
			new osgEarth::Annotation::LineString,
			m_pMap3D->getMapNode()->getMapSRS(), m_stippleLineStyle);
		m_pStippleFeatureNode = new osgEarth::Annotation::FeatureNode(
			m_pMap3D->getMapNode(), m_pStippleFeature);

		m_pPlaceNode = new osgEarth::Annotation::PlaceNode(
			m_pMap3D->getMapNode(), osgEarth::GeoPoint::GeoPoint(), "", m_textStyle);

		m_pLayerGroup->addChild(m_pStippleFeatureNode);
		m_pLayerGroup->addChild(m_pFeatureNode);
		m_pLayerGroup->addChild(m_pPlaceNode);
	}

	osg::Vec3d heightPos = osg::Vec3d(m_firstPoint.x(), m_firstPoint.y(), pos.z());

	m_pFeature->getGeometry()->clear();
	m_pFeatureNode->setStyle(m_lineStyle);
	m_pFeature->getGeometry()->push_back(m_firstPoint);
	m_pFeature->getGeometry()->push_back(heightPos);
	m_pFeatureNode->init();

	m_pStippleFeature->getGeometry()->clear();
	m_pStippleFeatureNode->setStyle(m_stippleLineStyle);
	m_pStippleFeature->getGeometry()->push_back(m_firstPoint);
	m_pStippleFeature->getGeometry()->push_back(pos);
	m_pStippleFeature->getGeometry()->push_back(heightPos);
	m_pStippleFeatureNode->init();

	QString str = QStringLiteral("¸ß¶È£º%1 Ã×").arg(heightPos.z() - m_firstPoint.z());
	m_pPlaceNode->setText(str.toStdWString());
	m_pPlaceNode->setPosition(
		osgEarth::GeoPoint::GeoPoint(
		m_pMap3D->getSRS(), heightPos.x(), heightPos.y()));
}
