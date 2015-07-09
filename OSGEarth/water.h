/* --------------------------------------------
** 版权: 
** 名称: water
** 作者: lyk 
** 日期: 2015/06/25 
** 描述: 
** ------------------------------------------*/
#ifndef WATER_H
#define WATER_H

#include "handleadapter.h"

class Water : public HandleAdapter
{
public:
	Water(GraphicsView* view);
	~Water();

protected:
	virtual void slotPickedXYZ(osg::Vec3d pos);
	virtual void slotMoveingXYZ(osg::Vec3d pos);
	virtual void slotRightHandle();

private:
	void drawWater(osg::Vec3d pos = osg::Vec3d());
	osg::Texture2D* creatText2D(const QString& strFile);
	void initShader();

private:
	osg::ref_ptr<osg::Vec3dArray> m_vecPoints;
	osg::Geode* m_pWater;
	char* m_waterFrag;
	char* m_waterVert;
};

#endif // WATER_H
