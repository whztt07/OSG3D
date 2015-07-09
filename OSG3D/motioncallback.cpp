#include "motioncallback.h"

MotionCallback::MotionCallback()
	: osg::NodeCallback()
{
	m_dPreviousTime = 0.0;
}

MotionCallback::~MotionCallback()
{

}

void MotionCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	if (!m_pMotion.valid())
	{
		return;
	}

	//osg::ref_ptr<osg::MatrixTransform> mat = dynamic_cast<osg::MatrixTransform*>(node);
	auto mat = dynamic_cast<osg::MatrixTransform*>(node);
	if (!mat)
	{
		return;
	}

	double dCurr = nv->getFrameStamp()->getSimulationTime();
	if (m_dPreviousTime == 0.0)
	{
		m_dPreviousTime = dCurr;
	}

	m_pMotion->update(dCurr - m_dPreviousTime);

	m_dPreviousTime = dCurr;

	mat->setMatrix(osg::Matrix::translate(
		osg::Vec3d(100.0, 0.0, 0.0) * m_pMotion->getValue()));
}
