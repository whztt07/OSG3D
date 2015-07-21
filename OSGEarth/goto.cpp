#include "goto.h"

GoTo::GoTo(GraphicsView* view, QWidget *parent)
	: m_pMap3D(view), QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slotGoTo()));
}

GoTo::~GoTo()
{

}

void GoTo::slotGoTo()
{
	m_pMap3D->getManipulator()->setViewpoint(osgEarth::Util::Viewpoint(
		ui.lineEditLon->text().toDouble(),
		ui.lineEditLat->text().toDouble(),
		ui.lineEditAlt->text().toDouble(),
		0.0, -90.0, 5000));
}
