#ifndef RADARMAP_H
#define RADARMAP_H

#include "framehandle.h"
#include "graphicsview.h"

class RadarMap : public QObject
{
	Q_OBJECT

public:
	RadarMap(GraphicsView* view, QObject *parent = nullptr);
	~RadarMap();

	void setGeomtry(int x = 20, int y = 20, int width = 320, int height = 180)
	{
		m_iX = x; m_iY = y; m_iWidth = width; m_iHeight = height;
	}

	void enableMap();
	void disableMap();

private slots:
	void slotFrameViewport(const osg::Vec3d& pos);

private:
	void createMap();

private:
	// 显示的区域
	int m_iX;
	int m_iY;
	int m_iWidth;
	int m_iHeight;

	// HUD相机
	osg::ref_ptr<osg::Camera> m_pHUDCamera;
	GraphicsView* m_pOSGViewer;
};

#endif // RADARMAP_H
