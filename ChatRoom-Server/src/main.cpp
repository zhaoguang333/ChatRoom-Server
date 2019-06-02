#include "ChatRoomServerUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ChatRoomServerUI w;
	w.show();
	return a.exec();
}
