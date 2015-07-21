/* --------------------------------------------
** 版权: 
** 名称: goto
** 作者: louyk 
** 日期: 2015/07/19 
** 描述: 
** ------------------------------------------*/
#ifndef GOTO_H
#define GOTO_H

#include <QtWidgets/QDialog>
#include "graphicsview.h"
#include "ui_goto.h"
#include "MyOSGEarth.h"

class GoTo : public QDialog
{
	Q_OBJECT

public:
	GoTo(GraphicsView* view, QWidget *parent = nullptr);
	~GoTo();

private slots:
	void slotGoTo();

private:
	Ui::GoTo ui;
	GraphicsView* m_pMap3D;
};

#endif // GOTO_H
