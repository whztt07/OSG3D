/* --------------------------------------------
** 版权:
** 名称: drawline
** 作者: lyk 
** 日期: 2015/06/15 
** 描述: 
** ------------------------------------------*/
#ifndef DRAWLINE_H
#define DRAWLINE_H

#include "handleadapter.h"

class DrawLine : public HandleAdapter
{
public:
	DrawLine(GraphicsView* view);
	~DrawLine();

protected:
	virtual void slotPicked(osg::Vec3d pos);
	virtual void slotMoveing(osg::Vec3d pos);
	virtual void slotRightHandle();

private:
	osgEarth::Symbology::Style m_lineStyle;
	osgEarth::Features::Feature* m_pFeature;
	osgEarth::Annotation::FeatureNode* m_pFeatureNode;

	osgEarth::Symbology::Style m_stippleLineStyle;
	osgEarth::Features::Feature* m_pStippleFeature;
	osgEarth::Annotation::FeatureNode* m_pStippleFeatureNode;

	std::vector<osg::Vec3d> m_vecPoint;
};

#endif // DRAWLINE_H
