/********************************************************************************
** Form generated from reading UI file 'udpsimulation.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDPSIMULATION_H
#define UI_UDPSIMULATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UDPSimulation
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *input_label;
    QLineEdit *input_msg;
    QPushButton *multiple_send_btn;
    QHBoxLayout *join_btns_layout;
    QPushButton *join_btn_user_1;
    QPushButton *join_btn_user_2;
    QPushButton *join_btn_user_3;
    QPushButton *join_btn_user_4;
    QPushButton *join_btn_user_5;
    QHBoxLayout *quit_btns_layout;
    QPushButton *quit_btn_user_1;
    QPushButton *quit_btn_user_2;
    QPushButton *quit_btn_user_3;
    QPushButton *quit_btn_user_4;
    QPushButton *quit_btn_user_5;
    QLabel *label_ID;
    QHBoxLayout *input_user_ID_layout;
    QSpinBox *input_id_user_1;
    QSpinBox *input_id_user_2;
    QSpinBox *input_id_user_3;
    QSpinBox *input_id_user_4;
    QSpinBox *input_id_user_5;
    QHBoxLayout *user_list_layout;
    QListWidget *list_user_1;
    QListWidget *list_user_2;
    QListWidget *list_user_3;
    QListWidget *list_user_4;
    QListWidget *list_user_5;
    QHBoxLayout *checkbox_layout;
    QCheckBox *check_box_user_1;
    QCheckBox *check_box_user_2;
    QCheckBox *check_box_user_3;
    QCheckBox *check_box_user_4;
    QCheckBox *check_box_user_5;
    QLabel *log_label;
    QTextEdit *log;
    QPushButton *btn_log_clear;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UDPSimulation)
    {
        if (UDPSimulation->objectName().isEmpty())
            UDPSimulation->setObjectName(QString::fromUtf8("UDPSimulation"));
        UDPSimulation->resize(800, 655);
        centralwidget = new QWidget(UDPSimulation);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        input_label = new QLabel(centralwidget);
        input_label->setObjectName(QString::fromUtf8("input_label"));
        input_label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(input_label);

        input_msg = new QLineEdit(centralwidget);
        input_msg->setObjectName(QString::fromUtf8("input_msg"));

        verticalLayout->addWidget(input_msg);

        multiple_send_btn = new QPushButton(centralwidget);
        multiple_send_btn->setObjectName(QString::fromUtf8("multiple_send_btn"));

        verticalLayout->addWidget(multiple_send_btn);

        join_btns_layout = new QHBoxLayout();
        join_btns_layout->setSpacing(1);
        join_btns_layout->setObjectName(QString::fromUtf8("join_btns_layout"));
        join_btn_user_1 = new QPushButton(centralwidget);
        join_btn_user_1->setObjectName(QString::fromUtf8("join_btn_user_1"));
        join_btn_user_1->setEnabled(false);

        join_btns_layout->addWidget(join_btn_user_1);

        join_btn_user_2 = new QPushButton(centralwidget);
        join_btn_user_2->setObjectName(QString::fromUtf8("join_btn_user_2"));
        join_btn_user_2->setEnabled(false);

        join_btns_layout->addWidget(join_btn_user_2);

        join_btn_user_3 = new QPushButton(centralwidget);
        join_btn_user_3->setObjectName(QString::fromUtf8("join_btn_user_3"));
        join_btn_user_3->setEnabled(false);

        join_btns_layout->addWidget(join_btn_user_3);

        join_btn_user_4 = new QPushButton(centralwidget);
        join_btn_user_4->setObjectName(QString::fromUtf8("join_btn_user_4"));
        join_btn_user_4->setEnabled(false);

        join_btns_layout->addWidget(join_btn_user_4);

        join_btn_user_5 = new QPushButton(centralwidget);
        join_btn_user_5->setObjectName(QString::fromUtf8("join_btn_user_5"));
        join_btn_user_5->setEnabled(false);

        join_btns_layout->addWidget(join_btn_user_5);


        verticalLayout->addLayout(join_btns_layout);

        quit_btns_layout = new QHBoxLayout();
        quit_btns_layout->setSpacing(1);
        quit_btns_layout->setObjectName(QString::fromUtf8("quit_btns_layout"));
        quit_btn_user_1 = new QPushButton(centralwidget);
        quit_btn_user_1->setObjectName(QString::fromUtf8("quit_btn_user_1"));
        quit_btn_user_1->setEnabled(false);

        quit_btns_layout->addWidget(quit_btn_user_1);

        quit_btn_user_2 = new QPushButton(centralwidget);
        quit_btn_user_2->setObjectName(QString::fromUtf8("quit_btn_user_2"));
        quit_btn_user_2->setEnabled(false);

        quit_btns_layout->addWidget(quit_btn_user_2);

        quit_btn_user_3 = new QPushButton(centralwidget);
        quit_btn_user_3->setObjectName(QString::fromUtf8("quit_btn_user_3"));
        quit_btn_user_3->setEnabled(false);

        quit_btns_layout->addWidget(quit_btn_user_3);

        quit_btn_user_4 = new QPushButton(centralwidget);
        quit_btn_user_4->setObjectName(QString::fromUtf8("quit_btn_user_4"));
        quit_btn_user_4->setEnabled(false);

        quit_btns_layout->addWidget(quit_btn_user_4);

        quit_btn_user_5 = new QPushButton(centralwidget);
        quit_btn_user_5->setObjectName(QString::fromUtf8("quit_btn_user_5"));
        quit_btn_user_5->setEnabled(false);

        quit_btns_layout->addWidget(quit_btn_user_5);


        verticalLayout->addLayout(quit_btns_layout);

        label_ID = new QLabel(centralwidget);
        label_ID->setObjectName(QString::fromUtf8("label_ID"));
        label_ID->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_ID);

        input_user_ID_layout = new QHBoxLayout();
        input_user_ID_layout->setSpacing(1);
        input_user_ID_layout->setObjectName(QString::fromUtf8("input_user_ID_layout"));
        input_id_user_1 = new QSpinBox(centralwidget);
        input_id_user_1->setObjectName(QString::fromUtf8("input_id_user_1"));

        input_user_ID_layout->addWidget(input_id_user_1);

        input_id_user_2 = new QSpinBox(centralwidget);
        input_id_user_2->setObjectName(QString::fromUtf8("input_id_user_2"));

        input_user_ID_layout->addWidget(input_id_user_2);

        input_id_user_3 = new QSpinBox(centralwidget);
        input_id_user_3->setObjectName(QString::fromUtf8("input_id_user_3"));

        input_user_ID_layout->addWidget(input_id_user_3);

        input_id_user_4 = new QSpinBox(centralwidget);
        input_id_user_4->setObjectName(QString::fromUtf8("input_id_user_4"));

        input_user_ID_layout->addWidget(input_id_user_4);

        input_id_user_5 = new QSpinBox(centralwidget);
        input_id_user_5->setObjectName(QString::fromUtf8("input_id_user_5"));

        input_user_ID_layout->addWidget(input_id_user_5);


        verticalLayout->addLayout(input_user_ID_layout);

        user_list_layout = new QHBoxLayout();
        user_list_layout->setSpacing(1);
        user_list_layout->setObjectName(QString::fromUtf8("user_list_layout"));
        list_user_1 = new QListWidget(centralwidget);
        list_user_1->setObjectName(QString::fromUtf8("list_user_1"));

        user_list_layout->addWidget(list_user_1);

        list_user_2 = new QListWidget(centralwidget);
        list_user_2->setObjectName(QString::fromUtf8("list_user_2"));

        user_list_layout->addWidget(list_user_2);

        list_user_3 = new QListWidget(centralwidget);
        list_user_3->setObjectName(QString::fromUtf8("list_user_3"));

        user_list_layout->addWidget(list_user_3);

        list_user_4 = new QListWidget(centralwidget);
        list_user_4->setObjectName(QString::fromUtf8("list_user_4"));

        user_list_layout->addWidget(list_user_4);

        list_user_5 = new QListWidget(centralwidget);
        list_user_5->setObjectName(QString::fromUtf8("list_user_5"));

        user_list_layout->addWidget(list_user_5);


        verticalLayout->addLayout(user_list_layout);

        checkbox_layout = new QHBoxLayout();
        checkbox_layout->setObjectName(QString::fromUtf8("checkbox_layout"));
        check_box_user_1 = new QCheckBox(centralwidget);
        check_box_user_1->setObjectName(QString::fromUtf8("check_box_user_1"));

        checkbox_layout->addWidget(check_box_user_1);

        check_box_user_2 = new QCheckBox(centralwidget);
        check_box_user_2->setObjectName(QString::fromUtf8("check_box_user_2"));

        checkbox_layout->addWidget(check_box_user_2);

        check_box_user_3 = new QCheckBox(centralwidget);
        check_box_user_3->setObjectName(QString::fromUtf8("check_box_user_3"));

        checkbox_layout->addWidget(check_box_user_3);

        check_box_user_4 = new QCheckBox(centralwidget);
        check_box_user_4->setObjectName(QString::fromUtf8("check_box_user_4"));

        checkbox_layout->addWidget(check_box_user_4);

        check_box_user_5 = new QCheckBox(centralwidget);
        check_box_user_5->setObjectName(QString::fromUtf8("check_box_user_5"));

        checkbox_layout->addWidget(check_box_user_5);


        verticalLayout->addLayout(checkbox_layout);

        log_label = new QLabel(centralwidget);
        log_label->setObjectName(QString::fromUtf8("log_label"));
        log_label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(log_label);

        log = new QTextEdit(centralwidget);
        log->setObjectName(QString::fromUtf8("log"));

        verticalLayout->addWidget(log);

        btn_log_clear = new QPushButton(centralwidget);
        btn_log_clear->setObjectName(QString::fromUtf8("btn_log_clear"));

        verticalLayout->addWidget(btn_log_clear);


        verticalLayout_2->addLayout(verticalLayout);

        UDPSimulation->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UDPSimulation);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        UDPSimulation->setMenuBar(menubar);
        statusbar = new QStatusBar(UDPSimulation);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        UDPSimulation->setStatusBar(statusbar);

        retranslateUi(UDPSimulation);

        QMetaObject::connectSlotsByName(UDPSimulation);
    } // setupUi

    void retranslateUi(QMainWindow *UDPSimulation)
    {
        UDPSimulation->setWindowTitle(QApplication::translate("UDPSimulation", "UDPSimulation", nullptr));
        input_label->setText(QApplication::translate("UDPSimulation", "input", nullptr));
        multiple_send_btn->setText(QApplication::translate("UDPSimulation", "Send multiple message ", nullptr));
        join_btn_user_1->setText(QApplication::translate("UDPSimulation", "join", nullptr));
        join_btn_user_2->setText(QApplication::translate("UDPSimulation", "join", nullptr));
        join_btn_user_3->setText(QApplication::translate("UDPSimulation", "join", nullptr));
        join_btn_user_4->setText(QApplication::translate("UDPSimulation", "join", nullptr));
        join_btn_user_5->setText(QApplication::translate("UDPSimulation", "join", nullptr));
        quit_btn_user_1->setText(QApplication::translate("UDPSimulation", "quit", nullptr));
        quit_btn_user_2->setText(QApplication::translate("UDPSimulation", "quit", nullptr));
        quit_btn_user_3->setText(QApplication::translate("UDPSimulation", "quit", nullptr));
        quit_btn_user_4->setText(QApplication::translate("UDPSimulation", "quit", nullptr));
        quit_btn_user_5->setText(QApplication::translate("UDPSimulation", "quit", nullptr));
        label_ID->setText(QApplication::translate("UDPSimulation", "user ID", nullptr));
        check_box_user_1->setText(QApplication::translate("UDPSimulation", "send", nullptr));
        check_box_user_2->setText(QApplication::translate("UDPSimulation", "send", nullptr));
        check_box_user_3->setText(QApplication::translate("UDPSimulation", "send", nullptr));
        check_box_user_4->setText(QApplication::translate("UDPSimulation", "send", nullptr));
        check_box_user_5->setText(QApplication::translate("UDPSimulation", "send", nullptr));
        log_label->setText(QApplication::translate("UDPSimulation", "Log", nullptr));
        btn_log_clear->setText(QApplication::translate("UDPSimulation", "clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UDPSimulation: public Ui_UDPSimulation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDPSIMULATION_H
