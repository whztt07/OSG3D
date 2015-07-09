/* --------------------------------------------
** 版权: 
** 名称: avatar
** 作者: lyk 
** 日期: 2015/06/29 
** 描述: 
** ------------------------------------------*/
#ifndef AVATAR_H
#define AVATAR_H

#include <QtCore/QObject>
#include "MyOSG.h"
#include "MyOSGEarth.h"
#include "graphicsview.h"
#include "controlavatar.h"

class Avatar : public QObject
{
	Q_OBJECT

public:
	Avatar(GraphicsView* view, QObject *parent = NULL);
	~Avatar();

	void benginHandle();
	void endHandle();

private slots:
	void slotUp();
	void slotDown();
	void slotLeft();
	void slotRight();

private:
	void addAvatar();
	void setPostion(double lon, double lat, double alt);
	void setPostion(const osg::Vec3d& worldPos);
	void setRotation(double x, double y, double z);
	osg::Vec3d getCurentPos();
	
private:
	GraphicsView* m_pMap3D;
	ControlAvatar* m_pHandleEvent;
	osg::Group* m_pGroup;
	osg::MatrixTransform* m_pAvatarNode;
	osg::MatrixTransform* m_pMat;
};

#endif // AVATAR_H
