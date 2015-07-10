/* --------------------------------------------
** 版权: 
** 名称: framehandle
** 作者: louyk 
** 日期: 2015/07/09 
** 描述: 
** ------------------------------------------*/
#ifndef FRAMEHANDLE_H
#define FRAMEHANDLE_H

#include <QtCore/QObject>
#include "MyOSG.h"

class FrameHandle : public QObject, public osgGA::GUIEventHandler
{
	Q_OBJECT

public:
	FrameHandle();
	~FrameHandle();

protected:
	virtual bool handle(const osgGA::GUIEventAdapter& ea,
		osgGA::GUIActionAdapter& aa);

signals:
	// 发送每一帧时视点所在位置
	void signalFrameViewport(const osg::Vec3d& pos);

private:
	
};

#endif // FRAMEHANDLE_H
