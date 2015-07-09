/* --------------------------------------------
** 版权: 
** 名称: handleadapter
** 作者: louyk 
** 日期: 2015/07/09 
** 描述: 
** ------------------------------------------*/
#ifndef HANDLEADAPTER_H
#define HANDLEADAPTER_H

#include <QtCore/QObject>
#include "pickhandle.h"
#include "graphicsview.h"

class HandleAdapter : public QObject
{
	Q_OBJECT

public:
	HandleAdapter(GraphicsView* view, QObject* parent = NULL);
	~HandleAdapter();

	void benginHandle();
	void endHandle();

private slots:
	virtual void slotPicked(osg::Vec3d pos){}
	virtual void slotMoveing(osg::Vec3d pos){}

	virtual void slotPickedXYZ(osg::Vec3d pos){}
	virtual void slotMoveingXYZ(osg::Vec3d pos){}

	virtual void slotRightHandle(){}

public:
	GraphicsView* m_pMap3D;
	osg::Group* m_pLayerGroup;
	PickHandle* m_pEventHandle;
};

#endif // HANDLEADAPTER_H
