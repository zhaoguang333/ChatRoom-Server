#pragma once

#include <QTcpServer>
#include "DoTcpSocket.h"

class DoTcpServer : public QTcpServer
{
	Q_OBJECT

protected:
	void incomingConnection(int socketDescriptor);	//�麯����������һ���µ�����ʱ��QTcpSever��ᴥ���˺���
public:
	QList<DoTcpSocket*> clientList;	//����ÿһ������������û�
private:
	void userLoginCheck(int, int);	//����û���¼�ɹ�����¼�����Ѿ���¼
	void updateAllUser();			//֪ͨ���пͻ����Լ�����Ϣ
	void noticeAllClient(QString);	//�����пͻ��˷��͵�¼����Ϣ

public slots:
	void userLogin_Slots(QString, QString, int, int, QString, QString);	//�û���¼�ۺ�������
	void userExitHandle_Slots(int);	//�û��˳�����
	void disConnected_Slots(int);								//�Ͽ�����ʱ��'�׽��ֶ���'ɾ��
	void chatMessage_Slots(int, QString);							//������Ϣ
	void userRegister_Slots(int, QString, QString);						//�û�ע��

signals:
	void serverUIAddUser_Signals(QString, QString, QString, QString);	//֪ͨ��������������û���Ϣ
signals:
	void serverUIDeleteUser_Signals(QString);							//֪ͨ��������������û���Ϣ
signals:
	void serverUIChatMessage_Signals(QString);							//֪ͨ�����������������
	

public:
	DoTcpServer(QObject *parent, int port = 0);
	~DoTcpServer();
};
