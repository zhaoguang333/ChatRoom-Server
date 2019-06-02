#include "DoTcpServer.h"
#include "DBconnection.h"
#include <QDataStream>



DoTcpServer::DoTcpServer(QObject *parent, int port)
	: QTcpServer(parent)
{
	//��ָ���˿ڼ�������ĵ�ַ
	listen(QHostAddress::Any, port);

	//�������ݿ�
	if (!createConnection())
	{
		qDebug() << QString::fromLocal8Bit("�������ݿ�ʧ�ܣ�");
	}
	else
	{
		qDebug() << QString::fromLocal8Bit("�������ݿ�ɹ���");
	}
}

DoTcpServer::~DoTcpServer()
{
}

//������һ���µ�����ʱ��QTcpSever��ᴥ���˺���
void DoTcpServer::incomingConnection(int socketDescriptor)
{
	qDebug() << QString::fromLocal8Bit("������һ���µ�����ʱ��QTcpSever��ᴥ���˺������˺������׽���������Ϊ��") << socketDescriptor;

	//����һ���µ�TcpSocket��ͻ�������
	DoTcpSocket *client = new DoTcpSocket(this);
	//�û���¼
	connect(client, SIGNAL(userLogin_Signals(QString, QString, int, int, QString, QString)), this, SLOT(userLogin_Slots(QString, QString, int, int, QString, QString)));
	//�û��˳�����-----�޸����ݿ�����
	connect(client, SIGNAL(userExitHandle_Signals(int)), this, SLOT(userExitHandle_Slots(int)));
	//�û��Ͽ�����
	connect(client, SIGNAL(disConnected_Signals(int)), this, SLOT(disConnected_Slots(int)));
	//������Ϣ
	connect(client, SIGNAL(chatMessage_Signals(int, QString)), this, SLOT(chatMessage_Slots(int, QString)));
	//�û�ע��
	connect(client, SIGNAL(userRegister_Signals(int, QString, QString)), this, SLOT(userRegister_Slots(int, QString, QString)));

	//����'�ͻ����׽��ֶ���'����������������ʶ�������������ͻ���
	client->setSocketDescriptor(socketDescriptor);
	clientList << client;
}

//�ͻ��������¼����Ĳۺ���
void DoTcpServer::userLogin_Slots(QString userAccount, QString userPassword, int userLoginStatus, int socketDescriptor, QString userComputerName, QString userComputerIP)
{
	qDebug() << QString::fromLocal8Bit("�ͻ��������¼����Ĳۺ��������׽���������Ϊ��") << socketDescriptor;

	//��ѯ���ݿ���Ϣ
	QSqlQuery query;
	query.exec("SELECT account,password,status,name FROM userinfo");
	//��֤����ͻ�����Ϣ����
	while (query.next())
	{
		QString accountDB = query.value(0).toString();
		QString passwordDB = query.value(1).toString();
		//��֤�˺ź������Ƿ������ݿ��������ͬ�������ֱͬ����ͻ��˷��ش�����Ϣ
		if (userAccount == accountDB && userPassword == passwordDB)
		{
			//��֤���˺ŵĵ�¼״̬
			int s = query.value(2).toInt();
			if (userLoginStatus == s)
			{
				//��ѯ���˺ŵ�����
				QString userName = query.value(3).toString();

				//�޸����ݿ�ĵ�¼״̬
				QSqlQuery q;
				q.exec(QString("UPDATE userinfo SET status = '1' WHERE account = '%1'").arg(userAccount));

				//������û���ip��ַ
				q.exec(QString("UPDATE userinfo SET ip = '%1' WHERE account = '%2'").arg(userComputerIP).arg(userAccount));

				//������û����׽���
				q.exec(QString("UPDATE userinfo SET descriptor = '%1' WHERE account = '%2'").arg(socketDescriptor).arg(userAccount));

				//�ڷ�������ʾ�ͻ�����Ϣ
				emit serverUIAddUser_Signals(userComputerName, userComputerIP, userAccount, userName);

				//��ͻ��˷�������ͻ��˳ɹ��ĵ�¼��
				userLoginCheck(socketDescriptor, 1);

				//�����пͻ��˷��͵�¼�������ҵ���Ϣ
				noticeAllClient(userName);

				//�����пͻ��˸������������û�����Ϣ
				updateAllUser();

				//���غ���
				return;
			}
			else
			{
				//��ͻ��˷�������ͻ����Ѿ���¼��Ϣ
				userLoginCheck(socketDescriptor,2);

				//���غ���
				return;
			}
		}
	}
	//ֱ����ͻ��˷�������ͻ��˴�����Ϣ
	userLoginCheck(socketDescriptor, 0);
}

//����û���¼״̬---��¼�ɹ�---��¼����---�Ѿ���¼
void DoTcpServer::userLoginCheck(int socketDescriptor,int status)
{
	QByteArray checkData;
	QDataStream out(&checkData, QIODevice::WriteOnly);
	out << RequestTypeEnum::USERLOGINCHECK << status;
	//��Ӧ��¼״̬���������������ͻ���
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

//�����пͻ��˷��͵�¼�������ҵ���Ϣ���˺������ǿͻ�������ģ����в����׽���������������
void DoTcpServer::noticeAllClient(QString userName)
{
	QString time = QDateTime::currentDateTime().toString("MM-dd hh:mm");
	QString enterChatRoomMsg = userName + " : " + time + QString::fromLocal8Bit(" ����������");

	QByteArray data;
	QDataStream out(&data, QIODevice::WriteOnly);
	out << RequestTypeEnum::NOTICEALLCLIENT << userName << enterChatRoomMsg;
	//�����пͻ��˷��͵�¼�������ҵ���Ϣ
	for (int i = 0; i < clientList.count(); i++)
	{
		QTcpSocket* responseBroadcast = clientList.at(i);
		int length = responseBroadcast->write(data);
	}
}

//�����пͻ��˸������������û�����Ϣ��ֻ��ѯ���ݿ���Ӧ���ͻ��˼��ɣ��˺������ǿͻ�������ģ����в����׽���������������
void DoTcpServer::updateAllUser()
{
	QSqlQuery query;
	//ѭ�������Ѿ���¼���ߵ�ÿһ���û�
	for (int i = 0; i < clientList.count(); i++)
	{
		query.exec("SELECT name,ip FROM userinfo WHERE status = '1'");
		while (query.next())
		{
			QString userName = query.value(0).toString();
			QString userIPAddress = query.value(1).toString();

			//�����Ѿ���¼���ߵĵ�i���û�
			QByteArray data;
			QDataStream out(&data, QIODevice::WriteOnly);
			out << RequestTypeEnum::UPDATEALLUSER << userName << userIPAddress;
			QTcpSocket* responseBroadcast = clientList.at(i);
			int length = responseBroadcast->write(data);
		}
	}
}

//�û��˳�����-----�޸����ݿ�����
void DoTcpServer::userExitHandle_Slots(int socketDescriptor)
{
	qDebug() << QString::fromLocal8Bit("********�û��˳������޸����ݿ⣬���׽���������Ϊ��") << socketDescriptor;

	QSqlQuery q;
	q.exec(QString("SELECT descriptor,account,name FROM userinfo WHERE descriptor = '%1'").arg(socketDescriptor));
	while (q.next())
	{
		int descriptorTemp = q.value(0).toInt();
		QString userAccount = q.value(1).toString();
		QString userName = q.value(2).toString();
		//�жϴ����ݿ��ѯ�������׽����������Ƿ�������ͻ��˵��׽�����ͬ
		if (descriptorTemp == socketDescriptor)
		{
			//�޸����ݿ�ĵ�¼״̬
			q.exec(QString("UPDATE userinfo SET status = '0' WHERE account = '%1'").arg(userAccount));

			//ɾ���û���ip��ַ
			q.exec(QString("UPDATE userinfo SET ip = '0.0.0.0' WHERE account = '%1'").arg(userAccount));

			//ɾ�����û����׽���
			q.exec(QString("UPDATE userinfo SET descriptor = '0' WHERE account = '%1'").arg(userAccount));

			//��ѯ�ͻ����б�����������·�������������
			emit serverUIDeleteUser_Signals(userAccount);

			//��Ӧ���ͻ������û��˳������ҵ���Ϣ
			QString time = QDateTime::currentDateTime().toString("MM-dd hh:mm");
			QString exitInformation = userName + " : " + time + QString::fromLocal8Bit(" �˳�������");

			QByteArray data;
			QDataStream out(&data, QIODevice::WriteOnly);
			out << RequestTypeEnum::USEREXIT << userName << exitInformation;
			for (int i = 0; i < clientList.count(); i++)
			{
				//��Ӧ��ÿһ���ͻ���
				QTcpSocket* serverBroadcast = clientList.at(i);
				int length = serverBroadcast->write(data);
			}
		}
	}
	
}

//�û��Ͽ�����
void DoTcpServer::disConnected_Slots(int socketDescriptor)
{
	for (int i = 0; i < clientList.count(); i++)
	{
		QTcpSocket* clientListtRemove = clientList.at(i);
		if (clientListtRemove->socketDescriptor() == socketDescriptor)
		{
			//���б���ɾ�����ӵĿͻ���
			clientList.removeAt(i);
			qDebug() << QString::fromLocal8Bit("���б�ɾ���ͻ��˺������Ϊ��") << clientList.count();
			return;
		}
	}
}

//������Ϣ
void DoTcpServer::chatMessage_Slots(int socketDescriptor, QString userChatMessage)
{
	qDebug() << QString::fromLocal8Bit("������Ϣ�����׽���������Ϊ��") << socketDescriptor;

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

	//�ڷ�������ʾ�ͻ��˷�������Ϣ
	emit serverUIChatMessage_Signals(chatMessage);
}

//�û�ע��
void DoTcpServer::userRegister_Slots(int socketDescriptor, QString userName_Register, QString userPassword_Register)
{
	qDebug() << QString::fromLocal8Bit("�û�ע�Ṧ�ܣ����׽���������Ϊ��") << socketDescriptor;
	QString userAccount;	//ʹ��ѭ���õ����˺Ų��������ݿ�

	QSqlQuery q;
	bool n = q.exec("SELECT account FROM userinfo");
	while (q.next())
		for (int i = 100; i < 200; i++)
		{
			QString userAccountTemp = q.value(0).toString();
			userAccount = QString::number(i);
			//�ж����ݿ�������˺��Ƿ����
			if (userAccount == userAccountTemp)
			{
				q.next();
			}
			else
			{
				//�������ݿ�
				bool m = q.exec(QString("INSERT INTO userinfo(account,password,name,status) VALUES('%1','%2','%3',0)").arg(userAccount).arg(userPassword_Register).arg(userName_Register));

				QByteArray checkData;
				QDataStream out(&checkData, QIODevice::WriteOnly);
				out << RequestTypeEnum::USERREGISTER << userAccount;
				//��Ӧ�˺Ÿ��������������ͻ���
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


