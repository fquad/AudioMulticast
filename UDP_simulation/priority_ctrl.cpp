#include "priority_ctrl.h"
#include "priority.h"


priority_ctrl::priority_ctrl(int id) :
  m_priority(new priority(id)), m_current_state(state_idle)
{}

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
    if(i_e == EVENT::E_RECV_UPDATE)
    {
        m_priority->update_list(i_data);
    }

    switch (m_current_state)
    {
        case state_idle:
            qDebug() << "FSM state: state_idle";

            if(i_e == EVENT::E_SEND)
            {
                //PTT button pressed
                m_current_state = State::state_rts;
                m_priority->send_RTS(i_data);

                //state_rts entry Point
                rts_timer.setSingleShot(true);

                connect(&rts_timer, SIGNAL(timeout()), this, SLOT(rts_timeout()));
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
                connect(&rts_timer, SIGNAL(timeout()), this, SLOT(rts_timeout()));
                cts_timer.start(t_timeout);

                m_priority->answer_RTS(i_data,true);

                break;

            }
        break;

        case state_cts:
            qDebug() << "FSM state: state_cts";

            if(i_e == EVENT::E_RECV_REQUEST)
            {
                //Received a request of sending from another user
                m_priority->answer_RTS(i_data,false);
                break;

            } else if(i_e == EVENT::E_RECV_AUDIO_DATA)
            {
                //Audio data packet received
                m_priority->reproduce_audio(i_data);
                break;

            }
        break;

        case state_rts:

            qDebug() << "FSM state: state_rts";

            if(i_e == EVENT::E_RECV_REQUEST)
            {
                //Received a request to send from another user
                m_priority->answer_RTS(i_data,false);
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

            qDebug() << "FSM state: state_sending";

            if(i_e == EVENT::E_STOP_SEND)
            {
                //PTT button released
                m_current_state = State::state_idle;
                break;

            } else if(i_e == EVENT::E_SEND_AUDIO_DATA)
            {
                //audio data available to be sent
                m_priority->send_audio(i_data);
                break;
            }
        break;

        default:
        break;
    }
}

void priority_ctrl::rts_timeout()
{
    qDebug() << "rts_timeout";
    bool answer = m_priority->evaluate_list();

    if(answer)
    {
        qDebug() << "permission_confirmed";
        m_current_state = State::state_sending;
    } else
    {
        qDebug() << "permission_denied";
        m_current_state = State::state_idle;
    }

    m_priority->clear_request_list();
    m_priority->clear_answer_list();
}

void priority_ctrl::cts_timeout()
{
    qDebug() << "cts_timeout";

    m_current_state = State::state_idle;
    m_priority->clear_request_list();
}

