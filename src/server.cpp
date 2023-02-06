#include "server.h"

Server::Server(int port, std::string passwd)
{
    dt = 0;
    this->port = port;
    this->password = passwd;
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        Console::log("socket() error", PRINT_GENERAL);
        Console::log(strerror(errno), PRINT_GENERAL);
        abort();
    }
    this->servername = "IRC";
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
        Console::log("updated: " + std::to_string(dt));
        // FD_ZERO(&fd_read);
        // FD_ZERO(&fd_write);
        // struct timeval timeout = {0, 0};
        // int occupied = select(FD_SETSIZE, &fd_read, &fd_write, NULL, &timeout);
        // if (occupied != 0)
        //     Console::log("Occupied: " + std::to_string(occupied));
        // for (int i = 0; i < 1024; i++)
        //     if (FD_ISSET(i, &fd_read) || FD_ISSET(i, &fd_write))
        //         Console::log("File descriptorts occupied: " + std::to_string(i));
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

        for (std::map<int, User>::iterator it = users.begin(); it != users.end();) {
            char buffer[MESSEGE_MAX_LEN];
            buffer[MESSEGE_MAX_LEN - 1] = 0;
            // Console::log("user with fd " + std::to_string(it->second.fd));
            // Console::log("Result is: " + std::to_string(result) + " and messege is " + it->second.buffer);
            int result = recv(it->first, buffer, MESSEGE_MAX_LEN - 1, 0);
            if (result == 0) {
                Console::log("User " + std::to_string(it->first) + " disconnected", PRINT_LOG);
                users.erase(it++);
                continue;
            }
            if (result == -1 && !it->second.out.empty()) {
                Console::log(it->second.out, PRINT_LOG);
                // Здесь вызывается твоя функция
                it->second.out.erase();
                it++;
                continue;
            }
            // buffer[result] = 0;
            it->second.out += buffer;
            memset(buffer, 0, MESSEGE_MAX_LEN);
            it++;
        }
        usleep(1000000);
        dt++;
    }
}

User::User()
{
    // memset(buffer, 0, MESSEGE_MAX_LEN);
}
