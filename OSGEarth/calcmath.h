/* --------------------------------------------
** 版权: 
** 名称: math
** 作者: lyk 
** 日期: 2015/06/23 
** 描述: 
** ------------------------------------------*/
#ifndef MATH_H
#define MATH_H

#include "MyOSG.h"

class CalcMath
{
public:
	CalcMath();
	~CalcMath();

	// 球面面积计算公式
	double calcArea(std::vector<osg::Vec3d> points);

private:
	
};

#endif // MATH_H
