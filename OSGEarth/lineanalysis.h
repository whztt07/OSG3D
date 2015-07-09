/* --------------------------------------------
** 版权: 
** 名称: lineanalysis
** 作者: lyk 
** 日期: 2015/06/25 
** 描述: 
** ------------------------------------------*/
#ifndef LINEANALYSIS_H
#define LINEANALYSIS_H

#include "handleadapter.h"

class LineAnalysis : public HandleAdapter
{
public:
	LineAnalysis(GraphicsView* view);
	~LineAnalysis();

protected:
	virtual void slotPicked(osg::Vec3d pos);
	virtual void slotMoveing(osg::Vec3d pos);
	virtual void slotRightHandle();

private:
	void analysis(osg::Vec3d pos);
	osg::Vec3d getWorldCoord(osg::Vec3d pos);

private:
	osgEarth::Annotation::FeatureNode* m_pLine;
	osg::Vec3d m_firstPoint;
	osgEarth::Annotation::PlaceNode* m_pPlaceNode;
	osgEarth::Symbology::Style m_lineStyle;
	osgEarth::Symbology::Style m_textStyle;
};

#endif // LINEANALYSIS_H
