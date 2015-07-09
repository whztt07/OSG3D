#include "osg3d.h"

OSG3D::OSG3D(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pMotion = nullptr;

	init();

	connect(ui.actionMotion, SIGNAL(triggered()), this, SLOT(slotMotion()));
}

OSG3D::~OSG3D()
{

}

void OSG3D::init()
{
	m_pOSGView = new GraphicsView;
	this->setCentralWidget(m_pOSGView);
}

void OSG3D::slotMotion()
{
	if (ui.actionMotion->isChecked())
	{
		if (m_pMotion == nullptr)
		{
			m_pMotion = new Motion(m_pOSGView);
			m_pMotion->show();
		}
	}
	else
	{
		delete m_pMotion;
		m_pMotion = nullptr;
	}
}
