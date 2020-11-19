#include "multicast.h"

#include "user.h"

Multicast::Multicast(User* i_user):
    m_user(i_user), m_id(m_user->get_id()),
    m_timer_count(0)
{
    connect(&m_socket, SIGNAL(new_packet_ready(QByteArray&)),
            m_user, SLOT(receive(QByteArray&)));
}

void Multicast::reproduce_audio(QByteArray i_audio_data)
{
    //play the received audio on the speakers

    //test version with text messages
    quint8 id = i_audio_data.at(0);
    QString str = QString::number(m_id)
            + " : received from"
            +  QString::number(id)
            + " > "
            + i_audio_data.mid(1,-1);

    qDebug() << "received audio : " << i_audio_data;
}

void Multicast::send_audio()
{
    //capture audio from the microphone and send it

    //test version with text messages
    QByteArray audio_data;
    audio_data.append(m_id);

    //m_audio_interface.start_input();
    // --------------------------------------------------


    //send(MSG_TYPE::AUDIO, audio_data);


    //qDebug() << "received audio : " << audioData;
}

void Multicast::send_RTS()
{
    //send a request to start sending audio
    QByteArray msg;
    msg.append(m_id);

    qDebug() << m_id
             << "want to send";

    send(MSG_TYPE::REQUEST, msg);
}

void Multicast::update_user(QByteArray& i_user_name)
{
    /*update the list with all users present in the group by checking
    * if the received id is in the list or not
    */
    quint8 id = i_user_name.at(0);

    if(!m_connected_user->contains(id))
    {
        //user id is not in the users list
        (*m_connected_user)[id] = 1;
        m_connected_user_prev[id] = 0;

        emit m_user->update_gui_list();

    } else
    {
        //user is already in the users list
        m_connected_user_prev[id]++;
    }
}

void Multicast::check_list()
{
    //qDebug() << '(' << m_id << ')';
    //qDebug() << "----------------------------------------";

    //check if a value was not updated
    for(quint8 key : m_connected_user->keys())
    {
        if((*m_connected_user)[key] == m_connected_user_prev[key])
        {
            m_connected_user->remove(key);
            m_connected_user_prev.remove(key);

            emit m_user->update_gui_list();
        }
        //else qDebug() << key;
    }

    //qDebug() << "----------------------------------------\n\n";

    m_connected_user_prev = *m_connected_user;
}

void Multicast::send_user_id()
{
    //qDebug() << QString::number(m_id) << " sent is id";
    QByteArray msg;
    msg.append(m_id);
    send(MSG_TYPE::UPDATE_NAME, msg);
}

void Multicast::answer_RTS(bool i_answer, QByteArray i_requester_id)
{
    // answer to the received request to send
    //TODO errore non bisogna inviare m_id ma l'id di chi ha fatto la richiesta

    //check if the id of the user who made the request is valid
    quint8 r_id = i_requester_id.at(0);

    if(r_id > 0 && r_id < 255)
    {

        qDebug() << QString::number(m_id)
                 << " answered : "
                 << QString::number(i_answer)
                 << " to : "
                 << i_requester_id;

        QByteArray msg;

        msg.append(m_id);
        msg.append(r_id);
        msg.append(i_answer);

        send(MSG_TYPE::ANSWER, msg);

    }
}

bool Multicast::evaluate_list()
{
    /* evaluate the lists created in the T intervall to check if
     * the user is able to send or not
     */

    int n_sender = m_request_list.size() + 1;
    int n_user = m_connected_user->size() + 1;
    int n_answer =  m_answer_list.size();
    int n_permission = 0;

    for(int i = 0; i < n_answer; i++)
    {
        if(m_answer_list.at(i) == 1)
        {
            n_permission++;
        }
    }
    qDebug() << m_id << " is evaluating his list";
    qDebug() << "---------------";
    qDebug() << "   n sender    : " + QString::number(n_sender);
    qDebug() << "   n answer    : " + QString::number(n_answer);
    qDebug() << "   n permission: " + QString::number(n_permission);
    qDebug() << "   n user      : " + QString::number(n_user);

    if((n_user - 1) < 1)
    {
        //No one in the group
        qDebug() << "permission denied";
        qDebug() << "---------------";
        return false;
    }

    if( 1 / n_sender  <= n_permission / (n_user - 1) )
    {
        qDebug() << "permission granted";
        qDebug() << "---------------";
        send_audio();
        return true;
    }

    qDebug() << "permission denied";
    qDebug() << "---------------";

    return false;
}

void Multicast::add_RTS(QByteArray i_data)
{
    //add the received Request To Send to the list with all the requests

    quint8 id = i_data.at(0);
    qDebug() << m_id
             << " added: "
             << id
             << " to request to list";

    m_request_list.append(id);
}

void Multicast::add_answer_to_list(QByteArray i_data)
{
    // add the received answer the the lists of all answers
    quint8 id = i_data.at(1);
    int answer = i_data.at(2);

    // check that the asnwer is to the user request
    if(id == m_id)
    {
        m_answer_list.append(answer);

        qDebug() << m_id
                 << " added answer to list with value: "
                 << answer;
    }
}

void Multicast::clear_request_list()
{
    m_request_list.clear();
}

void Multicast::clear_answer_list()
{
    m_answer_list.clear();
}

void Multicast::send(MSG_TYPE i_type, QByteArray data)
{
    // send the given message on a comunication medium
    // currently to the simulated users
    // in the final implementation the message will be sent using the multicast protocol

    QByteArray t_msg_to_users;
    t_msg_to_users.append(i_type);
    t_msg_to_users.append(data);

    m_socket.send(t_msg_to_users, t_msg_to_users.size());
}

void Multicast::connect_to_group()
{
    m_socket.setIP(m_user->get_IP());
    m_socket.setPort(m_user->get_port());
    m_socket.start();
}

void Multicast::disconnect_from_group()
{
    m_socket.close();
}
