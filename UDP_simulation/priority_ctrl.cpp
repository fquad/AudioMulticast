#include "priority_ctrl.h"
#include "priority.h"


priority_ctrl::priority_ctrl(int id, UDPSimulation *w) :
  m_priority(new priority(id, w)),
  m_current_state(state_nogroup),
  m_is_sending(false),
  m_ingroup(false)
{
    //connect the timers to their callback
    connect(&rts_timer, SIGNAL(timeout()), this, SLOT(rts_timeout()));
    connect(&cts_timer, SIGNAL(timeout()), this, SLOT(cts_timeout()));
}

priority_ctrl::~priority_ctrl()
{
    delete m_priority;
    qDebug() << "FSM deleted";
}

void priority_ctrl::set_user_list(QMap<QString, int>* i_user_list_ptr)
{
    m_priority->set_user_list(i_user_list_ptr);
}

void priority_ctrl::process(EVENT i_e, QString i_data)
{

    if(m_ingroup == true){
        if(i_e == EVENT::E_CHECK_LIST)
        {
            m_priority->check_list();
            return;
        }

        if(i_e == EVENT::E_RECV_UPDATE)
        {
            m_priority->update_users_list(i_data);
            return;
        }

        if(i_e == EVENT::E_SEND_UPDATE)
        {
            m_priority->send_user_id();
            return;
        }
        if(i_e == EVENT::E_DISCONNECT){
            qDebug() << "disconnect";
            m_priority->disconnect_from_group();
            m_current_state = State::state_nogroup;
            m_ingroup = false;
            return;
        }
    }



    switch (m_current_state)
    {

        case state_nogroup:
            if(i_e == EVENT::E_CONNECT){
                // user connect to the group
                qDebug() << "connected";
                m_priority->connect_to_group();
                m_current_state = State::state_idle;
                m_ingroup = true;
            }
        break;

        case state_idle:
            //qDebug() << QString::number(m_priority->getId()) <<   " FSM state: state_idle";
            //TODO chage E_REQUEST_SEND in E_SEND_REQUEST

            if(i_e == EVENT::E_REQUEST_SEND)
            {
                //PTT button pressed
                m_current_state = State::state_rts;
                m_priority->send_RTS();

                //state_rts entry Point
                rts_timer.setSingleShot(true);
                rts_timer.start(t_timeout);

                break;

            } else if(i_e == EVENT::E_RECV_AUDIO_DATA)
            {
                //Audio data packet received
                m_priority->reproduce_audio(i_data);
                break;

            } else if(i_e == EVENT::E_RECV_REQUEST)
            {
                //Received a request to send from another user
                m_current_state = State::state_cts;

                // state_cts entry Point
                cts_timer.setSingleShot(true);
                cts_timer.start(t_timeout);

                m_priority->answer_RTS(true, i_data);

                break;

            }
        break;

        case state_cts:
            //qDebug() << QString::number(m_priority->getId()) <<   " FSM state: state_cts";

            //JUST FOR SIMULATION PURPOSE
            if(i_e == EVENT::E_REQUEST_SEND)
            {
                //PTT button pressed
                m_current_state = State::state_rts;
                m_priority->send_RTS();

                //state_rts entry Point
                rts_timer.setSingleShot(true);
                rts_timer.start(t_timeout);

                break;

            }
            //END JUST FOR SIMULATION PURPOSE


            if(i_e == EVENT::E_RECV_REQUEST)
            {
                //Received a request of sending from another user
                m_priority->answer_RTS(false, i_data);
                break;

            } else if(i_e == EVENT::E_RECV_AUDIO_DATA)
            {
                //Audio data packet received
                m_priority->reproduce_audio(i_data);
                break;

            }
        break;

        case state_rts:

            //qDebug() << QString::number(m_priority->getId()) <<   " FSM state: state_rts";

            if(i_e == EVENT::E_RECV_REQUEST)
            {
                //Received a request to send from another user
                m_priority->answer_RTS(false, i_data);
                m_priority->add_RTS(i_data);
                break;

            } else if(i_e == EVENT::E_ANSWER_TO_RTS)
            {
                //received an answer to a request to send
                m_priority->add_answer_to_list(i_data);
                break;

            } else if(i_e == EVENT::E_RECV_AUDIO_DATA)
            {
                //Audio data packet received
                m_priority->reproduce_audio(i_data);

                //someone is already transmitting
                m_current_state = State::state_idle;
                rts_timer.stop();
                break;
            }
        break;

        case state_sending:

            //qDebug() << QString::number(m_priority->getId()) <<  " FSM state: state_sending";

            if(i_e == EVENT::E_STOP_SEND)
            {
                //PTT button released
                m_current_state = State::state_idle;
                m_is_sending = false;
                break;

            } else if(i_e == EVENT::E_SEND_AUDIO_DATA)
            {
                //audio data available to be sent
                m_priority->send_audio();
                break;
            }
        break;
    }
}

bool priority_ctrl::get_is_sending(){
    return m_is_sending;
}


void priority_ctrl::rts_timeout()
{
    qDebug() << QString::number(m_priority->getId()) <<   " rts_timeout";
    bool answer = m_priority->evaluate_list();

    if(answer)
    {
        //qDebug() << "permission_confirmed";
        m_current_state = State::state_sending;
        m_is_sending = true;
    } else
    {
        //qDebug() << "permission_denied";
        m_current_state = State::state_idle;
    }

    m_priority->clear_request_list();
    m_priority->clear_answer_list();
}

void priority_ctrl::cts_timeout()
{
    qDebug() << QString::number(m_priority->getId()) <<  " cts_timeout";
    m_current_state = State::state_idle;
    m_priority->clear_request_list();
}

