#include <QtWidgets>

#include "QTetris.h"



int main(int argc, char *argv[])
{
	QStringList paths = QCoreApplication::libraryPaths();
	paths.append(".");
	paths.append("imageformats");
	paths.append("mediaservice");
	paths.append("platforms");
	QCoreApplication::setLibraryPaths(paths);

	QApplication a(argc, argv);
	QTetris w;
	w.show();
	return a.exec();
}
