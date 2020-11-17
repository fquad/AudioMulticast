#ifndef PRIORITY_H
#define PRIORITY_H

#include <QString>
#include <QDebug>
#include <QByteArray>

class UDPSimulation;

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


    priority(int id, UDPSimulation *w);

    void connect_to_group();
    void disconnect_from_group();

    void reproduce_audio(QByteArray data);

    void send_audio();
    void send_RTS();
    void answer_RTS(bool answer, QByteArray requesterId);

    bool evaluate_list();

    void check_list();
    void update_users_list(QByteArray& i_user_name);
    void send_user_id();

    void add_RTS(QByteArray data);
    void add_answer_to_list(QByteArray data);

    void clear_request_list();
    void clear_answer_list();

    int getId();



    inline void set_user_list(QMap<quint8, int>* i_user_list_ptr)
    { m_connected_user = i_user_list_ptr; }

private:
    UDPSimulation *m_window;
    quint8 m_id;
    int m_count_call_tout;
    void send(MSG_TYPE i_type, QByteArray data);


    QMap<quint8, int>* m_connected_user;
    QMap<quint8, int> m_connected_user_prev;

    QList<quint8> m_request_list;
    QList<int> m_answer_list;

signals:
    void send_signal(QByteArray& o_msg);
};

#endif // PRIORITY_H
