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
	struct connection_type {
		fd_t fd;
		sockaddr_in netstat;
		std::string readbuffer;
		std::string writebuffer;
	};
	//TODO add more events if needed
	enum event_type {
		DISCONNECTED
		, MESSAGE_RECIEVED//send this event in the case of a new connection as well
		, SERVER_TERMINATED//idk
	};
	struct message_type {
		event_type event;
		fd_t fd;
		const char *message;//may be of other string type
	};
	typedef std::map<fd_t, connection_type> connections_type;
public:
    Server(int port_, std::string passwd);
	//TODO should not exist
    void run();

	//TODO (if no messages, should wait for a message)
	//should perform other work like pinging connections.
	message_type recieveMessage();

	//TODO
    void terminateConnection(fd_t fd);
	//TODO
	void shutdown();
    void sendMessage(fd_t fd, const std::string &message); // Для отправки сообщения юзеру с заданым дескриптором. Список юзеров хранится в users.

    void setPassword(const std::string& password) { m_password = password; }
    const std::string& getPassword() const { return m_password; }
	//TODO should not be used
    connections_type& getConnections() { return m_connections; }
    int getSockFd() { return m_sock; }
private:
	//TODO should not exist
	void run_iteration();
private:
    int m_dt;
    int m_sock;
    const int port;
    std::string m_password;
    connections_type m_connections;
};
}
#endif
