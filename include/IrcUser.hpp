#pragma once
#include <string>
namespace ft_irc {
	struct User {
		std::string username;
		std::string hostname;
		std::string servername;
		std::string realname;
		std::string nickname;
		enum Mode {
			DISCONNECTED, REGULAR, OPERATOR
		} mode;
	};
}
