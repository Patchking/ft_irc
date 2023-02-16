#ifndef SIMPLEBOT_HPP
#define SIMPLEBOT_HPP
#include <string>
#include "IrcUser.hpp"

namespace ft_irc {
class SimpleBot {
	public:
		std::string request(const User& user, const std::string&);
	private:
};
}
#endif
