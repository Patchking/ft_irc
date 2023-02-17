#ifndef IRCCONNECTIONSTIMEOUT_HPP
#define IRCCONNECTIONSTIMEOUT_HPP
#include <map>
#include <sys/time.h>
#include "IrcConnectionTimeout.hpp"

#define DISCONNECT_DELAY	1000 * 10
#define PING_DELAY			1000 * 3

namespace ft_irc {
class IrcConnectionsTimeout {
	public:
		//milliseconds. Returns time to next ping to all users.
		unsigned int nextTimeout();
		//If someone didn't answer for a while return their fd. One per func calling.
		int isSomeoneTimedOut();
		void addConnections(int fd);
		void removeConnections(int fd);
		void update(int fd);
	private:
		unsigned int getTime();
		unsigned int priv_update = 0;
		std::map<int, unsigned int> mp;
};
}

#endif
