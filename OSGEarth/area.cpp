#include "area.h"
#include "calcmath.h"

Area::Area(GraphicsView* view)
: HandleAdapter(view)
{
	m_vecPoints.clear();
	m_pFeatureNode = NULL;
	m_pPolygonEdit = NULL;
	m_pPlaceNode = NULL;

	m_polygonStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()
		->fill()->color() = osgEarth::Symbology::Color::Yellow;
	m_polygonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_polygonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
	m_polygonStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;

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

Area::~Area()
{

}

void Area::slotPicked(osg::Vec3d pos)
{
	m_vecPoints.push_back(pos);
	if (m_vecPoints.size() <= 2)
	{
		return;
	}

	drawPolygon();
}

void Area::slotMoveing(osg::Vec3d pos)
{
	if (m_vecPoints.size() < 2)
	{
		return;
	}
	drawPolygon(pos);
}

void Area::slotRightHandle()
{
	endHandle();
	drawPolygon();
	m_pFeatureNode = nullptr;
}

void Area::drawPolygon(osg::Vec3d pos/* = osg::Vec3d()*/)
{
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

		m_pPlaceNode = new osgEarth::Annotation::PlaceNode(
			m_pMap3D->getMapNode(), osgEarth::GeoPoint::GeoPoint(), "", m_textStyle);
		m_pPlaceNode->setDynamic(true);

		m_pLayerGroup->addChild(m_pFeatureNode);
		m_pLayerGroup->addChild(m_pPlaceNode);
	}
	std::vector<osg::Vec3d> vecPoints = m_vecPoints;
	osgEarth::Symbology::Geometry* pGeometry = m_pFeatureNode->getFeature()->getGeometry();
	pGeometry->clear();
	m_pFeatureNode->setStyle(m_polygonStyle);
	for (auto& n : m_vecPoints)
	{
		pGeometry->push_back(n);
	}
	if (pos != osg::Vec3d())
	{
		pGeometry->push_back(pos);
		vecPoints.push_back(pos);
	}

	CalcMath math;
	QString str = QStringLiteral("Ãæ»ý£º%1 ©O").arg(
		QString::number(math.calcArea(vecPoints),
		'g', 9));
	m_pPlaceNode->setText(str.toStdWString());
	m_pPlaceNode->setPosition(osgEarth::GeoPoint::GeoPoint(m_pMap3D->getSRS(), pos));

	m_pFeatureNode->init();
}
