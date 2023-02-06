#pragma once

#include <string>
#include "Networking.hpp"

namespace ft_irc {
	struct User
	{
		fd_t fd;
		std::string readbuffer;
		std::string writebuffer;
		sockaddr_in netstat;
	};
}
