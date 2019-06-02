#include "DoTcpSocket.h"
#include <QDataStream>

//����ֻ�н������ݣ����������ڿͻ�����QTcpServer��
DoTcpSocket::DoTcpSocket(QObject *parent)
	: QTcpSocket(parent)
{
	//readyRead()��disconnected() �� QTcpSocket �̳������ź�
	connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived_Slots()));
	connect(this, SIGNAL(disconnected()), this, SLOT(disConnected_Slots()));
}

DoTcpSocket::~DoTcpSocket()
{
}

//���տͻ��˷������ݵĲۺ���
void DoTcpSocket::dataReceived_Slots()
{
	while (bytesAvailable() > 0)
	{
		int length = bytesAvailable();
		QDataStream in(this);

		//������������
		int type;
		in >> type;

		switch (type)
		{
		case USERLOGIN:
			in >> clientComputerName >> clientComputerIP >> clientlAccount >> clientPassword >> clientLoginStatus;
			emit userLogin_Signals(clientlAccount, clientPassword, clientLoginStatus, this->socketDescriptor(), clientComputerName, clientComputerIP);
			break;
		case CHATMESSAGE:
			in >> userChatMessage;
			emit chatMessage_Signals(this->socketDescriptor(), userChatMessage);
			break;
		case USERREGISTER:
			in >> userName_Register >> userPassword_Register;
			emit userRegister_Signals(this->socketDescriptor(), userName_Register, userPassword_Register);
			break;
		case USEREXITHANDLE:
			emit userExitHandle_Signals(this->socketDescriptor());
			break;
		default:
			break;
		}
	}
}

//�ͻ��˶Ͽ����ӷ����Ĳۺ���
void DoTcpSocket::disConnected_Slots()
{
	emit disConnected_Signals(this->socketDescriptor());
}

