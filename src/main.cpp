#include "main.h"


//TODO implement atoi
int atoi(char const *);

void check_input(int argc, char **argv)
{
    if (argc != 3) {
        Console::log("Wrong argument", PRINT_GENERAL);
        Console::log("Usage: ./ircserv <port> <password>", PRINT_GENERAL);
        abort();
    }
    if (atoi(argv[1]) < 1024 || atoi(argv[2]) > 0xffff) {
        Console::log("Error: port must be in range [1024:65535]", PRINT_GENERAL);
        abort();
    }
}

int main(int argc, char **argv)
{
    Console::set_log_level(PRINT_LOG);
    check_input(argc, argv);
    int port = atoi(argv[1]);
    Console::log("Init server, port - " + std::to_string(port), PRINT_GENERAL);
    Server serv(port, argv[2]);
    serv.run();
}
