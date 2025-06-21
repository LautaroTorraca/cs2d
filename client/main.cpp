#include <QApplication>
#include "Login/ServerMenu.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	ServerMenu menu(argv[1]);
	menu.show();
	return app.exec();
}
