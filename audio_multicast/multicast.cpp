#include "multicast.h"

#include "user.h"

Multicast::Multicast(User* i_user):
    m_user(i_user), m_id(m_user->get_ID()),
    m_timer_count(0)
{
    connect(&m_socket, SIGNAL(new_packet_ready(QByteArray&)),
            m_user, SLOT(receive(QByteArray&)));

    connect(&m_audio_interface, SIGNAL(data_ready(QByteArray&)),
            this, SLOT(data_audio_ready(QByteArray&)));
}

void Multicast::data_audio_ready(QByteArray& i_data_audio)
{
    QByteArray audio_data;
    audio_data.append(m_id);
    audio_data.append(i_data_audio);

    //qDebug() << i_data_audio;
    send(MSG_TYPE::AUDIO, audio_data);
}

void Multicast::reproduce_audio(QByteArray i_audio_data)
{
    //play the received audio on the speakers

    quint8 id = i_audio_data.at(0);
    QByteArray audio_data = i_audio_data.mid(1,-1);

//    qDebug() << QString::number(m_id)
//            + " : received from"
//            +  QString::number(id)
//            + " > "
//            + audio_data;

    m_audio_interface.audio_reproduce_audio(i_audio_data);
}

void Multicast::start_send_audio()
{
    //capture audio from the microphone and send it
    m_audio_interface.audio_input_start();
}

void Multicast::stop_send_audio()
{
    m_audio_interface.audio_input_stop();
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


    qDebug() << m_id << " is evaluating his list";
    qDebug() << "---------------";
    //qDebug() << "   n sender    : " + QString::number(n_sender);
    //qDebug() << "   n answer    : " + QString::number(n_answer);
    //qDebug() << "   n user      : " + QString::number(n_user);

    if((n_user - 1) < 1){
        //No one in the group
        qDebug() << "permission denied";
        qDebug() << "---------------";
        return false;
    }

    int max_value = 0;
    quint8 max_id = 0;
    for(auto e : m_answer_list.keys())
    {
        if(m_answer_list.value(e) > max_value){
            max_value = m_answer_list.value(e);
            max_id = e;
        }

    }

    if( max_id == m_id){
        qDebug() << "permission granted";
        qDebug() << "---------------";
        start_send_audio();
        return true;
    }else{
        qDebug() << "permission denied";
        qDebug() << "---------------";
        return false;
    }
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

    int n_answer;
    if(m_answer_list.count(0)){
        m_answer_list.insert(id,answer);
    }else{
        n_answer = m_answer_list.value(id) + answer;
        m_answer_list.insert(id,n_answer);
    }
    qDebug() << m_id
             << " has answer value: "
             << answer;
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

void Multicast::set_user_ID()
{
    quint8 ID = 0;
    bool free = true;

    while(true)
    {
        free = true;
        for (quint8 occupied_ID : m_connected_user->keys())
        {
            free &= occupied_ID != ID;
            if (!free) break;
        }
        if(free) break;
        ++ID;
    }

    m_user->set_ID(ID);
    m_id = ID;
}
