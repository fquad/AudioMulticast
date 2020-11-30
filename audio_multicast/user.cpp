#include "user.h"

#include<QDebug>


User::User():
     m_ID(201), m_count_call_tout(0),
    m_in_device(QAudioDeviceInfo::defaultInputDevice()),
    m_out_device(QAudioDeviceInfo::defaultOutputDevice())
{
    m_FSM = new MulticastCtrl(this);
    m_FSM->set_user_list(&m_connected_user);

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

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout_send_name()));
    m_timer.start(1000);

    return true;
}

bool User::quit_group()
{
    m_FSM->process(EVENT::E_DISCONNECT);

    disconnect(&m_timer, nullptr, this, nullptr);

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
        QByteArray t_name = QByteArray::number(m_ID);
        m_FSM->process(EVENT::E_SEND_UPDATE, &t_name);
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
    int t_type = i_msg.at(0);
    int sender_ID = i_msg.at(1);


    QByteArray t_msg = i_msg.mid(1,-1);

    if(sender_ID != m_ID)
    {
        qDebug() << m_ID
                 << "received type: "
                 << i_msg.mid(0,1)
                 << " msg: "
                 << i_msg.mid(1,-1).toHex();

        switch(t_type)
        {
        case Multicast::MSG_TYPE::UPDATE_NAME:
            m_FSM->process(EVENT::E_RECV_UPDATE, &t_msg);
            break;

        case Multicast::MSG_TYPE::MSG:
            qDebug() << "msg "<<  t_msg;
            break;

        case Multicast::MSG_TYPE::ANSWER:
            m_FSM->process(EVENT::E_ANSWER_TO_RTS, &t_msg);
            break;

        case Multicast::MSG_TYPE::REQUEST:
            m_FSM->process(EVENT::E_RECV_REQUEST, &t_msg);
            break;

        case Multicast::MSG_TYPE::AUDIO:
            m_FSM->process(EVENT::E_RECV_AUDIO_DATA, &t_msg);
            break;
        }
    }
}
