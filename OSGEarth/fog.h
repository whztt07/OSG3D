/* --------------------------------------------
** 版权: 
** 名称: fog
** 作者: louyk 
** 日期: 2015/07/22 
** 描述: 
** ------------------------------------------*/
#ifndef FOG_H
#define FOG_H

#include "graphicsview.h"

class Fog
{
public:
	Fog(GraphicsView* view);
	~Fog();

	// 雾效果，iLevel级别1-10
	void run(int iLevel);

	// 结束雾效果
	void stop();

private:
	GraphicsView* m_pMap3D;
	osg::ref_ptr<osg::Fog> m_pFog;
	osg::ref_ptr<osgEarth::Util::FogEffect> m_pFogEffect;
};

#endif // FOG_H
