#ifndef ABORT_HPP
#define ABORT_HPP

#include <cstdlib>
#include "Console.hpp"
#include "main.hpp"
#include "IrcServer.hpp"

extern ft_irc::IrcServer *g_server_link;

namespace ft_irc {

	inline void ft_sig_handler(int sig_num) {
		(void)sig_num;
		Console::log("^C catched. Exit", Console::GENERAL);
		delete g_server_link;
		abort();
	}

	inline
	void abort() {
		exit(0);
	}
}

#endif
