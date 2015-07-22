#ifndef OSGEARTH_H
#define OSGEARTH_H

#include <QtWidgets/QMainWindow>
#include "ui_OSGEarth.h"
#include "drawline.h"
#include "MyOSG.h"
#include "graphicsview.h"
#include "drawpolygon.h"
#include "drawcircle.h"
#include "distance.h"
#include "area.h"
#include "height.h"
#include "water.h"
#include "lineanalysis.h"
#include "areaanalysis.h"
#include "avatar.h"
#include "radarmap.h"
#include "goto.h"
#include "weather.h"

class OSGEarth : public QMainWindow
{
	Q_OBJECT

public:
	OSGEarth(QWidget *parent = 0);
	~OSGEarth();

private slots:
	void slotLine();
	void slotPolygon();
	void slotCircle();
	void slotDistance();
	void slotArea();
	void slotHeight();
	void slotWater();
	void slotLineIntervisibility();
	void slotAreaIntervisibility();
	void slotAvatar();
	void slotOverlay();
	void slotGride();
	void slotRadarMap();
	void slotSwitchMap();
	void slotGoto();

	void slotSun();
	void slotMoon();

	void slotWeather();

private:
	Ui::OSGEarthClass ui;
	DrawLine* m_pDrawLine;
	GraphicsView* m_pViewer;
	DrawPolygon* m_pPolygon;
	DrawCircle* m_pCircle;
	Distance* m_pDistance;
	Area* m_pArea;
	Height* m_pHeight;
	Water* m_pWater;
	LineAnalysis* m_pLineAns;
	AreaAnalysis* m_pAreaAns;
	Avatar* m_pAvatarNode;
	osg::ref_ptr<osgEarth::Annotation::ImageOverlay> m_pImage;
	osg::ref_ptr<osgEarth::Util::GeodeticGraticule> m_pGraticule;
	RadarMap* m_pRadarMap;
	GoTo* m_pGoto;
	Weather* m_pWeather;
};

#endif // OSGEARTH_H
