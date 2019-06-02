#pragma once

#include <QTcpServer>
#include "DoTcpSocket.h"

class DoTcpServer : public QTcpServer
{
	Q_OBJECT

protected:
	void incomingConnection(int socketDescriptor);	//虚函数：当出现一个新的连接时，QTcpSever类会触发此函数
public:
	QList<DoTcpSocket*> clientList;	//保存每一个加入进来的用户
private:
	void userLoginCheck(int, int);	//检查用户登录成功，登录错误，已经登录
	void updateAllUser();			//通知所有客户端自己的信息
	void noticeAllClient(QString);	//向所有客户端发送登录的信息

public slots:
	void userLogin_Slots(QString, QString, int, int, QString, QString);	//用户登录槽函数处理
	void userExitHandle_Slots(int);	//用户退出处理
	void disConnected_Slots(int);								//断开连接时将'套接字对象'删除
	void chatMessage_Slots(int, QString);							//聊天消息
	void userRegister_Slots(int, QString, QString);						//用户注册

signals:
	void serverUIAddUser_Signals(QString, QString, QString, QString);	//通知服务器界面更新用户信息
signals:
	void serverUIDeleteUser_Signals(QString);							//通知服务器界面更新用户信息
signals:
	void serverUIChatMessage_Signals(QString);							//通知服务器界面更新聊天
	

public:
	DoTcpServer(QObject *parent, int port = 0);
	~DoTcpServer();
};
