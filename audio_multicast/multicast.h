#ifndef MULTICAST_H
#define MULTICAST_H

#include <QString>
#include <QDebug>
#include <QByteArray>

#include "udpinterface.h"

class User;

class Multicast: public QObject
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

    Multicast(User* i_user);

    void connect_to_group();
    void disconnect_from_group();

    void reproduce_audio(QByteArray data);

    void send_audio();
    void send_RTS();
    void answer_RTS(bool answer, QByteArray requesterId);

    bool evaluate_list();
    void check_list();
    void update_user(QByteArray& i_user_name);
    void send_user_id();

    void add_RTS(QByteArray data);
    void add_answer_to_list(QByteArray data);

    void clear_request_list();
    void clear_answer_list();

    inline int  get_id() { return m_id; };
    inline void set_user_list(QMap<quint8, int>* i_user_list_ptr)
    { m_connected_user = i_user_list_ptr; }

private:
    User* m_user;
    quint8 m_id;
    int m_timer_count;

    QMap<quint8, int>* m_connected_user;
    QMap<quint8, int>  m_connected_user_prev;

    QList<quint8> m_request_list;
    QList<int>    m_answer_list;

    void send(MSG_TYPE i_type, QByteArray data);

    //-----------------------------------------------------Socket

    UDPInterface m_socket;

};

#endif // PRIORITY_H
