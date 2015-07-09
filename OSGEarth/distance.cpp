#include "distance.h"

Distance::Distance(GraphicsView* view)
	: HandleAdapter(view)
{
	m_pFeatureNode = NULL;
	m_pPlaceNode = NULL;
	m_vectPoints.clear();

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

Distance::~Distance()
{

}

void Distance::slotPicked(osg::Vec3d pos)
{
	m_vectPoints.push_back(pos);

	if (m_pFeatureNode == NULL)
	{
		osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(
			new osgEarth::Annotation::LineString,
			m_pMap3D->getMapNode()->getMapSRS(), m_lineStyle);
		m_pFeatureNode = new osgEarth::Annotation::FeatureNode(
			m_pMap3D->getMapNode(), pFeature);

		m_pPlaceNode = new osgEarth::Annotation::PlaceNode(
			m_pMap3D->getMapNode(), osgEarth::GeoPoint::GeoPoint(), "", m_textStyle);
		m_pPlaceNode->setDynamic(true);

		m_pLayerGroup->addChild(m_pFeatureNode);
		m_pLayerGroup->addChild(m_pPlaceNode);
	}

	osgEarth::Symbology::Geometry* pGeometry = m_pFeatureNode->getFeature()->getGeometry();
	pGeometry->clear();
	m_pFeatureNode->setStyle(m_lineStyle);
	for (unsigned int i = 0; i < m_vectPoints.size(); ++i)
	{
		pGeometry->push_back(m_vectPoints[i]);
	}

	m_pFeatureNode->init();
}

void Distance::slotMoveing(osg::Vec3d pos)
{
	if (m_pFeatureNode)
	{
		osgEarth::Symbology::Geometry* pGeometry = m_pFeatureNode->getFeature()->getGeometry();
		pGeometry->clear();
		m_pFeatureNode->setStyle(m_lineStyle);
		pGeometry->push_back(m_vectPoints.at(m_vectPoints.size() - 1));
		pGeometry->push_back(pos);

		m_pFeatureNode->init();

		QString str = QStringLiteral("³¤¶È£º%1 Ã×").arg(
			QString::number(calcDistance(pos),
			'g', 9));
		m_pPlaceNode->setText(str.toStdWString());
		m_pPlaceNode->setPosition(osgEarth::GeoPoint::GeoPoint(m_pMap3D->getSRS(), pos));
	}
}

double Distance::calcDistance(osg::Vec3d pos)
{
	double dDis = 0.0;
	if (m_pFeatureNode)
	{
		for (unsigned int i = 1; i < m_vectPoints.size(); ++i)
		{
			dDis += osgEarth::GeoMath::distance(
				m_vectPoints.at(i - 1), m_vectPoints.at(i), m_pMap3D->getSRS());
		}
		dDis += osgEarth::GeoMath::distance(
			m_vectPoints.at(m_vectPoints.size() - 1), pos, m_pMap3D->getSRS());
	}
	return dDis;
}
