#include "widget3d.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Widget3D w;
	w.show();
	return a.exec();
}
