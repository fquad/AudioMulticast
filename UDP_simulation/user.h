#ifndef USER_H
#define USER_H

#include <QList>
#include "priority_ctrl.h"


class UDPSimulation;

class User: public QObject
{
    Q_OBJECT

//--------------------------------------- public
public:
    User(int m_id, UDPSimulation *w);
    ~User();

    void PTTpressed();
    void PTTreleased();
    bool get_is_sending();
    void connect_user(User* i_user);
    void disconnect_from_all();

    inline int get_id() const {return m_id;}
    inline QMap<QString, int>& get_connected_user_list() {return m_connected_user;}


//--------------------------------------- private
private:
    int m_id;

    priority_ctrl* FSM; //TODO: cambiare nome classe

    //State m_internal_state;

    int m_count_call_tout;

    QMap<QString, int> m_connected_user;

    QTimer* m_timer;


//----------------------------------- signals and slot
signals:
    void send_to_slot(QString& o_msg);
    void send_to_server(int, QString& msg);
    void update_gui_list(User* i_user); // signal to update the GUI list

public slots:
    void receive(QString&);
    void timeout_send_name();

};

#endif // USER_H
