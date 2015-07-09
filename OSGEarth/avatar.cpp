/* --------------------------------------------
** 版权: 
** 名称: avatar
** 作者: louyk 
** 日期: 2015/07/03 
** 描述: 
** ------------------------------------------*/
#include "avatar.h"

Avatar::Avatar(GraphicsView* view, QObject *parent)
	: m_pMap3D(view), QObject(parent)
{
	m_pGroup = new osg::Group;
	m_pMap3D->getRoot()->addChild(m_pGroup);

	m_pHandleEvent = new ControlAvatar;

	addAvatar();
	setRotation(90, 0, -90);
	setPostion(104.81443, 26.60379, 1921.2336);
}

Avatar::~Avatar()
{

}

void Avatar::benginHandle()
{
	connect(m_pHandleEvent, SIGNAL(signalUp()), this, SLOT(slotUp()));
	connect(m_pHandleEvent, SIGNAL(signalDown()), this, SLOT(slotDown()));
	connect(m_pHandleEvent, SIGNAL(signalLeft()), this, SLOT(slotLeft()));
	connect(m_pHandleEvent, SIGNAL(signalRight()), this, SLOT(slotRight()));
	m_pMap3D->getOSGViewer()->addEventHandler(m_pHandleEvent);
	if (m_pAvatarNode)
	{
		m_pMap3D->getManipulator()->setTetherNode(m_pAvatarNode);
		m_pMap3D->getManipulator()->setDistance(30.0);
	}
}

void Avatar::endHandle()
{
	disconnect(m_pHandleEvent, SIGNAL(signalUp()), this, SLOT(slotUp()));
	disconnect(m_pHandleEvent, SIGNAL(signalDown()), this, SLOT(slotDown()));
	disconnect(m_pHandleEvent, SIGNAL(signalLeft()), this, SLOT(slotLeft()));
	disconnect(m_pHandleEvent, SIGNAL(signalRight()), this, SLOT(slotRight()));
	m_pMap3D->getOSGViewer()->removeEventHandler(m_pHandleEvent);
	if (m_pAvatarNode)
	{
		m_pMap3D->getManipulator()->setTetherNode(0);
	}
}

void Avatar::slotUp()
{
	osg::Vec3d pos = getCurentPos();
	if (!pos.isNaN())
	{
		setPostion(osg::Vec3d(0, 0, 1));
	}
}

void Avatar::slotDown()
{
	osg::Vec3d pos = getCurentPos();
	if (!pos.isNaN())
	{
		setPostion(osg::Vec3d(0, 0, - 1));
	}
}

void Avatar::slotLeft()
{
	osg::Vec3d pos = getCurentPos();
	if (!pos.isNaN())
	{
		setPostion(osg::Vec3d(1, 0, 0));
	}
}

void Avatar::slotRight()
{
	osg::Vec3d pos = getCurentPos();
	if (!pos.isNaN())
	{
		setPostion(osg::Vec3d(- 1, 0, 0));
	}
}

void Avatar::addAvatar()
{
	osg::Node* pNode = osgDB::readNodeFile(
		QStringLiteral("E:/GreatMap/project/version/Data/Transportation/直升机.ive").toLocal8Bit().data());
	if (!pNode)
	{
		return;
	}
	m_pMat = new osg::MatrixTransform;
	m_pMat->addChild(pNode);

	m_pAvatarNode = new osg::MatrixTransform;
	m_pAvatarNode->addChild(pNode);
	m_pGroup->addChild(m_pAvatarNode);
}

void Avatar::setPostion(double lon, double lat, double alt)
{
	if (m_pAvatarNode)
	{
		osg::Matrix matrix;
		osgEarth::GeoPoint geo = osgEarth::GeoPoint::GeoPoint(
			m_pMap3D->getSRS(), lon, lat, alt, osgEarth::AltitudeMode::ALTMODE_ABSOLUTE);
		geo.createLocalToWorld(matrix);
		m_pAvatarNode->setMatrix(matrix);

		m_pMap3D->getManipulator()->setViewpoint(osgEarth::Util::Viewpoint(
			lon, lat, alt, 0.0, -90.0, 1000, m_pMap3D->getSRS()));
	}
}

void Avatar::setPostion(const osg::Vec3d& worldPos)
{
	if (m_pAvatarNode && !worldPos.isNaN())
	{
		osg::Matrix mat = m_pAvatarNode->getMatrix();
		//mat.preMultTranslate(mat.getTrans() + worldPos);
		mat.setTrans(mat.getTrans() + worldPos);
		m_pAvatarNode->setMatrix(mat);
	}
}

void Avatar::setRotation(double x, double y, double z)
{
	osg::Quat quat = osg::Quat(
	 	osg::inDegrees(x), osg::X_AXIS,
	 	osg::inDegrees(y), osg::Y_AXIS,
	 	osg::inDegrees(z), osg::Z_AXIS);
	osg::Matrix mat = m_pMat->getMatrix();
	mat.preMultRotate(quat);
	m_pMat->setMatrix(mat);
}

osg::Vec3d Avatar::getCurentPos()
{
	osg::Vec3d pos = osg::Vec3d();
	if (m_pAvatarNode)
	{
		osg::Matrix mat = m_pAvatarNode->getMatrix();
		pos = pos * mat;
	}
	return pos;
}
