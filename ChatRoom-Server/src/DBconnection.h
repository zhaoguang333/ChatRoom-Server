#pragma once

#include <QtSql>

//连接数据库
static bool createConnection()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setPort(3306);
	db.setUserName("root");
	db.setPassword("123456");
	db.setDatabaseName("chatroom");
	bool ok = db.open();
	db.exec("SET NAMES 'GBK'");
	if (!ok)
	{
		return false;
	}
	else
	{
		return true;
	}
}


