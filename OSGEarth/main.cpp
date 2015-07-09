#include "OSGEarth.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OSGEarth w;
	w.showMaximized();
	return a.exec();
}
