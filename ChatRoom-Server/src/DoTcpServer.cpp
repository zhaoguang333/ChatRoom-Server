#include "DoTcpServer.h"
#include "DBconnection.h"
#include <QDataStream>



DoTcpServer::DoTcpServer(QObject *parent, int port)
	: QTcpServer(parent)
{
	//在指定端口监听任意的地址
	listen(QHostAddress::Any, port);

	//连接数据库
	if (!createConnection())
	{
		qDebug() << QString::fromLocal8Bit("连接数据库失败！");
	}
	else
	{
		qDebug() << QString::fromLocal8Bit("连接数据库成功！");
	}
}

DoTcpServer::~DoTcpServer()
{
}

//当出现一个新的连接时，QTcpSever类会触发此函数
void DoTcpServer::incomingConnection(int socketDescriptor)
{
	qDebug() << QString::fromLocal8Bit("当出现一个新的连接时，QTcpSever类会触发此函数，此函数的套接字描述符为：") << socketDescriptor;

	//创建一个新的TcpSocket与客户端连接
	DoTcpSocket *client = new DoTcpSocket(this);
	//用户登录
	connect(client, SIGNAL(userLogin_Signals(QString, QString, int, int, QString, QString)), this, SLOT(userLogin_Slots(QString, QString, int, int, QString, QString)));
	//用户退出处理-----修改数据库数据
	connect(client, SIGNAL(userExitHandle_Signals(int)), this, SLOT(userExitHandle_Slots(int)));
	//用户断开连接
	connect(client, SIGNAL(disConnected_Signals(int)), this, SLOT(disConnected_Slots(int)));
	//聊天消息
	connect(client, SIGNAL(chatMessage_Signals(int, QString)), this, SLOT(chatMessage_Slots(int, QString)));
	//用户注册
	connect(client, SIGNAL(userRegister_Signals(int, QString, QString)), this, SLOT(userRegister_Slots(int, QString, QString)));

	//设置'客户端套接字对象'的描述符，用来标识加入进来的这个客户端
	client->setSocketDescriptor(socketDescriptor);
	clientList << client;
}

//客户端请求登录处理的槽函数
void DoTcpServer::userLogin_Slots(QString userAccount, QString userPassword, int userLoginStatus, int socketDescriptor, QString userComputerName, QString userComputerIP)
{
	qDebug() << QString::fromLocal8Bit("客户端请求登录处理的槽函数，此套接字描述符为：") << socketDescriptor;

	//查询数据库信息
	QSqlQuery query;
	query.exec("SELECT account,password,status,name FROM userinfo");
	//验证这个客户端信息处理
	while (query.next())
	{
		QString accountDB = query.value(0).toString();
		QString passwordDB = query.value(1).toString();
		//验证账号和密码是否与数据库的数据相同，如果不同直接向客户端返回错误信息
		if (userAccount == accountDB && userPassword == passwordDB)
		{
			//验证该账号的登录状态
			int s = query.value(2).toInt();
			if (userLoginStatus == s)
			{
				//查询该账号的名字
				QString userName = query.value(3).toString();

				//修改数据库的登录状态
				QSqlQuery q;
				q.exec(QString("UPDATE userinfo SET status = '1' WHERE account = '%1'").arg(userAccount));

				//保存该用户的ip地址
				q.exec(QString("UPDATE userinfo SET ip = '%1' WHERE account = '%2'").arg(userComputerIP).arg(userAccount));

				//保存该用户的套接字
				q.exec(QString("UPDATE userinfo SET descriptor = '%1' WHERE account = '%2'").arg(socketDescriptor).arg(userAccount));

				//在服务器显示客户端信息
				emit serverUIAddUser_Signals(userComputerName, userComputerIP, userAccount, userName);

				//向客户端返回这个客户端成功的登录了
				userLoginCheck(socketDescriptor, 1);

				//向所有客户端发送登录到聊天室的信息
				noticeAllClient(userName);

				//向所有客户端更新所有在线用户的信息
				updateAllUser();

				//返回函数
				return;
			}
			else
			{
				//向客户端返回这个客户端已经登录信息
				userLoginCheck(socketDescriptor,2);

				//返回函数
				return;
			}
		}
	}
	//直接向客户端返回这个客户端错误信息
	userLoginCheck(socketDescriptor, 0);
}

//检查用户登录状态---登录成功---登录错误---已经登录
void DoTcpServer::userLoginCheck(int socketDescriptor,int status)
{
	QByteArray checkData;
	QDataStream out(&checkData, QIODevice::WriteOnly);
	out << RequestTypeEnum::USERLOGINCHECK << status;
	//响应登录状态给发来请求的这个客户端
	for (int i = 0; i < clientList.count(); i++)
	{
		QTcpSocket* response = clientList.at(i);
		if (response->socketDescriptor() == socketDescriptor)
		{
			int length = response->write(checkData);
			return;
		}
	}
}

//向所有客户端发送登录到聊天室的信息，此函数不是客户端请求的，所有不用套接字描述符！！！
void DoTcpServer::noticeAllClient(QString userName)
{
	QString time = QDateTime::currentDateTime().toString("MM-dd hh:mm");
	QString enterChatRoomMsg = userName + " : " + time + QString::fromLocal8Bit(" 进入聊天室");

	QByteArray data;
	QDataStream out(&data, QIODevice::WriteOnly);
	out << RequestTypeEnum::NOTICEALLCLIENT << userName << enterChatRoomMsg;
	//向所有客户端发送登录到聊天室的信息
	for (int i = 0; i < clientList.count(); i++)
	{
		QTcpSocket* responseBroadcast = clientList.at(i);
		int length = responseBroadcast->write(data);
	}
}

//向所有客户端更新所有在线用户的信息，只查询数据库响应给客户端即可，此函数不是客户端请求的，所有不用套接字描述符！！！
void DoTcpServer::updateAllUser()
{
	QSqlQuery query;
	//循环发给已经登录在线的每一个用户
	for (int i = 0; i < clientList.count(); i++)
	{
		query.exec("SELECT name,ip FROM userinfo WHERE status = '1'");
		while (query.next())
		{
			QString userName = query.value(0).toString();
			QString userIPAddress = query.value(1).toString();

			//发给已经登录在线的第i个用户
			QByteArray data;
			QDataStream out(&data, QIODevice::WriteOnly);
			out << RequestTypeEnum::UPDATEALLUSER << userName << userIPAddress;
			QTcpSocket* responseBroadcast = clientList.at(i);
			int length = responseBroadcast->write(data);
		}
	}
}

//用户退出处理-----修改数据库数据
void DoTcpServer::userExitHandle_Slots(int socketDescriptor)
{
	qDebug() << QString::fromLocal8Bit("********用户退出处理，修改数据库，此套接字描述符为：") << socketDescriptor;

	QSqlQuery q;
	q.exec(QString("SELECT descriptor,account,name FROM userinfo WHERE descriptor = '%1'").arg(socketDescriptor));
	while (q.next())
	{
		int descriptorTemp = q.value(0).toInt();
		QString userAccount = q.value(1).toString();
		QString userName = q.value(2).toString();
		//判断从数据库查询出来的套接字描述符是否与请求客户端的套接字相同
		if (descriptorTemp == socketDescriptor)
		{
			//修改数据库的登录状态
			q.exec(QString("UPDATE userinfo SET status = '0' WHERE account = '%1'").arg(userAccount));

			//删除用户的ip地址
			q.exec(QString("UPDATE userinfo SET ip = '0.0.0.0' WHERE account = '%1'").arg(userAccount));

			//删除该用户的套接字
			q.exec(QString("UPDATE userinfo SET descriptor = '0' WHERE account = '%1'").arg(userAccount));

			//查询客户端列表的数量并更新服务器在线人数
			emit serverUIDeleteUser_Signals(userAccount);

			//响应给客户端有用户退出聊天室的信息
			QString time = QDateTime::currentDateTime().toString("MM-dd hh:mm");
			QString exitInformation = userName + " : " + time + QString::fromLocal8Bit(" 退出聊天室");

			QByteArray data;
			QDataStream out(&data, QIODevice::WriteOnly);
			out << RequestTypeEnum::USEREXIT << userName << exitInformation;
			for (int i = 0; i < clientList.count(); i++)
			{
				//响应给每一个客户端
				QTcpSocket* serverBroadcast = clientList.at(i);
				int length = serverBroadcast->write(data);
			}
		}
	}
	
}

//用户断开连接
void DoTcpServer::disConnected_Slots(int socketDescriptor)
{
	for (int i = 0; i < clientList.count(); i++)
	{
		QTcpSocket* clientListtRemove = clientList.at(i);
		if (clientListtRemove->socketDescriptor() == socketDescriptor)
		{
			//从列表中删除连接的客户端
			clientList.removeAt(i);
			qDebug() << QString::fromLocal8Bit("从列表删除客户端后的总数为：") << clientList.count();
			return;
		}
	}
}

//聊天消息
void DoTcpServer::chatMessage_Slots(int socketDescriptor, QString userChatMessage)
{
	qDebug() << QString::fromLocal8Bit("聊天消息，此套接字描述符为：") << socketDescriptor;

	QSqlQuery query;
	QString userName;
	query.exec(QString("SELECT name FROM userinfo WHERE descriptor = '%1'").arg(socketDescriptor));
	while (query.next())
	{
		userName = query.value(0).toString();
	}
	QString time = QDateTime::currentDateTime().toString("MM-dd hh:mm");
	QString chatMessage = "[ " + userName + " ] " + time + "\n" + userChatMessage;

	QByteArray messageData;
	QDataStream out(&messageData, QIODevice::WriteOnly);
	out << RequestTypeEnum::CHATMESSAGE << chatMessage;
	for (int i = 0; i < clientList.count(); i++)
	{
		QTcpSocket* serverBroadcast = clientList.at(i);
		int length = serverBroadcast->write(messageData);
	}

	//在服务器显示客户端发来的消息
	emit serverUIChatMessage_Signals(chatMessage);
}

//用户注册
void DoTcpServer::userRegister_Slots(int socketDescriptor, QString userName_Register, QString userPassword_Register)
{
	qDebug() << QString::fromLocal8Bit("用户注册功能，此套接字描述符为：") << socketDescriptor;
	QString userAccount;	//使用循环得到的账号并存入数据库

	QSqlQuery q;
	bool n = q.exec("SELECT account FROM userinfo");
	while (q.next())
		for (int i = 100; i < 200; i++)
		{
			QString userAccountTemp = q.value(0).toString();
			userAccount = QString::number(i);
			//判断数据库里面的账号是否存在
			if (userAccount == userAccountTemp)
			{
				q.next();
			}
			else
			{
				//存入数据库
				bool m = q.exec(QString("INSERT INTO userinfo(account,password,name,status) VALUES('%1','%2','%3',0)").arg(userAccount).arg(userPassword_Register).arg(userName_Register));

				QByteArray checkData;
				QDataStream out(&checkData, QIODevice::WriteOnly);
				out << RequestTypeEnum::USERREGISTER << userAccount;
				//响应账号给发来请求的这个客户端
				for (int i = 0; i < clientList.count(); i++)
				{
					QTcpSocket* clientListTemp = clientList.at(i);
					if (clientListTemp->socketDescriptor() == socketDescriptor)
					{
						int length = clientListTemp->write(checkData);
						return;
					}
				}

			}
		}
}


