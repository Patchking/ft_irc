#include "main.hpp"
#include <Abort.hpp>
//TODO implement atoi
int atoi(char const *);

void check_input(int argc, char **argv)
{
    if (argc != 3) {
		ft_irc::Console::log("Wrong argument"
				, ft_irc::Console::GENERAL);
		ft_irc::Console::log("Usage: ./ircserv <port> <password>"
				, ft_irc::Console::GENERAL);
		ft_irc::abort();
    }
    if (atoi(argv[1]) < 1024 || atoi(argv[2]) > 0xffff) {
		ft_irc::Console::log("Error: port must be in range [1024:65535]"
				, ft_irc::Console::GENERAL);
		ft_irc::abort();
    }
}

int main(int argc, char **argv)
{
	ft_irc::Console::set_log_level(ft_irc::Console::ALL);
    check_input(argc, argv);
    int port = atoi(argv[1]);
	ft_irc::Console::log("Init server, port - ", port, ft_irc::Console::GENERAL);
	ft_irc::Server serv(port, argv[2]);
    serv.run();
}
