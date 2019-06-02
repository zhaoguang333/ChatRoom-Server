#include "DoTcpSocket.h"
#include <QDataStream>

//此类只有接受数据，发送数据在客户端在QTcpServer类
DoTcpSocket::DoTcpSocket(QObject *parent)
	: QTcpSocket(parent)
{
	//readyRead()、disconnected() 是 QTcpSocket 继承来的信号
	connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived_Slots()));
	connect(this, SIGNAL(disconnected()), this, SLOT(disConnected_Slots()));
}

DoTcpSocket::~DoTcpSocket()
{
}

//接收客户端发来数据的槽函数
void DoTcpSocket::dataReceived_Slots()
{
	while (bytesAvailable() > 0)
	{
		int length = bytesAvailable();
		QDataStream in(this);

		//接收请求类型
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

//客户端断开连接发出的槽函数
void DoTcpSocket::disConnected_Slots()
{
	emit disConnected_Signals(this->socketDescriptor());
}

