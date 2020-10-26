#include "udpsimulation.h"
#include "ui_udpsimulation.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QErrorMessage>

#include "user.h"


/*
 *
 *  BRANCH TEST
 *
 *
 */

UDPSimulation::UDPSimulation(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::UDPSimulation),
      m_err_msg(new QErrorMessage(this)), m_count_user(0)
{
    ui->setupUi(this);
}

UDPSimulation::~UDPSimulation()
{
    for(User* user : m_user_list)
        delete user;
    delete ui;
}


void UDPSimulation::on_user_1_join_btn_clicked()
{
    if(is_join_flag[0])
    {
        int t_id = ui->input_id_user_1->value();

        ui->input_id_user_1->setEnabled(false);
        ui->quit_btn_user_1->setEnabled(true);

        ui->join_btn_user_1->setText(QString("send"));

        User* t_user = new User(t_id);

        if(m_server.join(t_user))
        {
            m_user_list[QString::number(t_id)] = t_user;
            m_count_user++;
        } else
        {
            delete t_user;
            QString t_msg = "The selected ID is already used";
            m_err_msg->showMessage(t_msg);
        }

        is_join_flag[0] = false;
    }else
    {
        QString msg = ui->input_msg->text();

    }

}

void UDPSimulation::on_user_2_join_btn_clicked()
{
    int t_id = ui->input_id_user_1->value();

    ui->input_id_user_1->setEnabled(false);
    ui->quit_btn_user_1->setEnabled(true);

    ui->join_btn_user_1->setText(QString("send"));

    User* t_user = new User(t_id);

    if(m_server.join(t_user))
    {
        m_user_list[QString::number(t_id)] = t_user;
        m_count_user++;
    } else
    {
        delete t_user;
        QString t_msg = "The selected ID is already used";
        m_err_msg->showMessage(t_msg);
    }
}

void UDPSimulation::on_user_3_join_btn_clicked()
{
    int t_id = ui->input_id_user_1->value();

    ui->input_id_user_1->setEnabled(false);
    ui->quit_btn_user_1->setEnabled(true);

    ui->join_btn_user_1->setText(QString("send"));

    User* t_user = new User(t_id);

    if(m_server.join(t_user))
    {
        m_user_list[QString::number(t_id)] = t_user;
        m_count_user++;
    } else
    {
        delete t_user;
        QString t_msg = "The selected ID is already used";
        m_err_msg->showMessage(t_msg);
    }
}

void UDPSimulation::on_user_4_join_btn_clicked()
{
    int t_id = ui->input_id_user_1->value();

    ui->input_id_user_1->setEnabled(false);
    ui->quit_btn_user_1->setEnabled(true);

    ui->join_btn_user_1->setText(QString("send"));

    User* t_user = new User(t_id);

    if(m_server.join(t_user))
    {
        m_user_list[QString::number(t_id)] = t_user;
        m_count_user++;
    } else
    {
        delete t_user;
        QString t_msg = "The selected ID is already used";
        m_err_msg->showMessage(t_msg);
    }
}

void UDPSimulation::on_user_5_join_btn_clicked()
{
    int t_id = ui->input_id_user_1->value();

    ui->input_id_user_1->setEnabled(false);
    ui->quit_btn_user_1->setEnabled(true);

    ui->join_btn_user_1->setText(QString("send"));

    User* t_user = new User(t_id);

    if(m_server.join(t_user))
    {
        m_user_list[QString::number(t_id)] = t_user;
        m_count_user++;
    } else
    {
        delete t_user;
        QString t_msg = "The selected ID is already used";
        m_err_msg->showMessage(t_msg);
    }
}

void UDPSimulation::on_quit_btn_user_1_clicked()
{
    QString t_id = ui->input_id_user_1->text();
    m_server.exit(m_user_list[t_id]);
    delete m_user_list[t_id];
    m_user_list.remove(t_id);
}

void UDPSimulation::on_quit_btn_user_2_clicked()
{
    QString t_id = ui->input_id_user_1->text();
    m_server.exit(m_user_list[t_id]);
    delete m_user_list[t_id];
    m_user_list.remove(t_id);
}

void UDPSimulation::on_quit_btn_user_3_clicked()
{
    QString t_id = ui->input_id_user_1->text();
    m_server.exit(m_user_list[t_id]);
    delete m_user_list[t_id];
    m_user_list.remove(t_id);
}

void UDPSimulation::on_quit_btn_user_4_clicked()
{
    QString t_id = ui->input_id_user_1->text();
    m_server.exit(m_user_list[t_id]);
    delete m_user_list[t_id];
    m_user_list.remove(t_id);
}

void UDPSimulation::on_quit_btn_user_5_clicked()
{
    QString t_id = ui->input_id_user_1->text();
    m_server.exit(m_user_list[t_id]);
    delete m_user_list[t_id];
    m_user_list.remove(t_id);
}
