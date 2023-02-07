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


void Server::run() {
	out.clear();
	Console::log("updated: ", m_dt, Console::DEBUG);
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

	// Попытка прочитать fd всех текущих соединений.
	// В случае успешного чтения передает управление логике
	// , в случае разрыва соединения удалет информацию о соединении.
	for (connections_type::iterator it = m_connections.begin(); it != m_connections.end();) {
		char buffer[MESSAGE_MAX_LEN];
		buffer[0] = '\0';
		ssize_t result = recv(it->first, buffer, MESSAGE_MAX_LEN - 1, 0);
		enum {
			USER_DISCONNECTED = 0,
			USER_STOPPED_WRITING = -1
		};
		switch (result) {
			case USER_DISCONNECTED:
				Console::log("User ", it->first, " disconnected", Console::LOG);
				out.push_back(message_type(DISCONNECTED,
									it->first, NULL));
				m_connections.erase(it++);
				continue ;
			break; case USER_STOPPED_WRITING:
				if (it->second.readbuffer.empty())
					break;
				Console::log("User #", it->first, " sends message");
				Console::log(it->second.readbuffer, Console::LOG);
				// При получении сообщения вызывается то
				// , что ты вставишь ниже
				// . Для доступа к сообщению - "it->second.readbuffer"
				// sendMessage(0, it->second.readbuffer);
				out.push_back(message_type(MESSAGE_RECIEVED,
									it->first, it->second.readbuffer.c_str()));
				// - это пример
				// . Сервер пытается отправить всем доступным хостам
				// ответное сообщение.

				// Пример заканчивается здесь.
				it->second.readbuffer.erase();
			break; default:
				Console::log("User #", it->first, "message updated");
				buffer[result] = '\0';
				it->second.readbuffer += buffer;
		}
		it++;
	}

	for (connections_type::iterator it = m_connections.begin(); it != m_connections.end(); ++it) {
		if (!it->second.writebuffer.empty()) {
			send(it->first, it->second.writebuffer.c_str()
					, it->second.writebuffer.size(), 0);
			it->second.writebuffer.erase();
		}
	}

	usleep(100000); // Таймер логики. Можно редактировать, как вздумается
	++m_dt;
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
		Console::log("SendMessage error. No such fd ", fd, Console::GENERAL);
		abort();
	}
	m_connections[fd].writebuffer += message;
}

void Server::terminateConnection(fd_t fd)
{
	m_connections.erase(fd);
}

}
