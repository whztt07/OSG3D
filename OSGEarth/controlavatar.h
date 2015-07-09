/* --------------------------------------------
** 版权: 
** 名称: controlavatar
** 作者: lyk 
** 日期: 2015/06/29 
** 描述: 
** ------------------------------------------*/
#ifndef CONTROLAVATAR_H
#define CONTROLAVATAR_H

#include <QtCore/QObject>
#include "MyOSG.h"

class ControlAvatar : public QObject, public osgGA::GUIEventHandler
{
	Q_OBJECT

public:
	ControlAvatar(QObject *parent = NULL);
	~ControlAvatar();

protected:
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

signals:
	void signalUp();
	void signalDown();
	void signalLeft();
	void signalRight();

private:
	
};

#endif // CONTROLAVATAR_H
