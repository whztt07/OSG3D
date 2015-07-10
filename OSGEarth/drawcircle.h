#ifndef DRAWCIRCLE_H
#define DRAWCIRCLE_H

#include "handleadapter.h"

class DrawCircle : public HandleAdapter
{
public:
	DrawCircle(GraphicsView* view);
	~DrawCircle();

protected:
	virtual void slotPicked(osg::Vec3d pos);
	virtual void slotMoveing(osg::Vec3d pos);
	virtual void slotRightHandle();

private:
	osg::Vec3d m_centerPoint;

	osgEarth::Symbology::Style m_circleStyle;
	osgEarth::Annotation::CircleNode* m_pCircleNode;
	osgEarth::Annotation::CircleNodeEditor* m_pCircleEdit;
};

#endif // DRAWCIRCLE_H
