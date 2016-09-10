#include <QApplication>
#include "JK_MainWgt.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	JK_MainWgt mWgt(nullptr);
	mWgt.show();

	return app.exec();
}
