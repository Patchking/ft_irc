#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <string.h>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "console.h"
#include "main.h"

class User
{
public:
    User();
    int fd;
    std::string readbuffer;
    std::string writebuffer;
    struct sockaddr_in netstat;
private:
    
};

class Server
{
private:
    int dt;
    std::string password;
    std::map<int, User> users;
    int sock;

public:
    const int port;
    Server(int port_, std::string passwd);
    void run();

    void disconnect_user(int fd);
    void sendMessege(int fd, const std::string &messege); // Для отправки сообщения юзеру с заданым дескриптором. Список юзеров хранится в users.

    void setPassword(std::string password_) { password = password_; }
    std::string getPassword() const { return password; }

    std::map<int, User> *getUsers() { return &users; }
    int getSockFd() { return sock; }
};

#endif
