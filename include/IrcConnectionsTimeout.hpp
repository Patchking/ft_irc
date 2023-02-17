#ifndef IRCCONNECTIONSTIMEOUT_HPP
#define IRCCONNECTIONSTIMEOUT_HPP
#include <map>
#include <sys/time.h>
#include "IrcConnectionTimeout.hpp"

#define DISCONNECT_DELAY	1000 * 2
#define PING_DELAY			1000 * 3

namespace ft_irc {
class IrcConnectionsTimeout {
	public:
		IrcConnectionsTimeout();
		//milliseconds. Returns time to next ping to all users.
		unsigned int nextTimeout();
		//If someone hasn't been updateTimeout() for a DISCONNECT_DELAY time. Return fd. Otherwise return -1 
		int isSomeoneTimedOut();
		//Is fd is expired (havn't updateTimeout for a DISCONNECT_DELAY)? 
		bool isTimedOut(int fd);
		void addConnections(int fd);
		void removeConnections(int fd);
		//Update timeout timer
		void updateTimeout(int fd);
		//Update ping timer
		void updatePing();
	private:
		unsigned int getTime();
		unsigned int priv_update;
		std::map<int, unsigned int> mp;
};
}

#endif
