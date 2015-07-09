#ifndef AREA_H
#define AREA_H

#include "handleadapter.h"

class Area : public HandleAdapter
{
public:
	Area(GraphicsView* view);
	~Area();

protected:
	virtual void slotPicked(osg::Vec3d pos);
	virtual void slotMoveing(osg::Vec3d pos);
	virtual void slotRightHandle();

private:
	void drawPolygon(osg::Vec3d pos = osg::Vec3d());

private:
	std::vector<osg::Vec3d> m_vecPoints;
	osgEarth::Symbology::Style m_polygonStyle;
	osgEarth::Symbology::Style m_textStyle;
	osgEarth::Annotation::FeatureNode* m_pFeatureNode;
	osgEarth::Annotation::FeatureEditor* m_pPolygonEdit;
	osgEarth::Annotation::PlaceNode* m_pPlaceNode;
};

#endif // AREA_H
