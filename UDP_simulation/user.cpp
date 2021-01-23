#include "user.h"

#include<QDebug>
#include<QTimer>


User::User(int i_id, UDPSimulation *w):
    m_id(i_id),
    m_count_call_tout(0),
    m_timer(new QTimer(this))
{
    FSM = new priority_ctrl(i_id, w);
    FSM->set_user_list(&m_connected_user);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout_send_name()));
    m_timer->start(1000);
}

User::~User()
{
    delete FSM;
}

void User::connect_user(User* i_user)
{
    //TODO just needed in the simulation enviroment
    connect(FSM->m_priority, SIGNAL(send_signal(QByteArray&)),
            i_user, SLOT(receive(QByteArray&)));
    FSM->process(EVENT::E_CONNECT);
}

void User::disconnect_from_all()
{
    disconnect(this, nullptr, nullptr, nullptr);
    FSM->process(EVENT::E_DISCONNECT);
}

void User::timeout_send_name()
{
    m_count_call_tout++;

    if(m_count_call_tout == 2)
    {
        //check every 2 second the list to control if someone has left
        FSM->process(EVENT::E_CHECK_LIST);

        m_count_call_tout = 0;
        //used to update the GUI list ( only present in simulation)
        emit update_gui_list(this);
    }else{
        //send every 1 second the user id for updating the list
        QByteArray t_name = QByteArray::number(m_id);
        FSM->process(EVENT::E_SEND_UPDATE, t_name);
    }
}


void User::PTTpressed(){
    FSM->process(EVENT::E_REQUEST_SEND);
}

void User::PTTreleased(){
    FSM->process(EVENT::E_STOP_SEND);
}

bool User::get_is_sending(){
    return  FSM->get_is_sending();
}

void User::receive(QByteArray& i_msg)
{
    //int t_type = i_msg.mid(0,1).toInt();
    int t_type = i_msg.at(0);

    QByteArray t_msg = i_msg.mid(1,-1);

    qDebug() << m_id
             << "received type: "
             << i_msg.mid(0,1)
             << " msg: "
             << i_msg.mid(1,-1);

    switch(t_type)
    {

    case priority::MSG_TYPE::UPDATE_NAME:
        FSM->process(EVENT::E_RECV_UPDATE, t_msg);
        break;

    case priority::MSG_TYPE::MSG:
        qDebug() << "msg "<<  t_msg;
        break;

    case priority::MSG_TYPE::ANSWER:
        FSM->process(EVENT::E_ANSWER_TO_RTS, t_msg);
        break;

    case priority::MSG_TYPE::REQUEST:
        FSM->process(EVENT::E_RECV_REQUEST, t_msg);
        break;

    case priority::MSG_TYPE::AUDIO:
        FSM->process(EVENT::E_RECV_AUDIO_DATA, t_msg);
        break;
    }
}
