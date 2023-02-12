#pragma once
#include <string>
#include <ostream>

namespace ft_irc {
	struct User {
		User():mode(DISCONNECTED){}
		std::string username;
		std::string hostname;
		std::string servername;
		std::string realname;
		std::string nickname;
		std::string password;
		enum Mode {
			DISCONNECTED, REGULAR, OPERATOR
		} mode;
	};
}

//class std::ostream;

std::ostream& operator <<(std::ostream& stream, const ft_irc::User::Mode mode);

std::ostream& operator <<(std::ostream& stream, const ft_irc::User& user);
