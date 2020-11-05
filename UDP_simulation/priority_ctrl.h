#ifndef PRIORITY_CTRL_H
#define PRIORITY_CTRL_H

#include "priority.h"
#include <QString>
#include <qDebug>
#include <QTimer>

const int t_timeout = 100;
const int user_update_timeout = 1000;

class priority_ctrl:  public QObject
{
    Q_OBJECT
public:
    enum Event{e_request_received,
               e_send,
               e_stop_send,
               e_recv_audio_data,
               e_send_audio_data,
               e_answer_to_rts,
               e_update_name,
              };

    priority_ctrl(int id);
    ~priority_ctrl();
    void process(Event e, QString data = nullptr);

private:
    enum State{state_idle,
               state_rts,
               state_cts,
               state_sending
             };



    priority myPriority;
    State currentState;

    QTimer cts_timer;
    QTimer rts_timer;
    QTimer user_list_timer;

private slots:
    void rts_timeout();
    void cts_timeout();
    void timeout_send_name();
};

#endif // PRIORITY_CTRL_H
