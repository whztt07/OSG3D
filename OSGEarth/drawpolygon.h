#ifndef DRAWPOLYGON_H
#define DRAWPOLYGON_H

#include "handleadapter.h"

class DrawPolygon : public HandleAdapter
{
public:
	DrawPolygon(GraphicsView* view);
	~DrawPolygon();

protected:
	virtual void slotPicked(osg::Vec3d pos);
	virtual void slotMoveing(osg::Vec3d pos);
	virtual void slotRightHandle();

private:
	std::vector<osg::Vec3d> m_vecPoints;

	osgEarth::Symbology::Style m_polygonStyle;
	osgEarth::Annotation::FeatureNode* m_pFeatureNode;
	osgEarth::Annotation::FeatureEditor* m_pPolygonEdit;

	osgEarth::Symbology::Style m_stippleLineStyle;
	osgEarth::Annotation::FeatureNode* m_pStippleFeatureNode;
};

#endif // DRAWPOLYGON_H
