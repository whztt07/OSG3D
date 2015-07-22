#include "weather.h"

Weather::Weather(GraphicsView* view, QWidget *parent)
: m_pMap3D(view), QDialog(parent)
{
	ui.setupUi(this);
	m_pRain = nullptr;
	m_pSnow = nullptr;
	m_pFog = nullptr;

	m_pRain = new Rain(m_pMap3D);
	m_pSnow = new Snow(m_pMap3D);
	m_pFog = new Fog(m_pMap3D);

	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slotLevel(int)));
}

Weather::~Weather()
{

}

void Weather::slotLevel(int iLevel)
{
	if (ui.radioButtonRain->isChecked())
	{
		m_pFog->stop();
		m_pSnow->stop();
		m_pRain->stop();

		m_pRain->run(iLevel, width() / 2, height() / 2);
	}
	else if (ui.radioButtonSnow->isChecked())
	{
		m_pFog->stop();
		m_pSnow->stop();
		m_pRain->stop();

		m_pSnow->run(iLevel, width() / 2, height() / 2);
	}
	else if (ui.radioButtonFog->isChecked())
	{
		m_pFog->stop();
		m_pSnow->stop();
		m_pRain->stop();

		m_pFog->run(iLevel);
	}
}

void Weather::closeEvent(QCloseEvent *e)
{
	m_pFog->stop();
	m_pSnow->stop();
	m_pRain->stop();

	close();
}
