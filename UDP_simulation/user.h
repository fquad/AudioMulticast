#ifndef USER_H
#define USER_H

#include <QList>



class User: public QObject
{
    Q_OBJECT

//--------------------------------------- public
public:
    User(int m_id);
    ~User();

    void send(int i_type, QString& i_msg);
    void connect_user(User* i_user);
    void disconnect_from_all();

    inline int get_id() const {return m_id;};
    inline QMap<QString, int>& get_connected_user_list() {return m_connected_user;};
public:
    enum MSG_TYPE
    {
        UPDATE_NAME, MSG,
        AUDIO_DATA, AUDIO_ACK
    };

//--------------------------------------- private
private:
    enum State
    {
        IDLE, TALK,
        LISTEN
    };

    int m_id;

    State m_internal_state;

    int m_count_call_tout;

    QMap<QString, int> m_connected_user;
    QMap<QString, int> m_last_count;

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
