#ifndef USER_H
#define USER_H

#include <QList>
#include "multicastctrl.h"
#include <QByteArray>

class UDPSimulation;

class User: public QObject
{
    Q_OBJECT

//--------------------------------------- public
public:
    User(int m_id);
    ~User();
    void PTT_pressed();
    void PTT_released();
    bool get_is_sending();
    bool join_group(QHostAddress& i_IP, quint16 i_port);
    bool quit_group();

    inline int get_id() { return m_id; }
    inline QMap<quint8, int>& get_connected_user_list() { return m_connected_user; }
    inline quint16 get_port() { return m_port; };
    inline QHostAddress& get_IP() { return m_IP; };

//--------------------------------------- private
private:
    int m_id;

    MulticastCtrl* m_FSM;

    int m_count_call_tout;

    QMap<quint8, int> m_connected_user;

    QTimer* m_timer;

    QHostAddress m_IP;
    quint16 m_port;

//----------------------------------- signals and slot
signals:
    void send_to_slot(QByteArray& o_msg);
    void send_to_server(int, QByteArray& msg);
    void update_gui_list(); // signal to update the GUI list

public slots:
    void receive(QByteArray&);
    void timeout_send_name();

};

#endif // USER_H
