#ifndef IRCCONNECTIONSTIMEOUT_HPP
#define IRCCONNECTIONSTIMEOUT_HPP
#include <vector>
#include "IrcConnectionTimeout.hpp"

namespace ft_irc {
class IrcConnectionsTimeout {
	public:
	typedef IrcConnectionTimeout::id_type id_type;
	enum {NO_TIMEDOUTS = -1};
	public:
	public:
	//milliseconds
	int nextTimeout();
	id_type nextTimedOut()const;
	void addConnections(const std::vector<id_type>&);
	void removeConnections(const std::vector<id_type>&);
	void update(id_type);
	private:
	std::vector<IrcConnectionTimeout> m_timeoutQueue;
};
}

#endif
