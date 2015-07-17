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
	GraphicsView(const QString& strFile, QWidget* parent = 0);
	~GraphicsView();

	osgViewer::Viewer* getOSGViewer(){ return m_pViewer; }
	osg::Group* getRoot(){ return m_pSceneData; }
	osgEarth::MapNode* getMapNode(){ return m_pMapNode; }
	const osgEarth::SpatialReference* getSRS(){ return m_pMapSRS; }
	osgEarth::Util::EarthManipulator* getManipulator(){ return m_pEarthManipulator; }
	void setEarthFile(const QString& str);
	void release();

protected:
	virtual void drawBackground(QPainter *painter, const QRectF& rect);
	virtual void timerEvent(QTimerEvent *event);

private:
	void init();
	void createSky();

private:
	osg::ref_ptr<osg::Group> m_pRoot;
	osg::ref_ptr<osgViewer::Viewer> m_pViewer;
	osg::ref_ptr<osg::Group> m_pSceneData;
	osg::ref_ptr<osgEarth::MapNode> m_pMapNode;
	osg::ref_ptr<osgEarth::Util::SkyNode> m_pSkyNode;
	osg::ref_ptr<const osgEarth::SpatialReference> m_pMapSRS;
	osg::ref_ptr<osgEarth::Util::EarthManipulator> m_pEarthManipulator;
};

#endif // GRAPHICSVIEW_H
