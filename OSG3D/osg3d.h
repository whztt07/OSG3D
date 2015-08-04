#ifndef OSG3D_H
#define OSG3D_H

#include <QtWidgets/QMainWindow>
#include "ui_osg3d.h"
#include "graphicsview.h"
#include "motion.h"

class OSG3D : public QMainWindow
{
	Q_OBJECT

public:
	OSG3D(QWidget *parent = 0);
	~OSG3D();

private slots:
	void slotMotion();

private:
	void init();
	void addAvater();

private:
	Ui::OSG3DClass ui;
	GraphicsView* m_pOSGView;
	Motion* m_pMotion;
};

#endif // OSG3D_H
