#ifndef MULTICAST_H
#define MULTICAST_H

#include <QString>
#include <QDebug>
#include <QByteArray>

#include "udpinterface.h"
#include "audiointerface.h"

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

    void start_send_audio();
    void stop_send_audio();

    void send_RTS();
    void send_user_id();

    void set_user_ID();

    void answer_RTS(bool answer, QByteArray requesterId);
    void add_RTS(QByteArray data);

    void add_answer_to_list(QByteArray data);
    void clear_answer_list();
    void clear_request_list();

    bool evaluate_list();
    void check_list();
    void update_user(QByteArray& i_user_name);

    inline void set_user_list(QMap<quint8, int>* i_user_list_ptr)
    { m_connected_user = i_user_list_ptr; }

private:
    void send(MSG_TYPE i_type, QByteArray data);


    User* m_user;
    int m_timer_count;

    QTimer m_timer_rts;

    QMap<quint8, int>* m_connected_user;
    QMap<quint8, int>  m_connected_user_prev;

    QList<quint8> m_request_list;
    QMap<quint8,int> m_answer_list;

    //-----------------------------------------------------Socket
    UDPInterface m_socket;

    //-----------------------------------------------------Audio
    AudioInterface m_audio_interface;

private slots:
    void data_audio_ready(QByteArray&);

};

#endif // PRIORITY_H
