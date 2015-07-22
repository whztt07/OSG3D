#ifndef WEATHER_H
#define WEATHER_H

#include <QtWidgets/QDialog>
#include "graphicsview.h"
#include "ui_weather.h"
#include "rain.h"
#include "snow.h"
#include "fog.h"

class Weather : public QDialog
{
	Q_OBJECT

public:
	Weather(GraphicsView* view, QWidget *parent = nullptr);
	~Weather();

protected:
	virtual void closeEvent(QCloseEvent *e);

private slots:
	void slotLevel(int iLevel);

private:
	Ui::Weather ui;
	GraphicsView* m_pMap3D;
	Rain* m_pRain;
	Snow* m_pSnow;
	Fog* m_pFog;
};

#endif // WEATHER_H
