#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>

//debug
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_user(new User(1))
    , ui(new Ui::MainWindow)
    , m_is_join(true)
{
    ui->setupUi(this);

    ui->gui_IP->setPlaceholderText("example: 111.111.111");

    //DEBUG
    ui->gui_IP->setText("239.255.255.250");
    ui->gui_port->setValue(1900);
    //DEBUG

    ui->gui_internal_state->setReadOnly(true);
    ui->gui_PTT->setEnabled(false);

    connect(m_user, SIGNAL(update_gui_list()), this, SLOT(update_gui_list()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_user;
}

void MainWindow::on_gui_join_clicked()
{
    //get port and IP to join
    QHostAddress IP = QHostAddress(ui->gui_IP->text());
    quint16 port = ui->gui_port->value();

    //check if the user can enter the UDP group
    if (m_user->join_group(IP, port) && m_is_join)
    {

        //the join button changes his text and becomes the quit button
        ui->gui_join->setText("quit");
        //the PTT is now available
        ui->gui_PTT->setEnabled(true);

        ui->gui_IP->setEnabled(false);
        ui->gui_port->setEnabled(false);

    } else
    {
        if (m_user->quit_group())
        {
            //the quit button becomes join button
            ui->gui_join->setText("join");
            ui->gui_PTT->setEnabled(false);

            ui->gui_IP->setEnabled(true);
            ui->gui_port->setEnabled(true);
        }
    }

    m_is_join = !m_is_join;
}

void MainWindow::on_gui_PTT_pressed()
{
    m_user->PTT_pressed();
}

void MainWindow::on_gui_PTT_released()
{
     m_user->PTT_released();
}

void MainWindow::update_gui_list()
{
    ui->gui_connected_user->clear();

    for(quint8 user : m_user->get_connected_user_list().keys())
    {
        ui->gui_connected_user->addItem(QString::number(user));
    }
}
