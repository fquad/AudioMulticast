#include "user.h"

#include<QDebug>
#include<QTimer>


User::User(int i_id):
    m_id(i_id),
    m_count_call_tout(0),
    m_timer(new QTimer(this))
{
    m_FSM = new MulticastCtrl(this);
    m_FSM->set_user_list(&m_connected_user);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout_send_name()));
    m_timer->start(1000);
}

User::~User()
{
    delete m_FSM;
}

bool User::join_group(QHostAddress& i_IP, quint16 i_port)
{
    m_IP = i_IP;
    m_port = i_port;

    m_FSM->process(EVENT::E_CONNECT);

    return true;
}

bool User::quit_group()
{
    disconnect(this, nullptr, nullptr, nullptr);
    m_FSM->process(EVENT::E_DISCONNECT);

    return true;
}

void User::timeout_send_name()
{
    m_count_call_tout++;

    if(m_count_call_tout == 2)
    {
        //check every 2 second the list to control if someone has left
        m_FSM->process(EVENT::E_CHECK_LIST);

        m_count_call_tout = 0;
        //used to update the GUI list ( only present in simulation)
        //emit update_gui_list(this);
    } else
    {
        //send every 1 second the user id for updating the list
        QByteArray t_name = QByteArray::number(m_id);
        m_FSM->process(EVENT::E_SEND_UPDATE, t_name);
    }
}

void User::PTT_pressed()
{
    m_FSM->process(EVENT::E_REQUEST_SEND);
}

void User::PTT_released()
{
    m_FSM->process(EVENT::E_STOP_SEND);
}

bool User::get_is_sending()
{
    return  m_FSM->get_is_sending();
}

void User::receive(QByteArray& i_msg)
{
    //int t_type = i_msg.mid(0,1).toInt();
    int t_type = i_msg.at(0);
    QByteArray t_msg = i_msg.mid(1,-1);

    if(t_msg.at(0) != m_id)
    {
        qDebug() << m_id
                 << "received type: "
                 << i_msg.mid(0,1)
                 << " msg: "
                 << i_msg.mid(1,-1);

        switch(t_type)
        {
        case Multicast::MSG_TYPE::UPDATE_NAME:
            m_FSM->process(EVENT::E_RECV_UPDATE, t_msg);
            break;

        case Multicast::MSG_TYPE::MSG:
            qDebug() << "msg "<<  t_msg;
            break;

        case Multicast::MSG_TYPE::ANSWER:
            m_FSM->process(EVENT::E_ANSWER_TO_RTS, t_msg);
            break;

        case Multicast::MSG_TYPE::REQUEST:
            m_FSM->process(EVENT::E_RECV_REQUEST, t_msg);
            break;

        case Multicast::MSG_TYPE::AUDIO:
            m_FSM->process(EVENT::E_RECV_AUDIO_DATA, t_msg);
            break;
        }
    }
}