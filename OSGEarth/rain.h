/* --------------------------------------------
** 版权: 
** 名称: rain
** 作者: louyk 
** 日期: 2015/07/22 
** 描述: 
** ------------------------------------------*/
#ifndef RAIN_H
#define RAIN_H

#include "graphicsview.h"

class Rain
{
public:
	Rain(GraphicsView* view);
	~Rain();

	// 雨效果，iLevel级别1-10，x:屏幕中心 y:屏幕中心
	void run(int iLevel, double x, double y);

	// 停止雨效果
	void stop();

private:
	// 根据屏幕点求世界坐标
	osg::Vec3d getPostion(double x, double y);

private:
	GraphicsView* m_pMap3D;
	osg::ref_ptr<osg::Group> m_pRainGroup;
};

#endif // RAIN_H
