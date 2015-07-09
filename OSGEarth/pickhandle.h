/* --------------------------------------------
** 版权: 
** 名称: pickhandle
** 作者: lyk 
** 日期: 2015/06/15 
** 描述: 
** ------------------------------------------*/
#ifndef PICKHANDLE_H
#define PICKHANDLE_H

#include <QtCore/QObject>
#include "MyOSG.h"
#include "MyOSGEarth.h"

class PickHandle : public QObject, public osgGA::GUIEventHandler
{
	Q_OBJECT
public:
	PickHandle(const osgEarth::SpatialReference* srs);
	~PickHandle();

protected:
	virtual bool handle(const osgGA::GUIEventAdapter& ea,
		osgGA::GUIActionAdapter& aa);

private:
	osg::Vec3d getPos(const osgGA::GUIEventAdapter& ea,
		osgGA::GUIActionAdapter& aa, osg::Vec3d& pos);

signals:
	// 经纬度信息
	void signalPicked(osg::Vec3d pos);
	void signalMoving(osg::Vec3d pos);

	// 世界坐标信息
	void signalPickedXYZ(osg::Vec3d pos);
	void signalMovingXYZ(osg::Vec3d pos);

	void signalRightPicked();

private:
	osg::Vec3d m_vecPostion;
	const osg::EllipsoidModel* m_pEllipsoid;
};

#endif // PICKHANDLE_H
