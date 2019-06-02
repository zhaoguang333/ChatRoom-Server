#pragma once

#include <QtWidgets/QWidget>
#include "ui_ChatRoomServerUI.h"
#include "DoTcpServer.h"

class ChatRoomServerUI : public QWidget
{
	Q_OBJECT
public:
	ChatRoomServerUI(QWidget *parent = Q_NULLPTR);

private:
	int port;		//�˿ںţ���ͻ�����ͬ
	void showServerHostIP();	//��ʾ������ip��ַ

	DoTcpServer* server;	//����һ��ȫ�ֵ�server����

public slots:
	void cleanBtn_Slots();	//������ť
	void serverUIAddUser_Slots(QString, QString, QString, QString);
	void serverUIDeleteUser_Slots(QString);
	void serverUIChatMessage_Slots(QString);
private:
	void closeEvent(QCloseEvent *event);	//��д�رմ��ں���


private:
	Ui::ChatRoomServerUIClass ui;
};
