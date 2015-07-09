#include "lineanalysis.h"

LineAnalysis::LineAnalysis(GraphicsView* view)
: HandleAdapter(view)
{
	m_pLine = NULL;
	m_firstPoint = osg::Vec3d();

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

LineAnalysis::~LineAnalysis()
{
}

void LineAnalysis::slotPicked(osg::Vec3d pos)
{
	m_firstPoint = pos;
}

void LineAnalysis::slotMoveing(osg::Vec3d pos)
{
	analysis(pos);
}

void LineAnalysis::slotRightHandle()
{
	endHandle();
}

void LineAnalysis::analysis(osg::Vec3d pos)
{
	if (m_firstPoint == osg::Vec3d())
	{
		return;
	}

	if (m_pLine == NULL)
	{
		osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(
			new osgEarth::Features::LineString,
			m_pMap3D->getSRS(), m_lineStyle);

		m_pLine = new osgEarth::Annotation::FeatureNode(m_pMap3D->getMapNode(), pFeature);

		m_pPlaceNode = new osgEarth::Annotation::PlaceNode(
			m_pMap3D->getMapNode(), osgEarth::GeoPoint::GeoPoint(), "", m_textStyle);

		m_pLayerGroup->addChild(m_pLine);
		m_pLayerGroup->addChild(m_pPlaceNode);
	}

	osgEarth::Symbology::Geometry* pGeom = m_pLine->getFeature()->getGeometry();
	pGeom->clear();
	m_pLine->setStyle(m_lineStyle);
	pGeom->push_back(m_firstPoint);
	pGeom->push_back(pos);
	m_pLine->init();

	// 碰撞检测
	QString str;
	osgUtil::IntersectVisitor iv;
	osg::ref_ptr<osg::LineSegment> line = new osg::LineSegment(
		getWorldCoord(osg::Vec3d(m_firstPoint.x(), m_firstPoint.y(), m_firstPoint.z() + 2)),
		getWorldCoord(osg::Vec3d(pos.x(), pos.y(), pos.z() + 2)));
	iv.addLineSegment(line);
	m_pMap3D->getMapNode()->getTerrain()->accept(iv);
	if (iv.hits())
	{
		str = QStringLiteral("两点不可见");
	}
	else
	{
		str = QStringLiteral("两点可见");
	}
	m_pPlaceNode->setText(str.toStdWString());
	m_pPlaceNode->setPosition(
		osgEarth::GeoPoint::GeoPoint(m_pMap3D->getSRS(), pos.x(), pos.y()));
}

osg::Vec3d LineAnalysis::getWorldCoord(osg::Vec3d pos)
{
	osg::Vec3d world;
	m_pMap3D->getSRS()->getEllipsoid()->convertLatLongHeightToXYZ(
		osg::DegreesToRadians(pos.y()),
		osg::DegreesToRadians(pos.x()),
		pos.z(), world.x(), world.y(), world.z());

	return world;
}
