#include "framehandle.h"

FrameHandle::FrameHandle()
	: osgGA::GUIEventHandler()
{

}

FrameHandle::~FrameHandle()
{

}

bool FrameHandle::handle(const osgGA::GUIEventAdapter& ea,
	osgGA::GUIActionAdapter& aa)
{
	auto view = dynamic_cast<osgViewer::Viewer*>(&aa);
	if (view && ea.getEventType() == osgGA::GUIEventAdapter::FRAME)
	{
// 		osgUtil::LineSegmentIntersector::Intersections intersections;
// 		if (view->computeIntersections(ea.getX(), ea.getY(), intersections))
// 		{
// 			auto iter = intersections.begin();
// 		}
		osg::Vec3d eye, center, up;
		view->getCamera()->getViewMatrixAsLookAt(eye, center, up);
		if (center != osg::Vec3d())
		{
			emit signalFrameViewport(center);
		}
	}

	return false;
}
