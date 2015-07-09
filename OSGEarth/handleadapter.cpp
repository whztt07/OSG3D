#include "handleadapter.h"

HandleAdapter::HandleAdapter(GraphicsView* view, QObject* parent/* = NULL*/)
	: m_pMap3D(view), QObject(parent)
{
	m_pLayerGroup = new osg::Group;
	m_pMap3D->getRoot()->addChild(m_pLayerGroup);

	m_pEventHandle = new PickHandle(m_pMap3D->getSRS());
}

HandleAdapter::~HandleAdapter()
{

}

void HandleAdapter::benginHandle()
{
	m_pMap3D->getOSGViewer()->addEventHandler(m_pEventHandle);
	connect(m_pEventHandle, SIGNAL(signalPicked(osg::Vec3d)), this, SLOT(slotPicked(osg::Vec3d)));
	connect(m_pEventHandle, SIGNAL(signalMoving(osg::Vec3d)), this, SLOT(slotMoveing(osg::Vec3d)));
	connect(m_pEventHandle, SIGNAL(signalRightPicked()), this, SLOT(slotRightHandle()));
	connect(m_pEventHandle, SIGNAL(signalPickedXYZ(osg::Vec3d)), this, SLOT(slotPickedXYZ(osg::Vec3d)));
	connect(m_pEventHandle, SIGNAL(signalMovingXYZ(osg::Vec3d)), this, SLOT(slotMoveingXYZ(osg::Vec3d)));
}

void HandleAdapter::endHandle()
{
	disconnect(m_pEventHandle, SIGNAL(signalPicked(osg::Vec3d)), this, SLOT(slotPicked(osg::Vec3d)));
	disconnect(m_pEventHandle, SIGNAL(signalMoving(osg::Vec3d)), this, SLOT(slotMoveing(osg::Vec3d)));
	disconnect(m_pEventHandle, SIGNAL(signalRightPicked()), this, SLOT(slotRightHandle()));
	disconnect(m_pEventHandle, SIGNAL(signalPickedXYZ(osg::Vec3d)), this, SLOT(slotPickedXYZ(osg::Vec3d)));
	disconnect(m_pEventHandle, SIGNAL(signalMovingXYZ(osg::Vec3d)), this, SLOT(slotMoveingXYZ(osg::Vec3d)));
	m_pMap3D->getOSGViewer()->removeEventHandler(m_pEventHandle);
}
