#include <QApplication>
#include "login/ServerMenu.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	ServerMenu menu;
	menu.show();
	return app.exec();
}
