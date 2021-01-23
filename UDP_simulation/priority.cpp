#include "priority.h"
#include "udpsimulation.h"
#include "ui_udpsimulation.h"

priority::priority(int id, UDPSimulation *w)
{
    m_window = w;
    m_id = id;
    m_count_call_tout = 0;
}

void priority::reproduce_audio(QByteArray data)
{
    //play the received audio on the speakers

    //test version with text messages
    quint8 id = data.at(0);
    QString str = QString::number(m_id)
            + " : received from"
            +  QString::number(id)
            + " > "
            + data.mid(1,-1);

    m_window->ui->log->append(str);

    qDebug() << "received audio : " << data;
}

void priority::send_audio()
{
    //capture audio from the microphone and send it

    //test version with text messages
    QByteArray audioData;
    audioData.append(m_id);
    audioData.append(m_window->ui->input_msg->text().toUtf8());

    send(MSG_TYPE::AUDIO, audioData);

    //qDebug() << "received audio : " << audioData;
}

void priority::send_RTS()
{
    //send a request to start sending audio
    QByteArray msg;
    msg.append(m_id);

    qDebug() << m_id
             << "want to send";
    send(MSG_TYPE::REQUEST,msg);
}

void priority::update_users_list(QByteArray& i_user_name)
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

        //QString user_to_update = QString::number(m_id);

        //emit update_gui_list(this);
    } else
    {
        //user is already in the users list
        m_connected_user_prev[id]++;
    }
}

void priority::check_list(){
    //qDebug() << '(' << m_id << ')';
    //qDebug() << "----------------------------------------";

    //check if a value was not updated
    for(quint8 key : m_connected_user->keys())
    {
        if((*m_connected_user)[key] == m_connected_user_prev[key])
        {
            m_connected_user->remove(key);
            m_connected_user_prev.remove(key);
        }
        //else qDebug() << key;
    }

    //qDebug() << "----------------------------------------\n\n";

    m_connected_user_prev = *m_connected_user;
}

void priority::send_user_id(){
    //qDebug() << QString::number(m_id) << " sent is id";
    QByteArray msg;
    msg.append(m_id);
    send(MSG_TYPE::UPDATE_NAME, msg);
}

void priority::answer_RTS(bool answer, QByteArray requesterId)
{
    // answer to the received request to send
    //TODO errore non bisogna inviare m_id ma l'id di chi ha fatto la richiesta

    //check if the id of the user who made the request is valid
    quint8 r_id = requesterId.at(0);

    if(r_id > 0 && r_id < 255){

        qDebug() << QString::number(m_id)
                 << " answered : "
                 << QString::number(answer)
                 << " to : "
                 << requesterId;

        QByteArray msg;
        msg.append(r_id);
        msg.append(answer);

        send(MSG_TYPE::ANSWER, msg);
    }
}

bool priority::evaluate_list()
{
    /* evaluate the lists created in the T intervall to check if
     * the user is able to send or not
     */


    int n_sender = m_request_list.size() + 1;
    int n_user = m_connected_user->size() + 1;
    int n_answer =  m_answer_list.size();
    int n_permission = 0;

    for(int i = 0; i < n_answer; i++){
        if(m_answer_list.at(i) == 1){
            n_permission++;
        }
    }
    qDebug() << m_id << " is evaluating his list";
    qDebug() << "---------------";
    qDebug() << "   n sender    : " + QString::number(n_sender);
    qDebug() << "   n answer    : " + QString::number(n_answer);
    qDebug() << "   n permission: " + QString::number(n_permission);
    qDebug() << "   n user      : " + QString::number(n_user);

    if((n_user - 1) < 1){
        //No one in the group
        qDebug() << "permission denied";
        qDebug() << "---------------";
        return false;
    }

    if( 1 / n_sender  <= n_permission / (n_user - 1) ){
        qDebug() << "permission granted";
        qDebug() << "---------------";
        send_audio();
        return true;
    }

    return false;
}

void priority::add_RTS(QByteArray data){
    //add the received Request To Send to the list with all the requests

    quint8 id = data.at(0);
    qDebug() << m_id
             << " added: "
             << id
             << " to request to list";

    m_request_list.append(id);
}

void priority::add_answer_to_list(QByteArray data){
    // add the received answer the the lists of all answers

    quint8 id = data.at(0);
    int answer = data.at(1);
    // check that the asnwer is to the user request
    if(id == m_id){
        m_answer_list.append(answer);

        qDebug() << m_id
                 << " added answer to list with value: "
                 << answer;
    }
}

void priority::clear_request_list()
{
    m_request_list.clear();
}

void priority::clear_answer_list()
{
    m_answer_list.clear();
}

void priority::send(MSG_TYPE i_type, QByteArray data){
    // send the given message on a comunication medium
    // currently to the simulated users
    // in the final implementation the message will be sent using the multicast protocol

    QByteArray t_msg_to_users;
    t_msg_to_users.append(i_type);
    t_msg_to_users.append(data);
    emit send_signal(t_msg_to_users);

    //TODO connect to receive function in user class

    /* //obsolete just for reference

    switch(i_type)
    {
    case priority::MSG_TYPE::UPDATE_NAME:
        emit send_to_slot(t_msg_to_users);
        break;

    case priority::MSG_TYPE::MSG:
        emit send_to_server(m_id, i_msg);
        break;
    }
    */

}

int priority::getId(){
    return m_id;
}

void priority::connect_to_group(){

}

void priority::disconnect_from_group(){

}
