#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <string.h>
#include <map>
#include <unistd.h>
#include <errno.h>
#include "Console.hpp"
#include "main.hpp"
#include "User.hpp"

namespace ft_irc {

class Server
{
public:
	typedef std::map<fd_t, User> users_type;
public:
    Server(int port_, std::string passwd);
    void run();

    void disconnect_user(int fd);
    void sendMessage(int fd, const std::string &message); // Для отправки сообщения юзеру с заданым дескриптором. Список юзеров хранится в users.

    void setPassword(const std::string& password) { m_password = password; }
    const std::string& getPassword() const { return m_password; }

    std::map<fd_t, User>& getUsers() { return m_users; }
    int getSockFd() { return m_sock; }
private:
	void
	run_iteration();
private:
    int m_dt;
    int m_sock;
    const int port;
    std::string m_password;
    users_type m_users;
};
}
#endif
