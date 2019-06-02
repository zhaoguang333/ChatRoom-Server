/********************************************************************************
** Form generated from reading UI file 'ChatRoomServerUI.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATROOMSERVERUI_H
#define UI_CHATROOMSERVERUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatRoomServerUIClass
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLabel *serverHostIP;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *PortLabel;
    QPushButton *cleanBtn;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QLabel *onlineNumber;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *ChatRoomServerUIClass)
    {
        if (ChatRoomServerUIClass->objectName().isEmpty())
            ChatRoomServerUIClass->setObjectName(QStringLiteral("ChatRoomServerUIClass"));
        ChatRoomServerUIClass->resize(1097, 601);
        ChatRoomServerUIClass->setMinimumSize(QSize(1087, 601));
        verticalLayout_3 = new QVBoxLayout(ChatRoomServerUIClass);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_2 = new QLabel(ChatRoomServerUIClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setPointSize(15);
        label_2->setFont(font);

        horizontalLayout_3->addWidget(label_2);

        serverHostIP = new QLabel(ChatRoomServerUIClass);
        serverHostIP->setObjectName(QStringLiteral("serverHostIP"));
        serverHostIP->setMinimumSize(QSize(100, 0));
        serverHostIP->setFont(font);
        serverHostIP->setCursor(QCursor(Qt::ArrowCursor));
        serverHostIP->setFocusPolicy(Qt::NoFocus);
        serverHostIP->setFrameShape(QFrame::Box);
        serverHostIP->setFrameShadow(QFrame::Sunken);
        serverHostIP->setTextFormat(Qt::AutoText);
        serverHostIP->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(serverHostIP);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        listWidget = new QListWidget(ChatRoomServerUIClass);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(ChatRoomServerUIClass);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        PortLabel = new QLabel(ChatRoomServerUIClass);
        PortLabel->setObjectName(QStringLiteral("PortLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(PortLabel->sizePolicy().hasHeightForWidth());
        PortLabel->setSizePolicy(sizePolicy1);
        PortLabel->setFrameShape(QFrame::Panel);
        PortLabel->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(PortLabel);

        cleanBtn = new QPushButton(ChatRoomServerUIClass);
        cleanBtn->setObjectName(QStringLiteral("cleanBtn"));

        horizontalLayout->addWidget(cleanBtn);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_4->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget = new QTableWidget(ChatRoomServerUIClass);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setTextElideMode(Qt::ElideMiddle);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(125);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(tableWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_3 = new QLabel(ChatRoomServerUIClass);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font1;
        font1.setPointSize(12);
        label_3->setFont(font1);

        horizontalLayout_2->addWidget(label_3);

        onlineNumber = new QLabel(ChatRoomServerUIClass);
        onlineNumber->setObjectName(QStringLiteral("onlineNumber"));
        onlineNumber->setMinimumSize(QSize(50, 0));
        onlineNumber->setFont(font1);
        onlineNumber->setFrameShape(QFrame::WinPanel);
        onlineNumber->setFrameShadow(QFrame::Plain);
        onlineNumber->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(onlineNumber);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_4);


        retranslateUi(ChatRoomServerUIClass);

        QMetaObject::connectSlotsByName(ChatRoomServerUIClass);
    } // setupUi

    void retranslateUi(QWidget *ChatRoomServerUIClass)
    {
        ChatRoomServerUIClass->setWindowTitle(QApplication::translate("ChatRoomServerUIClass", "ChatRoomServer", Q_NULLPTR));
        label_2->setText(QApplication::translate("ChatRoomServerUIClass", "\346\234\215\345\212\241\345\231\250IP\345\234\260\345\235\200\357\274\232", Q_NULLPTR));
        serverHostIP->setText(QApplication::translate("ChatRoomServerUIClass", "0.0.0.0", Q_NULLPTR));
        label->setText(QApplication::translate("ChatRoomServerUIClass", "\347\253\257\345\217\243\345\217\267\357\274\232", Q_NULLPTR));
        PortLabel->setText(QString());
        cleanBtn->setText(QApplication::translate("ChatRoomServerUIClass", "\346\270\205\345\261\217", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ChatRoomServerUIClass", "\345\220\215\345\255\227", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ChatRoomServerUIClass", "\350\264\246\345\217\267", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ChatRoomServerUIClass", "ip\345\234\260\345\235\200", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("ChatRoomServerUIClass", "\344\270\273\346\234\272\345\220\215", Q_NULLPTR));
        label_3->setText(QApplication::translate("ChatRoomServerUIClass", "\345\275\223\345\211\215\345\234\250\347\272\277\344\272\272\346\225\260\357\274\232", Q_NULLPTR));
        onlineNumber->setText(QApplication::translate("ChatRoomServerUIClass", "0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChatRoomServerUIClass: public Ui_ChatRoomServerUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATROOMSERVERUI_H
