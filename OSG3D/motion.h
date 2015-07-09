#ifndef MOTION_H
#define MOTION_H

#include <QWidget>
#include "ui_motion.h"
#include "motioncallback.h"
#include "MyOSG.h"
#include "graphicsview.h"

class Motion : public QWidget
{
	Q_OBJECT

public:
	Motion(GraphicsView* view, QWidget* parent = 0);
	~Motion();

private slots:
	void slotRadioChanged();

private:
	// 添加一个操作球
	void addSphere();

private:
	Ui::Motion ui;
	GraphicsView* m_pOSGView;
	MotionCallback* m_pMotion;
};

#endif // MOTION_H
