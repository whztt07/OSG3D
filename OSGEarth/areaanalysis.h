#ifndef AREAANALYSIS_H
#define AREAANALYSIS_H

#include "handleadapter.h"

class AreaAnalysis : public HandleAdapter
{
public:
	AreaAnalysis(GraphicsView* view);
	~AreaAnalysis();

protected:
	virtual void slotPicked(osg::Vec3d pos);

private:

};

#endif // AREAANALYSIS_H
