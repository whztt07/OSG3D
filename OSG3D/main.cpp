#include "osg3d.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OSG3D w;
	w.showMaximized();
	return a.exec();
}
