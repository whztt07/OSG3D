/* --------------------------------------------
** 版权: 
** 名称: fountain
** 作者: louyk 
** 日期: 2015/07/24 
** 描述: 
** ------------------------------------------*/
#ifndef FOUNTAIN_H
#define FOUNTAIN_H

#include "MyOSG.h"

class Fountain
{
public:
	Fountain();
	~Fountain();

	// 设置要创建喷泉的具体参数
	void setFountainParas(double num = 1000, double size = 0.2, double speed = 100);

	// 创建喷泉，参数为喷泉的位置信息及父节点
	osg::ref_ptr<osg::Node> createFountain(osg::Vec3d postion, osg::Group* parent);

private:
	osg::Vec3d m_vecPos;             // 位置
	double m_dParticlesNum;          // 粒子数目
	double m_dParticlesSize;         // 粒子大小
	double m_dParticlesSpeed;        // 粒子速度
};

#endif // FOUNTAIN_H
