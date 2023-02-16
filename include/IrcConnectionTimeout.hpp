#ifndef IRCCONNECTIONTIMEOUT_HPP
#define IRCCONNECTIONTIMEOUT_HPP

#include <ctime>

namespace ft_irc {

class IrcConnectionTimeout {
	public:
		typedef int id_type;
	public:
		int timeout()const;
		void update();
	private:
		//std::clock_t
		//id_type
};

}

#endif
