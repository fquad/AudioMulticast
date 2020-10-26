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

    QString msg = QString::number(UPDATE_NAME) + QString::number(m_id);
    send(msg);

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
    }
}

void User::receive(QString& i_msg)
{
    //qDebug() << i_msg << m_id;

    int type = i_msg.mid(0,1).toInt();
    QString msg = i_msg.mid(1,-1);

    switch(type)
    {
    case UPDATE_NAME:
        QString user = msg.mid(0,3);

        if(!m_connected_user.contains(user))
        {
            m_connected_user[user] = 1;
            m_last_count[user] = 0;
        } else
        {
            m_connected_user[user]++;
        }

        break;
    }
}

void User::send(QString& i_msg)
{
    emit send_to_slot(i_msg);
}
