/* --------------------------------------------
** 版权: 
** 名称: snow
** 作者: louyk 
** 日期: 2015/07/22 
** 描述: 
** ------------------------------------------*/
#ifndef SNOW_H
#define SNOW_H

#include "graphicsview.h"

class Snow
{
public:
	Snow(GraphicsView* view);
	~Snow();

	// 雪效果，iLevel级别1-10，x:屏幕中心 y:屏幕中心
	void run(int iLevel, double x, double y);

	// 停止雪效果
	void stop();

private:
	// 根据屏幕点求世界坐标
	osg::Vec3d getPostion(double x, double y);

private:
	GraphicsView* m_pMap3D;
	osg::ref_ptr<osg::Group> m_pSnowGroup;
};

#endif // SNOW_H
