#include "udpsimulation.h"
#include "ui_udpsimulation.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QErrorMessage>
#include <QRandomGenerator>

#include "user.h"

#include <QDebug>

UDPSimulation::UDPSimulation(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::UDPSimulation),
      m_err_msg(new QErrorMessage(this)), m_count_user(0)
{
    ui->setupUi(this);

    for(int i = 0; i<N_USER; ++i)
        is_join_flag[i] = true;
}

UDPSimulation::~UDPSimulation()
{
    for(USER_GUI user : m_user_list)
        delete user.m_user;
    delete ui;
}

void UDPSimulation::on_join_btn_user_1_clicked()
{
    if(is_join_flag[0])
    {
        int t_id = ui->input_id_user_1->value();
        User* t_user = new User(t_id);

        if(m_server.join(t_user))
        {
            connect(t_user, SIGNAL(update_gui_list(User*)), this, SLOT(receive_updated_list(User*)));
            connect(t_user, SIGNAL(send_to_server(int, QString&)), this, SLOT(receive_from_users(int, QString&)));

            ui->input_id_user_1->setEnabled(false);
            ui->quit_btn_user_1->setEnabled(true);
            ui->join_btn_user_1->setText(QString("send"));

            m_user_list[QString::number(t_id)].m_user = t_user;
            m_user_list[QString::number(t_id)].m_GUI_id = ui->input_id_user_1;
            m_user_list[QString::number(t_id)].m_GUI_user_list = ui->list_user_1;
            m_user_list[QString::number(t_id)].m_GUI_send_flag = ui->check_box_user_1;

            m_count_user++;
            is_join_flag[0] = false;
        } else
        {
            delete t_user;
            QString t_msg = "The selected ID is already used";
            m_err_msg->showMessage(t_msg);
        }
    } else
    {
        QString msg = ui->input_msg->text();
        m_user_list[QString::number(ui->input_id_user_1->value())].m_user->send(User::MSG_TYPE::MSG, msg);
    }
}

void UDPSimulation::on_join_btn_user_2_clicked()
{
    if(is_join_flag[1])
    {
        int t_id = ui->input_id_user_2->value();
        User* t_user = new User(t_id);

        if(m_server.join(t_user))
        {
            connect(t_user, SIGNAL(update_gui_list(User*)), this, SLOT(receive_updated_list(User*)));
            connect(t_user, SIGNAL(send_to_server(int, QString&)), this, SLOT(receive_from_users(int, QString&)));

            ui->input_id_user_2->setEnabled(false);
            ui->quit_btn_user_2->setEnabled(true);
            ui->join_btn_user_2->setText(QString("send"));

            m_user_list[QString::number(t_id)].m_user = t_user;
            m_user_list[QString::number(t_id)].m_GUI_id = ui->input_id_user_2;
            m_user_list[QString::number(t_id)].m_GUI_user_list = ui->list_user_2;
            m_user_list[QString::number(t_id)].m_GUI_send_flag = ui->check_box_user_2;

            m_count_user++;
            is_join_flag[1] = false;

        } else
        {
            delete t_user;
            QString t_msg = "The selected ID is already used";
            m_err_msg->showMessage(t_msg);

        }
    } else
    {
        QString msg = ui->input_msg->text();
        m_user_list[QString::number(ui->input_id_user_2->value())].m_user->send(User::MSG_TYPE::MSG, msg);
    }
}

void UDPSimulation::on_join_btn_user_3_clicked()
{
    if(is_join_flag[2])
    {
        int t_id = ui->input_id_user_3->value();
        User* t_user = new User(t_id);

        if(m_server.join(t_user))
        {
            connect(t_user, SIGNAL(update_gui_list(User*)), this, SLOT(receive_updated_list(User*)));
            connect(t_user, SIGNAL(send_to_server(int, QString&)), this, SLOT(receive_from_users(int, QString&)));

            ui->input_id_user_3->setEnabled(false);
            ui->quit_btn_user_3->setEnabled(true);
            ui->join_btn_user_3->setText(QString("send"));

            m_user_list[QString::number(t_id)].m_user = t_user;
            m_user_list[QString::number(t_id)].m_GUI_id = ui->input_id_user_3;
            m_user_list[QString::number(t_id)].m_GUI_user_list = ui->list_user_3;
            m_user_list[QString::number(t_id)].m_GUI_send_flag = ui->check_box_user_3;

            m_count_user++;
            is_join_flag[2] = false;
        } else
        {
            delete t_user;
            QString t_msg = "The selected ID is already used";
            m_err_msg->showMessage(t_msg);
        }
    }else
    {
        QString msg = ui->input_msg->text();
        m_user_list[QString::number(ui->input_id_user_3->value())].m_user->send(User::MSG_TYPE::MSG, msg);
    }
}

void UDPSimulation::on_join_btn_user_4_clicked()
{
    if(is_join_flag[3])
    {
        int t_id = ui->input_id_user_4->value();
        User* t_user = new User(t_id);

        if(m_server.join(t_user))
        {
            connect(t_user, SIGNAL(update_gui_list(User*)), this, SLOT(receive_updated_list(User*)));
            connect(t_user, SIGNAL(send_to_server(int, QString&)), this, SLOT(receive_from_users(int, QString&)));

            ui->input_id_user_4->setEnabled(false);
            ui->quit_btn_user_4->setEnabled(true);
            ui->join_btn_user_4->setText(QString("send"));

            m_user_list[QString::number(t_id)].m_user = t_user;
            m_user_list[QString::number(t_id)].m_GUI_id = ui->input_id_user_4;
            m_user_list[QString::number(t_id)].m_GUI_user_list = ui->list_user_4;
            m_user_list[QString::number(t_id)].m_GUI_send_flag = ui->check_box_user_4;

            m_count_user++;
            is_join_flag[3] = false;
        } else
        {
            delete t_user;
            QString t_msg = "The selected ID is already used";
            m_err_msg->showMessage(t_msg);
        }
    }else
    {
        QString msg = ui->input_msg->text();
        m_user_list[QString::number(ui->input_id_user_4->value())].m_user->send(User::MSG_TYPE::MSG, msg);
    }
}

void UDPSimulation::on_join_btn_user_5_clicked()
{
    if(is_join_flag[4])
    {
        int t_id = ui->input_id_user_5->value();
        User* t_user = new User(t_id);

        if(m_server.join(t_user))
        {
            connect(t_user, SIGNAL(update_gui_list(User*)), this, SLOT(receive_updated_list(User*)));
            connect(t_user, SIGNAL(send_to_server(int, QString&)), this, SLOT(receive_from_users(int, QString&)));

            ui->input_id_user_5->setEnabled(false);
            ui->quit_btn_user_5->setEnabled(true);
            ui->join_btn_user_5->setText(QString("send"));

            m_user_list[QString::number(t_id)].m_user = t_user;
            m_user_list[QString::number(t_id)].m_GUI_id = ui->input_id_user_5;
            m_user_list[QString::number(t_id)].m_GUI_user_list = ui->list_user_5;
            m_user_list[QString::number(t_id)].m_GUI_send_flag = ui->check_box_user_5;

            m_count_user++;
            is_join_flag[4] = false;
        } else
        {
            delete t_user;
            QString t_msg = "The selected ID is already used";
            m_err_msg->showMessage(t_msg);
        }
    } else // when it becomes send button
    {
        QString msg = ui->input_msg->text();
        m_user_list[QString::number(ui->input_id_user_5->value())].m_user->send(User::MSG_TYPE::MSG, msg);
    }
}

void UDPSimulation::on_quit_btn_user_1_clicked()
{
    QString t_id = ui->input_id_user_1->text();

    ui->input_id_user_1->setValue(0);
    ui->list_user_1->clear();
    ui->quit_btn_user_1->setEnabled(false);
    ui->input_id_user_1->setEnabled(true);
    ui->join_btn_user_1->setEnabled(false);
    ui->join_btn_user_1->setEnabled(false);
    ui->join_btn_user_1->setText("join");

    is_join_flag[0] = true;

    m_server.exit(m_user_list[t_id].m_user);
    delete m_user_list[t_id].m_user;
    m_user_list.remove(t_id);
}

void UDPSimulation::on_quit_btn_user_2_clicked()
{
    QString t_id = ui->input_id_user_2->text();

    ui->input_id_user_2->setValue(0);
    ui->list_user_2->clear();
    ui->quit_btn_user_2->setEnabled(false);
    ui->input_id_user_2->setEnabled(true);
    ui->join_btn_user_2->setEnabled(false);
    ui->join_btn_user_2->setEnabled(false);
    ui->join_btn_user_2->setText("join");

    is_join_flag[1] = true;

    m_server.exit(m_user_list[t_id].m_user);
    delete m_user_list[t_id].m_user;
    m_user_list.remove(t_id);
}

void UDPSimulation::on_quit_btn_user_3_clicked()
{
    QString t_id = ui->input_id_user_3->text();

    ui->input_id_user_3->setValue(0);
    ui->list_user_3->clear();
    ui->quit_btn_user_3->setEnabled(false);
    ui->input_id_user_3->setEnabled(true);
    ui->join_btn_user_3->setEnabled(false);
    ui->join_btn_user_3->setEnabled(false);
    ui->join_btn_user_3->setText("join");

    is_join_flag[2] = true;

    m_server.exit(m_user_list[t_id].m_user);
    delete m_user_list[t_id].m_user;
    m_user_list.remove(t_id);
}

void UDPSimulation::on_quit_btn_user_4_clicked()
{
    QString t_id = ui->input_id_user_4->text();

    ui->input_id_user_4->setValue(0);
    ui->list_user_4->clear();
    ui->quit_btn_user_4->setEnabled(false);
    ui->input_id_user_4->setEnabled(true);
    ui->join_btn_user_4->setEnabled(false);
    ui->join_btn_user_4->setEnabled(false);
    ui->join_btn_user_4->setText("join");

    is_join_flag[4] = true;

    m_server.exit(m_user_list[t_id].m_user);
    delete m_user_list[t_id].m_user;
    m_user_list.remove(t_id);
}

void UDPSimulation::on_quit_btn_user_5_clicked()
{
    QString t_id = ui->input_id_user_5->text();

    ui->input_id_user_5->setValue(0);
    ui->list_user_5->clear();
    ui->quit_btn_user_5->setEnabled(false);
    ui->input_id_user_5->setEnabled(true);
    ui->join_btn_user_5->setEnabled(false);
    ui->join_btn_user_5->setEnabled(false);
    ui->join_btn_user_5->setText("join");

    is_join_flag[4] = true;

    m_server.exit(m_user_list[t_id].m_user);
    delete m_user_list[t_id].m_user;
    m_user_list.remove(t_id);
}

void UDPSimulation::on_input_id_user_1_valueChanged(int arg1)
{
    ui->join_btn_user_1->setEnabled(true);
}

void UDPSimulation::on_input_id_user_2_valueChanged(int arg1)
{
    ui->join_btn_user_2->setEnabled(true);
}

void UDPSimulation::on_input_id_user_3_valueChanged(int arg1)
{
    ui->join_btn_user_3->setEnabled(true);
}

void UDPSimulation::on_input_id_user_4_valueChanged(int arg1)
{
    ui->join_btn_user_4->setEnabled(true);
}

void UDPSimulation::on_input_id_user_5_valueChanged(int arg1)
{
    ui->join_btn_user_5->setEnabled(true);
}

void UDPSimulation::receive_updated_list(User* i_user)
{
    qDebug() << 1;
    USER_GUI t_user = m_user_list[QString::number(i_user->get_id())];

    t_user.m_GUI_user_list->clear();

    for(QString user : t_user.m_user->get_connected_user_list().keys())
    {
        t_user.m_GUI_user_list->addItem(user);
    }
}

void UDPSimulation::receive_from_users(int i_id, QString& i_string)
{
    QString msg = QString("[server]: from (") + QString::number(i_id) + QString(") ") + i_string;
    ui->log->append(msg);
}

void UDPSimulation::on_multiple_send_btn_clicked()
{
    QList<User*> t_user_list;
    QList<User*> t_sorted_user_list;

    for(USER_GUI el : m_user_list)
        if(Qt::CheckState::Checked == el.m_GUI_send_flag->checkState())
        {
            t_user_list.append(el.m_user);
            t_sorted_user_list.append(nullptr);
        }

    for(User* el : t_user_list)
    {
          int t_rnd_index = QRandomGenerator::global()->generate() % t_sorted_user_list.size();

          while(t_sorted_user_list.at(t_rnd_index) != nullptr)
          {
              t_rnd_index = QRandomGenerator::global()->generate() % t_sorted_user_list.size();
          }
          t_sorted_user_list[t_rnd_index] = el;
    }
    QString msg = ui->input_msg->text();
    for(User* user : t_sorted_user_list)
        user->send(User::MSG_TYPE::MSG, msg);

}

void UDPSimulation::on_btn_log_clear_clicked()
{
    ui->log->clear();
}
