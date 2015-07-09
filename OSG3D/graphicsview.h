#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "MyOSG.h"
#include "EventAdapter.h"

class GraphicsView : public EventAdapter
{
	Q_OBJECT

public:
	GraphicsView(QWidget* parent = 0);
	~GraphicsView();

	osgViewer::Viewer* getOSGViewer(){ return m_pViewer; }
	osg::Group* getRoot(){ return m_pSceneData; }

protected:
	virtual void drawBackground(QPainter *painter, const QRectF& rect);
	virtual void timerEvent(QTimerEvent *event);

private:
	void init();

private:
	osg::Group* m_pSceneData;
	osg::StateSet* m_pStateSet;
	osgViewer::Viewer* m_pViewer;
};

#endif // GRAPHICSVIEW_H
