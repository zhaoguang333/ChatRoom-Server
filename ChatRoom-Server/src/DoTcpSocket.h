#pragma once

#include <QTcpSocket>

//枚举类
enum RequestTypeEnum
{
	USERLOGIN, USERLOGINCHECK, UPDATEALLUSER, NOTICEALLCLIENT, USEREXITHANDLE, USEREXIT, CHATMESSAGE, USERREGISTER
};

class DoTcpSocket : public QTcpSocket
{
	Q_OBJECT

public:
	//客户端发来的登录信息
	QString clientComputerName;	//客户端电脑名
	QString clientComputerIP;	//客户端ip地址
	QString clientlAccount;		//客户端账号
	QString clientPassword;		//客户端密码
	int clientLoginStatus;		//客户端登录状态

	QString userChatMessage;	//客户端发来的聊天消息

	QString userName_Register;		//注册用户的名字
	QString userPassword_Register;	//注册用户的密码

protected slots:
	void dataReceived_Slots();	//接收客户端发来数据的槽函数
	void disConnected_Slots();	//客户端断开连接发出的槽函数

signals:
	void userLogin_Signals(QString, QString, int, int, QString, QString);	//验证登录信息
signals:
	void userExitHandle_Signals(int);	//用户退出处理
signals:
	void disConnected_Signals(int);	//断开连接
signals:
	void chatMessage_Signals(int, QString);	//聊天消息
signals:
	void userRegister_Signals(int, QString,QString);	//用户注册

public:
	DoTcpSocket(QObject *parent);
	~DoTcpSocket();
};
