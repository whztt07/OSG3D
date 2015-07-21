#ifndef WIDGET3D_H
#define WIDGET3D_H

#include "EventAdapter.h"
#include "MyOSG.h"

class Widget3D : public EventAdapter, public osgViewer::Viewer
{
	Q_OBJECT

public:
	Widget3D(QWidget *parent = 0);
	~Widget3D();

	osgViewer::Viewer* getOSGViewer(){ return this; }
	osg::Group* getRoot(){ return m_pRoot; }

	void addEarth(const QString& strImage);

protected:
	virtual void paintGL(){ frame(); }
	virtual void timerEvent(QTimerEvent *event){ update(); }

private:
	void init3D();
	osg::ref_ptr<osg::Camera> createCamera(int x, int y, int w, int h);

private:
	osg::ref_ptr<osg::Group> m_pRoot;
};

#endif // WIDGET3D_H
