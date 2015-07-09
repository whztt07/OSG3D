#ifndef EVENTADAPTER_H
#define EVENTADAPTER_H
#include <QtGui/QInputEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtWidgets/QGraphicsView>
#include "MyOSG.h"

class EventAdapter : public QGraphicsView
{
public:
	EventAdapter();
	~EventAdapter();

protected:
	virtual bool viewportEvent(QEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);
	virtual void resizeEvent(QResizeEvent *event);
	virtual void moveEvent(QMoveEvent* event);
	virtual void timerEvent(QTimerEvent *event);

private:
	void setKeyboardModifiers(QInputEvent* event);

protected:
	osgViewer::GraphicsWindow* m_pGraphicsWindow;
};

#endif // EVENTADAPTER_H
