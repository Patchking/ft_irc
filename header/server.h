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
    // char buffer[MESSEGE_MAX_LEN];
    std::string out;
    struct sockaddr_in netstat;
private:
    
};

class Server
{
private:
    int port;
    int dt;
    std::string password;
    std::string servername;
    std::map<int, User> users;
    int sock;
    // fd_set fd_read;
    // fd_set fd_write;

public:
    Server(int port, std::string passwd);
    void run();
    int getPort() const { return port; }
    void setPort(int port_) { port = port_; }
    std::string getPassword() const { return password; }
    void setPassword(std::string password_) { password = password_; }
};

#endif
