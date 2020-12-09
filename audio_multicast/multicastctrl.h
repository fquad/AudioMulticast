#ifndef PRIORITY_CTRL_H
#define PRIORITY_CTRL_H

#include <QString>
#include <QDebug>
#include <QTimer>
#include <QByteArray>

#include "multicast.h"

const int max_retry_attemp = 3;

const int t_timeout = 500;

const int t_timeout_select_ID = 1000;

enum EVENT
{
    E_CONNECT,
    E_DISCONNECT,
    E_JOIN_GROUP,
    E_RECV_REQUEST,
    E_REQUEST_SEND,
    E_STOP_SEND,
    E_RECV_AUDIO_DATA,
    E_SEND_AUDIO_DATA,
    E_ANSWER_TO_RTS,
    E_RECV_UPDATE,
    E_SEND_UPDATE,
    E_CHECK_LIST,
};

class UDPSimulation;
class User;

class MulticastCtrl:  public QObject
{
    Q_OBJECT

public:
    MulticastCtrl(User* i_user);
    ~MulticastCtrl();

    bool get_is_sending();
    void process(EVENT i_e, QByteArray* i_data = nullptr);
    void in_group_process(EVENT i_e, QByteArray* i_data = nullptr);
    void set_user_list(QMap<quint8, int>* i_user_list_ptr);

    //TODO m_priority should be private or protected
    Multicast* m_multicast;
private:
    enum State
    {
        state_nogroup,
        state_connecting,
        state_ingroup,
        state_idle,
        state_rts,
        state_cts,
        state_sending
    };

    bool m_ingroup;
    bool m_is_sending;

    int m_retry_attemp;

    State m_state;
    State m_in_group_state;

    QTimer m_cts_timer;
    QTimer m_rts_timer;
    QTimer m_check_rcvd_audio_data_timer;

    QTimer m_select_ID_timer;
    bool m_first_time;

private slots:
    void rts_timeout();
    void cts_timeout();
    void select_ID_timeout();
    void received_audio_data_timeout();
};

#endif // PRIORITY_CTRL_H
