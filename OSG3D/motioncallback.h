#ifndef MOTIONCALLBACK_H
#define MOTIONCALLBACK_H

#include "MyOSG.h"

class MotionCallback : public osg::NodeCallback
{
public:
	MotionCallback();
	~MotionCallback();

	template<typename T>
	void setMotion()
	{
		m_pMotion = new T(0.0, 2.0, 1.0, osgAnimation::Motion::LOOP);
	}

protected:
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

private:
	double m_dPreviousTime;
	osg::ref_ptr<osgAnimation::Motion> m_pMotion;
};

#endif // MOTIONCALLBACK_H
