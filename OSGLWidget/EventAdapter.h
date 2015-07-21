#ifndef EVENTADAPTER_H
#define EVENTADAPTER_H
#include <QtGui/QInputEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtWidgets/QOpenGLWidget>
#include "MyOSG.h"

class EventAdapter : public QOpenGLWidget
{
public:
	EventAdapter(QWidget *parent = 0);
	~EventAdapter();

protected:
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);
	virtual void resizeGL(int width, int height);

private:
	void setKeyboardModifiers(QInputEvent* event);

protected:
	osgViewer::GraphicsWindow* m_pGraphicsWindow;
};

#endif // EVENTADAPTER_H
