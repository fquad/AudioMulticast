#include "multicastctrl.h"

#include "multicast.h"
#include "user.h"
#include <QRandomGenerator>

MulticastCtrl::MulticastCtrl(User* i_user) :
  m_multicast(new Multicast(i_user)),
  m_ingroup(false),
  m_is_sending(false),
  m_retry_attemp(0),
  m_state(state_nogroup),
  m_in_group_state(state_idle),
  m_first_time(true)
{
    //connect the timers to their callback
    connect(&m_rts_timer, SIGNAL(timeout()), this, SLOT(rts_timeout()));
    connect(&m_cts_timer, SIGNAL(timeout()), this, SLOT(cts_timeout()));

    connect(&m_select_ID_timer, SIGNAL(timeout()),
            this, SLOT(select_ID_timeout()));

    connect(&m_check_rcvd_audio_data_timer, SIGNAL(timeout()),
            this, SLOT(received_audio_data_timeout()));
}

MulticastCtrl::~MulticastCtrl()
{
    delete m_multicast;
    qDebug() << "FSM deleted";
}

void MulticastCtrl::set_user_list(QMap<quint8, int>* i_user_list_ptr)
{
    m_multicast->set_user_list(i_user_list_ptr);
}

void MulticastCtrl::in_group_process(EVENT i_e, QByteArray* i_data){

    switch (m_in_group_state)
    {
        case state_idle:

            if(i_e == EVENT::E_REQUEST_SEND)
            {
                //PTT button pressed
                m_in_group_state = State::state_rts;
                m_multicast->send_RTS();

                //state_rts entry Point
                m_rts_timer.setSingleShot(true);
                m_rts_timer.start(t_timeout);

                break;

            } else if(i_e == EVENT::E_RECV_AUDIO_DATA)
            {
                //Audio data packet received

                m_multicast->reproduce_audio(*i_data);
                break;

            } else if(i_e == EVENT::E_RECV_REQUEST)
            {
                //Received a request to send from another user
                m_in_group_state = State::state_cts;

                // state_cts entry Point
                m_cts_timer.setSingleShot(true);
                m_cts_timer.start(t_timeout);

                m_multicast->answer_RTS(true, *i_data);

                break;

            }
        break;

        case state_cts:
            if(i_e == EVENT::E_REQUEST_SEND)
            {
                //PTT button pressed
                m_in_group_state = State::state_rts;
                m_multicast->send_RTS();

                //state_rts entry Point
                m_rts_timer.setSingleShot(true);
                m_rts_timer.start(t_timeout);

                break;
            }

            if(i_e == EVENT::E_RECV_REQUEST)
            {
                //Received a request of sending from another user
                m_multicast->answer_RTS(false, *i_data);
                break;

            } else if(i_e == EVENT::E_RECV_AUDIO_DATA)
            {
                //Audio data packet received
                m_multicast->reproduce_audio(*i_data);
                break;

            }
        break;

        case state_rts:
            if(i_e == EVENT::E_RECV_REQUEST)
            {
                //Received a request to send from another user
                m_multicast->answer_RTS(false, *i_data);
                m_multicast->add_RTS(*i_data);
                break;

            } else if(i_e == EVENT::E_ANSWER_TO_RTS)
            {
                //received an answer to a request to send
                m_multicast->add_answer_to_list(*i_data);
                break;

            } else if(i_e == EVENT::E_RECV_AUDIO_DATA)
            {
                // Disable timer to check if no data are received
                m_check_rcvd_audio_data_timer.stop();

                //someone is already transmitting
                m_in_group_state = State::state_idle;
                m_rts_timer.stop();

                //Audio data packet received
                m_multicast->reproduce_audio(*i_data);

                break;
            }
        break;

        case state_sending:
            if(i_e == EVENT::E_STOP_SEND)
            {
                //PTT button released
                m_in_group_state = State::state_idle;
                m_is_sending = false;
                m_multicast->stop_send_audio();
                break;

            }
        break;
    }
}


void MulticastCtrl::process(EVENT i_e, QByteArray* i_data)
{
    switch(m_state){
        case state_nogroup:
            if(i_e == EVENT::E_CONNECT){
                qDebug() << "connecting";
                m_multicast->connect_to_group();
                m_select_ID_timer.setSingleShot(true);
                m_select_ID_timer.start(t_timeout_select_ID);

                m_state = State::state_connecting;

            }
        break;

        case state_connecting:

            if(i_e == EVENT::E_RECV_UPDATE){
                m_multicast->update_user(*i_data);
                return;
            }
            if(i_e == EVENT::E_CHECK_LIST){
                m_multicast->check_list();
                return;
            }
            if(i_e == EVENT::E_DISCONNECT){
                qDebug() << "disconnect";
                m_multicast->disconnect_from_group();
                m_state = State::state_nogroup;
                m_select_ID_timer.stop();
                m_ingroup = false;
                m_first_time = true;
                return;
            }


        break;

        case state_ingroup:
            if(i_e == EVENT::E_RECV_UPDATE){
                m_multicast->update_user(*i_data);
                return;
            }
            if(i_e == EVENT::E_CHECK_LIST){
                m_multicast->check_list();
                return;
            }
            if(i_e == EVENT::E_SEND_UPDATE){
                m_multicast->send_user_id();
                return;
            }

            if(i_e == EVENT::E_DISCONNECT){
                qDebug() << "disconnect";
                m_multicast->disconnect_from_group();
                m_state = State::state_nogroup;
                m_ingroup = false;
                m_first_time = true;
                return;
            }

            in_group_process(i_e, i_data);

        break;
    }
}

bool MulticastCtrl::get_is_sending()
{
    return m_is_sending;
}

void MulticastCtrl::rts_timeout()
{
    qDebug() << " rts_timeout";
    bool answer = m_multicast->evaluate_list();

    if(answer)
    {
        //qDebug() << "permission_confirmed";
        m_in_group_state = State::state_sending;
        m_is_sending = true;
        m_multicast->start_send_audio();

    } else
    {
        if(m_retry_attemp < max_retry_attemp)
        {
            m_retry_attemp++;
            qDebug() <<"retry to send";

        } else
        {
            // max number of attemp reached
            m_retry_attemp = 0;
            m_multicast->clear_request_list();
            m_multicast->clear_answer_list();
            m_in_group_state = State::state_idle;
            m_rts_timer.stop();
            return;
        }

        int random_t = 50 + (QRandomGenerator::global()->generate() % 25); //random number of milliseconds [50, 75]
        m_check_rcvd_audio_data_timer.setSingleShot(true);
        m_check_rcvd_audio_data_timer.start(random_t);

    }

    m_multicast->clear_request_list();
    m_multicast->clear_answer_list();
}

void MulticastCtrl::cts_timeout()
{
    qDebug() << "cts_timeout";
    m_in_group_state = State::state_idle;
    m_multicast->clear_request_list();
}

void MulticastCtrl::select_ID_timeout()
{
    m_multicast->set_user_ID();
    m_in_group_state = State::state_idle;
    m_state = State::state_ingroup;
}

void MulticastCtrl::received_audio_data_timeout()
{
    m_multicast->send_RTS();

    //state_rts entry Point
    m_rts_timer.setSingleShot(true);
    m_rts_timer.start(t_timeout);
}
