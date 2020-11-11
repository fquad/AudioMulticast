#ifndef PRIORITY_CTRL_H
#define PRIORITY_CTRL_H

#include "priority.h"
#include <QString>
#include <QDebug>
#include <QTimer>

const int t_timeout = 100;
const int user_update_timeout = 1000;

enum EVENT //nello user fare uno switch con i tipi di dati e usare process nel modo corretto (con l'evento giusto)
{
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

class priority_ctrl:  public QObject
{
    Q_OBJECT

public:
    priority_ctrl(int id);
    ~priority_ctrl();

    void process(EVENT e, QString data = nullptr);
    void set_user_list(QMap<QString, int>* i_user_list_ptr);

    priority* m_priority;
private:
    enum State
    {
        state_idle,
        state_rts,
        state_cts,
        state_sending
    };

    //priority* m_priority;

    State m_current_state;

    QTimer cts_timer;
    QTimer rts_timer;

private slots:
    void rts_timeout();
    void cts_timeout();
};

#endif // PRIORITY_CTRL_H
