#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QtWidgets/QGraphicsView>
#include <QtGui/QInputEvent>
#include "MyOSG.h"
#include "MyOSGEarth.h"
#include "EventAdapter.h"

class GraphicsView : public EventAdapter
{
	Q_OBJECT

public:
	GraphicsView(QWidget* parent = 0);
	~GraphicsView();

	osgViewer::Viewer* getOSGViewer(){ return m_pViewer; }
	osg::Group* getRoot(){ return m_pSceneData; }
	osgEarth::MapNode* getMapNode(){ return m_pMapNode; }
	const osgEarth::SpatialReference* getSRS(){ return m_pMapSRS; }
	osgEarth::Util::EarthManipulator* getManipulator(){ return m_pEarthManipulator; }

protected:
	virtual void drawBackground(QPainter *painter, const QRectF& rect);
	virtual void timerEvent(QTimerEvent *event);

private:
	void init();

private:
	osgEarth::Map* m_pMap;
	osg::Group* m_pSceneData;
	osg::StateSet* m_pStateSet;
	osgViewer::Viewer* m_pViewer;
	osgEarth::MapNode* m_pMapNode;
	osgEarth::Util::SkyNode* m_pSkyNode;
	const osgEarth::SpatialReference* m_pMapSRS;
	osgEarth::Util::EarthManipulator* m_pEarthManipulator;
};

#endif // GRAPHICSVIEW_H
