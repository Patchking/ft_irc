#include "server.h"

Server::Server(int port_, std::string passwd) : port(port_)
{
    dt = 0;
    this->password = passwd;
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        Console::log("socket() error", PRINT_GENERAL);
        Console::log(strerror(errno), PRINT_GENERAL);
        abort();
    }
    int trash = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &trash, sizeof(int)) < 0) {
        Console::log("setcockopt() error", PRINT_GENERAL);
        Console::log(strerror(errno), PRINT_GENERAL);
        abort();
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &trash, sizeof(int)) < 0) {
        Console::log("setcockopt() error", PRINT_GENERAL);
        Console::log(strerror(errno), PRINT_GENERAL);
        abort();
    }
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);
    if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        Console::log("bind() error", PRINT_GENERAL);
        Console::log(strerror(errno), PRINT_GENERAL);
        abort();
    }
    if (listen(sock, 42) < 0) {
        Console::log("listen() error", PRINT_GENERAL);
        Console::log(strerror(errno), PRINT_GENERAL);
        abort();
    }
    if (fcntl(sock, F_SETFL, O_NONBLOCK) < 0) {
        Console::log("fcntl() error", PRINT_GENERAL);
        Console::log(strerror(errno), PRINT_GENERAL);
        abort();
    }
}

void Server::run()
{
    while (1) {
        Console::log("updated: " + std::to_string(dt), PRINT_DEGUB);
        // Поиск новых соединений. Если успешно, сохранине информации о соединении
        {
            struct sockaddr_in csin;
            socklen_t csin_len;

            int new_user_descr = accept(sock, (struct sockaddr *)&csin, &csin_len);
            if (new_user_descr > 0) {
                Console::log("New incoming connection #" + std::to_string(new_user_descr), PRINT_LOG);
                users[new_user_descr].fd = new_user_descr;
                users[new_user_descr].netstat = csin;
            }
        }

        // Попытка прочитать fd всех текущих соединений. В случае успешного чтения передает управление логике, в случае разрыва соединения удалет информацию о соединении
        struct timeval timeout = {0, 0};
        FD_ZERO(&fd_read);
        FD_ZERO(&fd_write);
        select(FD_SETSIZE - 1, &fd_read, &fd_write, NULL, &timeout);
        for (std::map<int, User>::iterator it = users.begin(); it != users.end();) {
            char buffer[MESSEGE_MAX_LEN];
            buffer[0] = '\0';
            int result = recv(it->first, buffer, MESSEGE_MAX_LEN - 1, 0);
            if (result == 0) {
                Console::log("User " + std::to_string(it->first) + " disconnected", PRINT_LOG);
                disconnect_user((it++)->first);
                continue;
            }
            if (result == -1 && !it->second.readbuffer.empty()) {
                Console::log(it->second.readbuffer, PRINT_LOG);
                // При получении сообщения вызывается то, что ты вставишь ниже. Для доступа к сообщению - "it->second.readbuffer"

                sendMessege(0, it->second.readbuffer); // - это пример. Сервер пытается отправить всем доступным хостам ответное сообщение

                // Пример заканчивается здесь.
                it->second.readbuffer.erase();
            }
            else {
                buffer[result] = '\0';
                it->second.readbuffer += buffer;
            }
            it++;
        }

        for (std::map<int, User>::iterator it = users.begin(); it != users.end(); it++) {
            if (!it->second.writebuffer.empty() && FD_ISSET(it->first, &fd_write)) {
                send(it->first, it->second.writebuffer.c_str(), it->second.writebuffer.size(), 0);
                it->second.writebuffer.erase();
            }
        }

        usleep(1000000); // Таймер логики. Можно редактировать, как вздумается
        dt++;
    }
}

void Server::sendMessege(int fd, const std::string &messege)
{
    if (fd == 0) {
        for (std::map<int, User>::iterator it = users.begin(); it != users.end(); it++) {
            it->second.writebuffer += messege;
        }
        return ;
    }
    if (users.find(fd) == users.end()) {
        Console::log("SendMessege error. No such fd " + std::to_string(fd), PRINT_GENERAL);
        abort();
    }
    users[fd].writebuffer += messege;
}

void Server::disconnect_user(int fd)
{
    users.erase(fd);
}

User::User()
{
    // memset(buffer, 0, MESSEGE_MAX_LEN);
}
