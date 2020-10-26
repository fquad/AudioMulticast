#include "priority.h"

priority::priority(int id)
{
    m_id = id;
    m_count_call_tout = 0;
}

void priority::reproduce_audio(QString data)
{
    qDebug() << "received audio : " << data;
}

void priority::send_audio(QString data)
{
    qDebug() << "received audio : " << data;
}

void priority::send_RTS(QString data)
{
    QString id = data.mid(0,3);
    qDebug() << "id: " + id + " want to send";
}

void priority::update_list()
{
    qDebug() << '(' << m_id << ')';
    qDebug() << "----------------------------------------";

    //check if a value was not updated
    for(QString key : m_connected_user->keys())
    {
        if(m_connected_user->value(key) == m_connected_user_prev[key])
        {
            m_connected_user->remove(key);
            m_connected_user_prev.remove(key);
        }
        else qDebug() << key;
    }

    qDebug() << "----------------------------------------\n\n";

    m_connected_user_prev = *m_connected_user;
}

void priority::answer_RTS(QString data, bool answer)
{
    qDebug() << "answered : "
             + QString::number(answer)
             + " to : "
             + data.mid(0,3);
}

bool priority::evaluate_list()
{
    qDebug() << "evaluating list";
    int n_sender = m_request_list.size() + 1;
    int n_user = m_connected_user->size() + 1;
    int n_answer = 0;

    for(int i = 0; i < answer_list.size(); i++){
        QString id = m_connected_user->key(i);
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

void priority::add_RTS(QString data){
    QString id = data.mid(0,3);
    qDebug() << "added " + id + "request to list";
    m_request_list.append(id);
}

void priority::add_answer_to_list(QString data){
    QString id = data.mid(0,3);
    int answer = data.mid(3,1).toInt();
    // check that the asnwer is to the user request
    qDebug() << "added id: " + id
                + " answer to list with value: "
                + QString::number(answer);
    answer_list.insert(id,answer);
}

void priority::clear_request_list()
{
    m_request_list.clear();
}

void priority::clear_answer_list()
{
    answer_list.clear();
}

