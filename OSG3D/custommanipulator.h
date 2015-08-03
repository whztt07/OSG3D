/* --------------------------------------------
** 版权: (C) 2015
** 名称: custommanipulator
** 作者: louyk
** 日期: 2015/07/31 
** 描述: 自定义osg操作器，实现一个类似CS方式的操作器
** ------------------------------------------*/
#ifndef CUSTOMMANIPULATOR_H
#define CUSTOMMANIPULATOR_H

#include "MyOSG.h"

class CustomManipulator : public osgGA::CameraManipulator
{
public:
	CustomManipulator();
	~CustomManipulator();

	// 设置初始移动速度
	void setSpeed(double speed);

	// 控制碰撞检测开关
	void setCollision(bool b);

	void setCollisionNode(osg::Node* node){ m_pCollisionNode = node; }

protected:
	// 实现关于matrix的运算，控制相机操作
	virtual void setByMatrix(const osg::Matrixd& mat);
	virtual osg::Matrixd getMatrix() const;

	// 实现关于inverse matrix的运算，控制相机操作
	virtual void setByInverseMatrix(const osg::Matrixd& mat);
	virtual osg::Matrixd getInverseMatrix() const;

	// handle, 事件处理
	virtual bool handle(const osgGA::GUIEventAdapter& ea,
		osgGA::GUIActionAdapter& aa);

private:
	// 改变位置，delta为增量，非绝对量
	void changePosition(osg::Vec3d& delta);

private:
	double m_dSpeed;                           // 移动速度
	double m_dSpeedDelta;                      // 速度增减量
	float m_fAngle;                            // 旋转增量
	osg::Vec3d m_vecPosition;                  // 位置
	osg::Vec3d m_vecRotation;                  // 旋转

	bool m_bIsCollision;                       // 碰撞检测开关
	osg::ref_ptr<osg::Node> m_pCollisionNode;  // 碰撞检测节点

	bool m_bIsLeftPressed;                     // 记录左键是否按下
	int m_iPressedX;                           // 按下左键时X位置
	int m_iPressedY;                           // 按下左键时Y位置
};

#endif	// CUSTOMMANIPULATOR_H
