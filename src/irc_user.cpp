#include <IrcUser.hpp>

#include <ostream>
#include <cstdlib>

std::ostream& operator <<(std::ostream& stream, const ft_irc::User::Mode mode) {
	switch (mode) {
		break; case ft_irc::User::DISCONNECTED:
			stream << 'x';
		break; case ft_irc::User::REGULAR:
			stream << 'U';
		break; case ft_irc::User::OPERATOR:
			stream << '0';
		break; default: {
			char buffer[7];
			buffer[6] = 0;
			buffer[0] = (std::rand() & 0x7F) + 32;
			buffer[1] = (std::rand() & 0x7F) + 32;
			buffer[2] = (std::rand() & 0x7F) + 32;
			buffer[3] = (std::rand() & 0x7F) + 32;
			buffer[4] = (std::rand() & 0x7F) + 32;
			buffer[5] = (std::rand() & 0x7F) + 32;
			stream << buffer;
		}
	}
	return stream;
}

std::ostream& operator <<(std::ostream& stream, const ft_irc::User& user) {
	if (user.nickname.empty())
		stream << "*";
	else
		stream << user.nickname;
	stream << '!';
	if (user.username.empty())
		stream << "*";
	else
		stream << user.username;
	stream << '@';
	if (user.hostname.empty())
		stream << "*";
	else
		stream << user.hostname;
	stream << '$';
	if (user.servername.empty())
		stream << "*";
	else
		stream << user.servername;
	stream << ':';
	if (user.realname.empty())
		stream << "*";
	else
		stream << user.realname;
	stream << '{' << user.mode << '}';
	stream << '#';
	if (user.password.empty())
		stream << "*";
	else
		stream << user.password;
	return stream;
}
