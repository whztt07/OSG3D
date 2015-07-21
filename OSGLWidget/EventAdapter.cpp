#include "EventAdapter.h"
#include <QPaintEngine>

EventAdapter::EventAdapter(QWidget *parent/* = 0*/)
{
	
}

EventAdapter::~EventAdapter()
{

}

void EventAdapter::setKeyboardModifiers(QInputEvent* event)
{
	int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
	unsigned int mask = 0;
	if (modkey & Qt::ShiftModifier) mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
	if (modkey & Qt::ControlModifier) mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
	if (modkey & Qt::AltModifier) mask |= osgGA::GUIEventAdapter::MODKEY_ALT;

	m_pGraphicsWindow->getEventQueue()->getCurrentEventState()->setModKeyMask(mask);
}

void EventAdapter::keyPressEvent(QKeyEvent* event)
{
	QPoint pos = QCursor::pos();
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->keyPress(
		(osgGA::GUIEventAdapter::KeySymbol)*(event->text().toLatin1().data()));
	QOpenGLWidget::keyPressEvent(event);
}

void EventAdapter::keyReleaseEvent(QKeyEvent* event)
{
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->keyRelease(
		(osgGA::GUIEventAdapter::KeySymbol)*(event->text().toLatin1().data()));

	QOpenGLWidget::keyReleaseEvent(event);
}

void EventAdapter::mousePressEvent(QMouseEvent* event)
{
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
}

void EventAdapter::mouseReleaseEvent(QMouseEvent* event)
{
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);

	QOpenGLWidget::mouseReleaseEvent(event);
}

void EventAdapter::mouseDoubleClickEvent(QMouseEvent* event)
{
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);

	QOpenGLWidget::mouseDoubleClickEvent(event);
}

void EventAdapter::mouseMoveEvent(QMouseEvent* event)
{
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->mouseMotion(event->x(), event->y());
	QOpenGLWidget::mouseMoveEvent(event);
}

void EventAdapter::wheelEvent(QWheelEvent* event)
{
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->mouseScroll(
		event->orientation() == Qt::Vertical ?
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
	QOpenGLWidget::wheelEvent(event);
}

void EventAdapter::resizeGL(int width, int height)
{
	m_pGraphicsWindow->getEventQueue()->windowResize(0, 0, width, height);
	m_pGraphicsWindow->resized(0, 0, width, height);
}
