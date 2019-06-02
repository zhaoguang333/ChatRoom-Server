#include "ChatRoomServerUI.h"
#include <QHostInfo>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTableWidgetItem>

ChatRoomServerUI::ChatRoomServerUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	port = 8030;
	ui.PortLabel->setText(QString::number(port));
	showServerHostIP();
	connect(ui.cleanBtn, SIGNAL(clicked()), this, SLOT(cleanBtn_Slots()));	//������ť

	server = new DoTcpServer(this, port);
	connect(server, SIGNAL(serverUIAddUser_Signals(QString, QString, QString, QString)), this, SLOT(serverUIAddUser_Slots(QString, QString, QString, QString)));
	connect(server, SIGNAL(serverUIDeleteUser_Signals(QString)), this, SLOT(serverUIDeleteUser_Slots(QString)));
	connect(server, SIGNAL(serverUIChatMessage_Signals(QString)), this, SLOT(serverUIChatMessage_Slots(QString)));
}

void ChatRoomServerUI::showServerHostIP()
{
	QHostInfo hostInformation = QHostInfo::fromName(QHostInfo::localHostName());
	QList<QHostAddress> clientList = hostInformation.addresses();

	QString serverHostIP;
	for (int i = 0; i < clientList.length(); i++)
	{
		qDebug() << clientList[i].toString();
		if (clientList[i].protocol() == QAbstractSocket::IPv4Protocol)
		{
			serverHostIP = clientList[i].toString();
		}
	}

	ui.serverHostIP->setText(serverHostIP);
}

//���û�����
void ChatRoomServerUI::serverUIAddUser_Slots(QString userComputerName, QString userComputerIP, QString userAccount, QString userName)
{
	//�ڱ����ʾ�û���Ϣ
	QTableWidgetItem* account = new QTableWidgetItem(userAccount);
	QTableWidgetItem* name = new QTableWidgetItem(userName);
	QTableWidgetItem* hostname = new QTableWidgetItem(userComputerName);
	QTableWidgetItem* ip = new QTableWidgetItem(userComputerIP);
	ui.tableWidget->insertRow(0);
	ui.tableWidget->setItem(0, 0, name);	//����	
	ui.tableWidget->setItem(0, 1, account);	//�˺�
	ui.tableWidget->setItem(0, 2, ip);		//ip��ַ
	ui.tableWidget->setItem(0, 3, hostname);//������

	//���������û���
	ui.onlineNumber->setText(QString("%1").arg(ui.tableWidget->rowCount()));
}

//�û��˳�������
void ChatRoomServerUI::serverUIDeleteUser_Slots(QString userAccount)
{
	//�ڱ��ɾ���˳��û�
	int rowNumber = ui.tableWidget->findItems(userAccount, Qt::MatchExactly).first()->row();
	ui.tableWidget->removeRow(rowNumber);

	//���������û���
	ui.onlineNumber->setText(QString("%1").arg(ui.tableWidget->rowCount()));
}

//������Ϣ
void ChatRoomServerUI::serverUIChatMessage_Slots(QString message)
{
	ui.listWidget->addItem(message);
	ui.listWidget->scrollToBottom();
}

//������ť
void ChatRoomServerUI::cleanBtn_Slots()
{
	ui.listWidget->clear();
}

//��д�رմ��ں���
void ChatRoomServerUI::closeEvent(QCloseEvent * event)
{
	QMessageBox::StandardButton button;
	button = QMessageBox::question(this, QString::fromLocal8Bit("�˳�����"), QString(QString::fromLocal8Bit("ȷ���˳���������")), QMessageBox::Yes | QMessageBox::No);
	if (button == QMessageBox::No) {
		event->ignore();
	}
	else if (button == QMessageBox::Yes)
	{
		event->accept();
	}
}
