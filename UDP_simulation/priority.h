#ifndef PRIORITY_H
#define PRIORITY_H

#include <QString>
#include <QDebug>

class priority
{
public:
    priority(int id);
    void reproduce_audio(QString data);

    void send_audio(QString data);
    void send_RTS(QString data);
    void answer_RTS(QString data, bool answer);

    bool evaluate_list();
    void update_list(QString& i_user_name);
    void add_RTS(QString data);
    void add_answer_to_list(QString data);
    void clear_request_list();
    void clear_answer_list();

    inline void set_user_list(QMap<QString, int>* i_user_list_ptr)
    { m_connected_user = i_user_list_ptr; }

/*    void updateName(QString data); //togliere perchè lo gestisce lo user
    void send_name(); */             // ----------------------------------

private:
    int m_id;
    int m_count_call_tout;

    QMap<QString, int>* m_connected_user;
    QMap<QString, int> m_connected_user_prev;

    QList<QString> m_request_list;
    QMap<QString, int> answer_list;

    //const int dbg_var_n_user = 3;
};

#endif // PRIORITY_H
