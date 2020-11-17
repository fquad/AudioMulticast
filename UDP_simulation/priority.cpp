#include "priority.h"
#include "udpsimulation.h"
#include "ui_udpsimulation.h"

priority::priority(int id, UDPSimulation *w)
{
    m_window = w;
    m_id = id;
    m_count_call_tout = 0;
}

void priority::reproduce_audio(QString data)
{
    //play the received audio on the speakers

    //test version with text messages
    QString id = data.mid(0,3);
    QString str = QString::number(m_id) + " : received from" + id + " > " + data.mid(3,-1);
    m_window->ui->log->append(str);

    qDebug() << "received audio : " << data;
}

void priority::send_audio()
{
    //capture audio from the microphone and send it

    //test version with text messages
    QString audioData = QString::number(m_id) + m_window->ui->input_msg->text();

    send(MSG_TYPE::AUDIO, audioData);

    //qDebug() << "received audio : " << audioData;
}

void priority::send_RTS()
{
    //send a request to start sending audio

    QString id = QString::number(m_id);
    qDebug() << m_id
             << "want to send";
    send(MSG_TYPE::REQUEST,id);
}

void priority::update_users_list(QString& i_user_name)
{
    /*update the list with all users present in the group by checking
    * if the received id is in the list or not
    */

    if(!m_connected_user->contains(i_user_name))
    {
        //user id is not in the users list
        (*m_connected_user)[i_user_name] = 1;
        m_connected_user_prev[i_user_name] = 0;

        //QString user_to_update = QString::number(m_id);

        //emit update_gui_list(this);
    } else
    {
        //user is already in the users list
        m_connected_user_prev[i_user_name]++;
    }
}

void priority::check_list(){
    //qDebug() << '(' << m_id << ')';
    //qDebug() << "----------------------------------------";

    //check if a value was not updated
    for(QString key : m_connected_user->keys())
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
    send(MSG_TYPE::UPDATE_NAME, QString::number(m_id));
}

void priority::answer_RTS(bool answer, QString requesterId)
{
    // answer to the received request to send
    //TODO errore non bisogna inviare m_id ma l'id di chi ha fatto la richiesta

    //check if the id of the user who made the request is valid
    if(requesterId.toInt() > 0 && requesterId.toInt() < 255){

        qDebug() << QString::number(m_id)
                 << " answered : "
                 << QString::number(answer)
                 << " to : "
                 << requesterId;

        QString msg = requesterId + QString::number(answer);

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

void priority::add_RTS(QString data){
    //add the received Request To Send to the list with all the requests

    QString id = data.mid(0,3);
    qDebug() << m_id
             << " added: "
             << id
             << " to request to list";

    m_request_list.append(id);
}

void priority::add_answer_to_list(QString data){
    // add the received answer the the lists of all answers

    QString id = data.mid(0,3);
    int answer = data.mid(3,1).toInt();
    // check that the asnwer is to the user request
    if(id == QString::number(m_id)){
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

void priority::send(MSG_TYPE i_type, QString data){
    // send the given message on a comunication medium
    // currently to the simulated users
    // in the final implementation the message will be sent using the multicast protocol

    QString t_msg_to_users = QString::number(i_type) + data;
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
