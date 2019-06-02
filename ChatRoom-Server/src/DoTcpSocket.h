#pragma once

#include <QTcpSocket>

//ö����
enum RequestTypeEnum
{
	USERLOGIN, USERLOGINCHECK, UPDATEALLUSER, NOTICEALLCLIENT, USEREXITHANDLE, USEREXIT, CHATMESSAGE, USERREGISTER
};

class DoTcpSocket : public QTcpSocket
{
	Q_OBJECT

public:
	//�ͻ��˷����ĵ�¼��Ϣ
	QString clientComputerName;	//�ͻ��˵�����
	QString clientComputerIP;	//�ͻ���ip��ַ
	QString clientlAccount;		//�ͻ����˺�
	QString clientPassword;		//�ͻ�������
	int clientLoginStatus;		//�ͻ��˵�¼״̬

	QString userChatMessage;	//�ͻ��˷�����������Ϣ

	QString userName_Register;		//ע���û�������
	QString userPassword_Register;	//ע���û�������

protected slots:
	void dataReceived_Slots();	//���տͻ��˷������ݵĲۺ���
	void disConnected_Slots();	//�ͻ��˶Ͽ����ӷ����Ĳۺ���

signals:
	void userLogin_Signals(QString, QString, int, int, QString, QString);	//��֤��¼��Ϣ
signals:
	void userExitHandle_Signals(int);	//�û��˳�����
signals:
	void disConnected_Signals(int);	//�Ͽ�����
signals:
	void chatMessage_Signals(int, QString);	//������Ϣ
signals:
	void userRegister_Signals(int, QString,QString);	//�û�ע��

public:
	DoTcpSocket(QObject *parent);
	~DoTcpSocket();
};
