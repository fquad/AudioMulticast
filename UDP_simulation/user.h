#ifndef USER_H
#define USER_H

#include <QList>

enum MSG_TYPE
{
    UPDATE_NAME
};

enum State
{
    IDLE, TALK,
    LISTEN
};

class User: public QObject
{
    Q_OBJECT

public:
    User(int m_id);
    ~User();

    void send(QString& i_msg);
    void connect_user(User* i_user);
    void disconnect_from_all();

    inline int get_id() const {return m_id;};

private:
    int m_id;

    State m_internal_state;

    int m_count_call_tout;

    QMap<QString, int> m_connected_user;
    QMap<QString, int> m_last_count;

    QTimer* m_timer;

signals:
    void send_to_slot(QString& o_msg);

public slots:
    void receive(QString&);
    void timeout_send_name();

};

#endif // USER_H
