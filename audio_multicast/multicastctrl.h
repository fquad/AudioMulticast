#ifndef PRIORITY_CTRL_H
#define PRIORITY_CTRL_H

#include <QString>
#include <QDebug>
#include <QTimer>
#include <QByteArray>

#include "multicast.h"


const int t_timeout = 200;
const int user_update_timeout = 1000;

enum EVENT
{
    E_CONNECT,
    E_DISCONNECT,
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
    void process(EVENT e, QByteArray data = nullptr);
    void set_user_list(QMap<quint8, int>* i_user_list_ptr);

    //TODO m_priority should be private or protected
    Multicast* m_multicast;
private:
    enum State
    {
        state_nogroup,
        state_idle,
        state_rts,
        state_cts,
        state_sending
    };

    bool m_ingroup;
    bool m_is_sending;

    State m_current_state;

    QTimer cts_timer;
    QTimer rts_timer;

private slots:
    void rts_timeout();
    void cts_timeout();
};

#endif // PRIORITY_CTRL_H
