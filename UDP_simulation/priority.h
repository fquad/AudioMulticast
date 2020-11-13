#ifndef PRIORITY_H
#define PRIORITY_H

#include <QString>
#include <QDebug>

class priority: public QObject
{
    Q_OBJECT

public:
    enum MSG_TYPE
    {
        UPDATE_NAME=0,
        MSG,
        AUDIO,
        ANSWER,
        REQUEST,
    };


    priority(int id);
    void reproduce_audio(QString data);

    void send_audio();
    void send_RTS();
    void answer_RTS(bool answer, QString requesterId);

    bool evaluate_list();

    void check_list();
    void update_users_list(QString& i_user_name);
    void send_user_id();

    void add_RTS(QString data);
    void add_answer_to_list(QString data);

    void clear_request_list();
    void clear_answer_list();

    int getId();



    inline void set_user_list(QMap<QString, int>* i_user_list_ptr)
    { m_connected_user = i_user_list_ptr; }

/*    void updateName(QString data); //togliere perchè lo gestisce lo user
    void send_name(); */             // ----------------------------------

private:
    int m_id;
    int m_count_call_tout;
    void send(MSG_TYPE i_type, QString data);


    QMap<QString, int>* m_connected_user;
    QMap<QString, int> m_connected_user_prev;

    QList<QString> m_request_list;
    QList<int> m_answer_list;

signals:
    void send_signal(QString& o_msg);
};

#endif // PRIORITY_H
