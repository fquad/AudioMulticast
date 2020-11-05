#include "priority.h"

priority::priority(int id)
{
    m_id = id;
    m_count_call_tout = 0;
}

void priority::reproduceAudio(QString data){
    qDebug() << "received audio : " << data;
}

void priority::sendAudio(QString data){
    qDebug() << "received audio : " << data;
}

void priority::sendRequestToSend(QString data){
    QString id = data.mid(0,3);
    qDebug() << "id: " + id + " want to send";
}

void priority::answerRequestToSend(QString data, bool answer){
    qDebug() << "answered : "
             + QString::number(answer)
             + " to : "
             + data.mid(0,3);
}

bool priority::evaluateList(){
    qDebug() << "evaluating list";
    int n_sender = request_list.size() + 1;
    int n_user = m_connected_user.size() + 1;
    int n_answer = 0;

    for(int i = 0; i < answer_list.size(); i++){
        QString id = m_connected_user.key(i);
        if(answer_list.value(id) == 1){
            n_answer++;
        }
    }
    qDebug() << "---------";
    qDebug() << "n sender: " + QString::number(n_sender);
    qDebug() << "n answer: " + QString::number(n_answer);
    qDebug() << "n user  : " + QString::number(n_user);
    qDebug() << "---------";

    if( 1 / n_sender  <= n_answer / (n_user - 1) ){
        return true;
    }
    return false;
}

void priority::addRequestToList(QString data){
    QString id = data.mid(0,3);
    qDebug() << "added " + id + "request to list";
    request_list.append(id);
}

void priority::addAnswerToList(QString data){
    QString id = data.mid(0,3);
    int answer = data.mid(3,1).toInt();
    // check that the asnwer is to the user request
    qDebug() << "added id: " + id
                + " answer to list with value: "
                + QString::number(answer);
    answer_list.insert(id,answer);
}

void priority::clear_request_list(){
    request_list.clear();
}

void priority::clear_answer_list(){
    answer_list.clear();
}

void priority::send_name()
{
    //qDebug() << QString::number(m_id) + QString::number(MSG_TYPE::UPDATE_NAME);
    m_count_call_tout++;

    QString t_name = QString::number(m_id);

    //send(User::MSG_TYPE::UPDATE_NAME, t_name);

    if(m_count_call_tout == 2)
    {
        qDebug() << '(' << m_id << ')';
        qDebug() << "----------------------------------------";
        //check if a value was not updated
        for(QString key : m_connected_user.keys())
        {
            qDebug() << key;

            if(m_connected_user[key] == m_last_count[key])
            {
                m_connected_user.remove(key);
                m_last_count.remove(key);
            }
        }
        qDebug() << "----------------------------------------\n\n";

        for(QString user : m_connected_user.keys())
            m_last_count[user] = m_connected_user[user];

        m_count_call_tout = 0;
        //emit update_gui_list(this);
    }
}

void priority::updateName(QString data){
    QString t_user_to_add = data.mid(0,3);

    if(!m_connected_user.contains(t_user_to_add))
    {
        m_connected_user[t_user_to_add] = 1;
        m_last_count[t_user_to_add] = 0;

        QString user_to_update = QString::number(m_id);

        //emit update_gui_list(this);
    } else
    {
        m_connected_user[t_user_to_add]++;
    }
}
