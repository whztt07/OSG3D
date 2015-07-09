#ifndef DISTANCE_H
#define DISTANCE_H

#include "handleadapter.h"

class Distance : public HandleAdapter
{
public:
	Distance(GraphicsView* view);
	~Distance();

protected:
	virtual void slotPicked(osg::Vec3d pos);
	virtual void slotMoveing(osg::Vec3d pos);

private:
	double calcDistance(osg::Vec3d pos);

private:
	std::vector<osg::Vec3d> m_vectPoints;

	osgEarth::Symbology::Style m_lineStyle;
	osgEarth::Symbology::Style m_textStyle;
	osgEarth::Annotation::FeatureNode* m_pFeatureNode;
	osgEarth::Annotation::PlaceNode* m_pPlaceNode;
};

#endif // DISTANCE_H
