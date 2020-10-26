#include "server.h"

#include "user.h"

Server::Server()
{}

bool Server::join(User* i_user)
{
    if(!m_user_list.contains(QString::number(i_user->get_id())))
    {
        for(User* user : m_user_list)
        {
            if(user != i_user)
            {
                user->connect_user(i_user);
                i_user->connect_user(user);
            }
        }
        m_user_list[QString::number(i_user->get_id())] = i_user;

        return true;
    }
    else return false;
}

void Server::exit(User* i_user)
{
    i_user->disconnect_from_all();
    m_user_list.remove(QString::number(i_user->get_id()));
}

Server::~Server()
{}
