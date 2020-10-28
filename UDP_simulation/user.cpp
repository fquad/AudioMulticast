#include "user.h"

#include<QDebug>
#include<QTimer>

User::User(int i_id):
    m_id(i_id), m_count_call_tout(0),
    m_timer(new QTimer(this))
{
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout_send_name()));
    m_timer->start(1000);
}

User::~User()
{}

void User::connect_user(User* i_user)
{
    connect(this, SIGNAL(send_to_slot(QString&)),
            i_user, SLOT(receive(QString&)));
}

void User::disconnect_from_all()
{
    disconnect(this, nullptr, nullptr, nullptr);
}

void User::timeout_send_name()
{
    //qDebug() << QString::number(m_id) + QString::number(MSG_TYPE::UPDATE_NAME);
    m_count_call_tout++;

    QString t_name = QString::number(m_id);
    send(User::MSG_TYPE::UPDATE_NAME, t_name);

    if(m_count_call_tout == 2)
    {
        qDebug() << '(' << m_id << ')';
        qDebug() << "----------------------------------------";
        //check if a value was not updated
        for(QString key : m_connected_user.keys())
        {
            qDebug() << key;

            if(m_connected_user[key] == m_last_count[key])
            {
                m_connected_user.remove(key);
                m_last_count.remove(key);
            }
        }
        qDebug() << "----------------------------------------\n\n";

        for(QString user : m_connected_user.keys())
            m_last_count[user] = m_connected_user[user];

        m_count_call_tout = 0;
        emit update_gui_list(this);
    }
}

void User::receive(QString& i_msg)
{
    //qDebug() << i_msg << m_id;

    int t_type = i_msg.mid(0,1).toInt();
    QString t_msg = i_msg.mid(1,-1);

    switch(t_type)
    {
    case MSG_TYPE::UPDATE_NAME:
    {
        QString t_user_to_add = t_msg.mid(0,3);

        if(!m_connected_user.contains(t_user_to_add))
        {
            m_connected_user[t_user_to_add] = 1;
            m_last_count[t_user_to_add] = 0;

            QString user_to_update = QString::number(m_id);

            emit update_gui_list(this);
        } else
        {
            m_connected_user[t_user_to_add]++;
        }

        break;
    }
    case MSG_TYPE::MSG:
        qDebug() << t_msg;
        break;
    }
}

void User::send(int i_type, QString& i_msg)
{
    QString t_msg_to_users = QString::number(i_type) + i_msg;

    switch(i_type)
    {
    case MSG_TYPE::UPDATE_NAME:
        emit send_to_slot(t_msg_to_users);
        break;

    case MSG_TYPE::MSG:
        emit send_to_server(m_id, i_msg);
        break;

    }
}
