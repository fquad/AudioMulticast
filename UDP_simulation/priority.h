#ifndef PRIORITY_H
#define PRIORITY_H

#include <QString>
#include <qDebug>

class priority
{
public:
    priority(int id);
    void reproduceAudio(QString data);
    void sendAudio(QString data);
    void sendRequestToSend(QString data);
    void answerRequestToSend(QString data, bool answer);

    bool evaluateList();
    void addRequestToList(QString data);
    void addAnswerToList(QString data);
    void clear_request_list();
    void clear_answer_list();

    void updateName(QString data);
    void send_name();

private:
    int m_id;
    int m_count_call_tout;

    QMap<QString, int> m_connected_user;
    QMap<QString, int> m_last_count;

    QList<QString> users_list;
    QList<QString> request_list;
    QMap<QString, int> answer_list;

    //const int dbg_var_n_user = 3;
};

#endif // PRIORITY_H
