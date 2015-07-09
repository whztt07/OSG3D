#ifndef HEIGHT_H
#define HEIGHT_H

#include "handleadapter.h"

class Height : public HandleAdapter
{
public:
	Height(GraphicsView* view);
	~Height();

protected:
	virtual void slotPicked(osg::Vec3d pos);
	virtual void slotMoveing(osg::Vec3d pos);
	virtual void slotRightHandle();

private:
	void init();
	void drawHeight(osg::Vec3d pos = osg::Vec3d());

private:
	osg::Vec3d m_firstPoint;
	osgEarth::Symbology::Style m_lineStyle;
	osgEarth::Symbology::Style m_textStyle;
	osgEarth::Features::Feature* m_pFeature;
	osgEarth::Annotation::FeatureNode* m_pFeatureNode;

	osgEarth::Symbology::Style m_stippleLineStyle;
	osgEarth::Features::Feature* m_pStippleFeature;
	osgEarth::Annotation::FeatureNode* m_pStippleFeatureNode;
	osgEarth::Annotation::PlaceNode* m_pPlaceNode;
};

#endif // HEIGHT_H
