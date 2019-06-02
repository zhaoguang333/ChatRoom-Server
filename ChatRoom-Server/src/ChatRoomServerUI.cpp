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
	connect(ui.cleanBtn, SIGNAL(clicked()), this, SLOT(cleanBtn_Slots()));	//清屏按钮

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

//新用户增加
void ChatRoomServerUI::serverUIAddUser_Slots(QString userComputerName, QString userComputerIP, QString userAccount, QString userName)
{
	//在表格显示用户信息
	QTableWidgetItem* account = new QTableWidgetItem(userAccount);
	QTableWidgetItem* name = new QTableWidgetItem(userName);
	QTableWidgetItem* hostname = new QTableWidgetItem(userComputerName);
	QTableWidgetItem* ip = new QTableWidgetItem(userComputerIP);
	ui.tableWidget->insertRow(0);
	ui.tableWidget->setItem(0, 0, name);	//名字	
	ui.tableWidget->setItem(0, 1, account);	//账号
	ui.tableWidget->setItem(0, 2, ip);		//ip地址
	ui.tableWidget->setItem(0, 3, hostname);//主机名

	//更新在线用户数
	ui.onlineNumber->setText(QString("%1").arg(ui.tableWidget->rowCount()));
}

//用户退出聊天室
void ChatRoomServerUI::serverUIDeleteUser_Slots(QString userAccount)
{
	//在表格删除退出用户
	int rowNumber = ui.tableWidget->findItems(userAccount, Qt::MatchExactly).first()->row();
	ui.tableWidget->removeRow(rowNumber);

	//更新在线用户数
	ui.onlineNumber->setText(QString("%1").arg(ui.tableWidget->rowCount()));
}

//聊天信息
void ChatRoomServerUI::serverUIChatMessage_Slots(QString message)
{
	ui.listWidget->addItem(message);
	ui.listWidget->scrollToBottom();
}

//清屏按钮
void ChatRoomServerUI::cleanBtn_Slots()
{
	ui.listWidget->clear();
}

//重写关闭窗口函数
void ChatRoomServerUI::closeEvent(QCloseEvent * event)
{
	QMessageBox::StandardButton button;
	button = QMessageBox::question(this, QString::fromLocal8Bit("退出程序"), QString(QString::fromLocal8Bit("确认退出服务器？")), QMessageBox::Yes | QMessageBox::No);
	if (button == QMessageBox::No) {
		event->ignore();
	}
	else if (button == QMessageBox::Yes)
	{
		event->accept();
	}
}
