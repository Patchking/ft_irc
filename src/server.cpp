#include "Server.hpp"
#include <Abort.hpp>

namespace ft_irc {

Server::Server(int port_, std::string passwd) : port(port_)
{
	m_dt = 0;
	m_password = passwd;
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock < 0) {
		Console::log("socket() error", Console::GENERAL);
		Console::log(strerror(errno), Console::GENERAL);
		abort();
	}
	int trash = 1;
	if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, &trash, sizeof(int)) < 0) {
		Console::log("setcockopt() error", Console::GENERAL);
		Console::log(strerror(errno), Console::GENERAL);
		abort();
	}
	if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEPORT, &trash, sizeof(int)) < 0) {
		Console::log("setcockopt() error", Console::GENERAL);
		Console::log(strerror(errno), Console::GENERAL);
		abort();
	}
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	if (bind(m_sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
		Console::log("bind() error", Console::GENERAL);
		Console::log(strerror(errno), Console::GENERAL);
		abort();
	}
	if (listen(m_sock, 42) < 0) {
		Console::log("listen() error", Console::GENERAL);
		Console::log(strerror(errno), Console::GENERAL);
		abort();
	}
	if (fcntl(m_sock, F_SETFL, O_NONBLOCK) < 0) {
		Console::log("fcntl() error", Console::GENERAL);
		Console::log(strerror(errno), Console::GENERAL);
		abort();
	}
}

const std::vector<Server::message_type>& Server::getMessage() {
	Console::log("updated: ", m_dt, Console::DEBUG);
	out.clear();
	curlast_fd = 0;

	// Получил ли сервер только что какую-либо информацию на прошлом цикле.
	// Т.к. получение сообщения занимает несколько циклов,
	// уберает задерку в poll() если севрер получает сообщение.
	static bool just_something_happend = false;
	
	// Поиск новых соединений. Если успешно, сохранине информации о соединении
	{
		struct sockaddr_in csin;
		socklen_t csin_len;

		fd_t new_connection_descr
			= accept(m_sock, (struct sockaddr *)&csin, &csin_len);
		if (new_connection_descr > 0) {
			if (fcntl(new_connection_descr, F_SETFL, O_NONBLOCK) < 0) {
				Console::log("fcntl() error", Console::GENERAL);
				Console::log(strerror(errno), Console::GENERAL);
				abort();
			}
			Console::log("New incoming connection #"
					, new_connection_descr, Console::LOG);
			m_connections[new_connection_descr].fd = new_connection_descr;
			m_connections[new_connection_descr].netstat = csin;
		}
	}

	for (connections_type::iterator it = m_connections.begin(); it != m_connections.end(); it++) {
		addRecordToFds(it->first, POLLIN);
		if (!it->second.writebuffer.empty()) {
			addRecordToFds(it->first, POLLOUT);
		}
	}

	// Trying to determinate is connection free
	{
		int pull_return = poll(fds, curlast_fd, just_something_happend ? MIN_SERVER_DELAY : MAX_SERVER_DELAY);
		if (pull_return < 0) {
			Console::log("Pull returned error, but im not sure what does this mean", Console::GENERAL);
			Console::log(strerror(errno), Console::GENERAL);
		}
	}

	just_something_happend = false;
	for (int i = 0; i < curlast_fd; i++) {
		int curfd = fds[i].fd;
		switch (fds[i].events)
		{
		case POLLIN: {
			std::string &readBuffer = m_connections[curfd].readbuffer;
			if (fds[i].revents == POLLIN) {
				just_something_happend = true;
				char buffer[BUFFER_LEN];
				buffer[0] = '\0';
				ssize_t result = recv(curfd, buffer, BUFFER_LEN - 1, 0);
				enum {
					USER_DISCONNECTED = 0,
					ERR_OCCURED = -1
				};
				switch (result) {
					case USER_DISCONNECTED:
						Console::log("User ", curfd, " disconnected", Console::LOG);
						out.push_back(message_type(DISCONNECTED,
											curfd, readBuffer));
						terminateConnection(curfd);
						continue ;
					break; case ERR_OCCURED:
						Console::log("recv() error", Console::GENERAL);
						Console::log(strerror(errno), Console::GENERAL);
					break; default:
						Console::log("User #", curfd, " message updated", Console::DEBUG);
						buffer[result] = '\0';
						readBuffer += buffer;
				}
			} else if (!readBuffer.empty()) {
				Console::log("User #", curfd, " sends message");
				Console::log(readBuffer, Console::LOG);
				out.push_back(message_type(MESSAGE_RECIEVED,
							curfd, readBuffer));
			}
			break;
		}
		case POLLOUT: {
			std::string &writeBuffer = m_connections[curfd].writebuffer;
			if (!writeBuffer.empty() && fds[i].revents == POLLOUT) {
				Console::log("send message to ", i, ": ", writeBuffer);
				int send_result = send(curfd, writeBuffer.c_str()
						, writeBuffer.size(), 0);
				if (send_result < 0) {
					Console::log("send() error. Not sure is it error", Console::GENERAL);
					Console::log(strerror(errno), Console::GENERAL);
				}
				writeBuffer.erase();
			}
			break;
		}
		default:
			Console::log("Unreachable state in server.cpp", Console::GENERAL);
			abort();
			break;
		}
	}
	++m_dt;
	return out;
}

void Server::sendMessage(fd_t fd, const std::string &message)
{
	if (fd == 0) {
		for (connections_type::iterator it = m_connections.begin(); it != m_connections.end(); ++it) {
			it->second.writebuffer += message;
		}
		return ;
	}
	if (m_connections.find(fd) == m_connections.end()) {
		Console::log("SendMessage error. No such fd in user list. fd: ", fd, Console::GENERAL);
		Console::log("Program reached state which should be unreachable.", Console::GENERAL);
		abort();
	}
	m_connections[fd].writebuffer += message;
}

void Server::addRecordToFds(int fd, int type)
{
	if (curlast_fd * 2 >= MAX_CONNECTION) {
		Console::log("Out of fd on server", Console::GENERAL);
		abort();
	}
	fds[curlast_fd].fd = fd;
	fds[curlast_fd].events = type;
	fds[curlast_fd].revents = 0;
	curlast_fd++;
}

bool Server::isFdWriteable(int fd)
{
	if (!(fds[fd + MAX_CONNECTION].revents & POLLOUT))
		return false;
	fds[fd + MAX_CONNECTION].revents = 0;
    return true;
}

bool Server::isFdReadable(int fd)
{
	if (!(fds[fd].revents & POLLIN))
		return false;
	fds[fd].revents = 0;
    return true;
}

void Server::terminateConnection(fd_t fd)
{
	if (m_connections.find(fd) == m_connections.end()) {
		Console::log("No such user: ", fd, Console::GENERAL);
		return ;
	}
	close(fd);
	m_connections.erase(fd);
}

}
