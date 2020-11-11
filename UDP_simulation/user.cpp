#include "user.h"

#include<QDebug>
#include<QTimer>

User::User(int i_id):
    m_id(i_id),
    m_count_call_tout(0),
    m_timer(new QTimer(this))
{
    FSM = new priority_ctrl(i_id);
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
    //TODO trovare un modo per non avere m_priority pubblico
    connect(FSM->m_priority, SIGNAL(send_signal(QString&)),
            i_user, SLOT(receive(QString&)));
}

void User::disconnect_from_all()
{
    disconnect(this, nullptr, nullptr, nullptr);
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
        QString t_name = QString::number(m_id);
        FSM->process(EVENT::E_SEND_UPDATE, t_name);
    }
}


void User::PTTpressed(){
    QString msg = "myid:" + QString::number(m_id);
    FSM->process(EVENT::E_REQUEST_SEND, msg);
}

void User::receive(QString& i_msg)
{
    int t_type = i_msg.mid(0,1).toInt();
    QString t_msg = i_msg.mid(1,-1);

    qDebug() << QString::number(m_id)
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

        //    case MSG_TYPE::UPDATE_NAME:
        //    {
        //        QString t_user_to_add = t_msg.mid(0,3);


        //        if(!m_connected_user.contains(t_user_to_add))
        //        {
        //            m_connected_user[t_user_to_add] = 1;
        //            //m_last_count[t_user_to_add] = 0;

        //            QString user_to_update = QString::number(m_id);

        //            emit update_gui_list(this);
        //        } else
        //        {
        //            m_connected_user[t_user_to_add]++;
        //        }
        //        break;
        //    }

    case priority::MSG_TYPE::REQUEST:
        FSM->process(EVENT::E_RECV_REQUEST, t_msg);
        break;

    case priority::MSG_TYPE::AUDIO:
        FSM->process(EVENT::E_RECV_AUDIO_DATA, t_msg);
        break;
    }
}
