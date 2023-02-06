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

void Server::run()
{
	while (1) {
		Console::log("updated: " + std::to_string(m_dt), Console::DEBUG);
		// Поиск новых соединений. Если успешно, сохранине информации о соединении
		{
			struct sockaddr_in csin;
			socklen_t csin_len;

			int new_user_descr = accept(m_sock, (struct sockaddr *)&csin, &csin_len);
			if (new_user_descr > 0) {
				Console::log("New incoming connection #" + std::to_string(new_user_descr), Console::LOG);
				m_users[new_user_descr].fd = new_user_descr;
				m_users[new_user_descr].netstat = csin;
			}
		}

		// Попытка прочитать fd всех текущих соединений. В случае успешного чтения передает управление логике, в случае разрыва соединения удалет информацию о соединении
		for (std::map<int, User>::iterator it = m_users.begin(); it != m_users.end();) {
			char buffer[MESSAGE_MAX_LEN];
			buffer[0] = '\0';
			int result = recv(it->first, buffer, MESSAGE_MAX_LEN - 1, 0);
			enum Case {
				USER_DISCONNECTED = 0,
				USER_STOPPED_WRITING = -1,
			};
			//0 -> user send \0 and therefore it does not want to talk to the server anymore.
			//logout
			switch (result) {
				case USER_DISCONNECTED:
					Console::log("User " + std::to_string(it->first) + " disconnected", Console::LOG);
					disconnect_user((it++)->first);
				break; case USER_STOPPED_WRITING:
				//-1 -> user is not writing anything.
					if (it->second.readbuffer.empty())
						break;
					Console::log(it->second.readbuffer, Console::LOG);
					// При получении сообщения вызывается то
					// , что ты вставишь ниже
					// . Для доступа к сообщению - "it->second.readbuffer"
					//NOTE: change to logic. argument 1 is fd; 0 -> send to all,
					sendMessage(0, it->second.readbuffer);
					// - это пример
					// . Сервер пытается отправить всем доступным хостам ответное сообщение

					// Пример заканчивается здесь.
					it->second.readbuffer.erase();
				// user has not written anything. result = -1
				// result = buffer written.
				break; default:
					buffer[result] = '\0';
					it->second.readbuffer += buffer;
			}
			it++;
		}

		for (std::map<int, User>::iterator it = m_users.begin(); it != m_users.end(); it++) {
			if (!it->second.writebuffer.empty()) {
				send(it->first, it->second.writebuffer.c_str(), it->second.writebuffer.size(), 0);
				it->second.writebuffer.erase();
			}
		}

		usleep(1000000); // Таймер логики. Можно редактировать, как вздумается
		m_dt++;
	}
}

void Server::sendMessage(int fd, const std::string &message)
{
	if (fd == 0) {
		for (std::map<int, User>::iterator it = m_users.begin(); it != m_users.end(); it++) {
			it->second.writebuffer += message;
		}
		return ;
	}
	if (m_users.find(fd) == m_users.end()) {
		Console::log("SendMessage error. No such fd " + std::to_string(fd), Console::GENERAL);
		abort();
	}
	m_users[fd].writebuffer += message;
}

void Server::disconnect_user(int fd)
{
	m_users.erase(fd);
}

}
