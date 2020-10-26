#ifndef SERVER_H
#define SERVER_H

#include <QList>

class User;

class Server
{
public:
    Server();
    ~Server();

    bool join(User* i_user);
    void exit(User* i_user);
private:
    QMap<QString, User*> m_user_list;
};

#endif // SERVER_H
