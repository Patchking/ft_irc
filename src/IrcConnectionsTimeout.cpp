#include "IrcConnectionsTimeout.hpp"

unsigned int ft_irc::IrcConnectionsTimeout::nextTimeout()
{
    unsigned int curtime = getTime();

    if (curtime > priv_update + PING_DELAY)
        return 0;
    else
        return priv_update + PING_DELAY - curtime;
}

int ft_irc::IrcConnectionsTimeout::isSomeoneTimedOut()
{
    unsigned int curtime = getTime();
    for (std::map<int, unsigned int>::iterator it = mp.begin(); it != mp.end(); it++) {
        if (curtime > it->second + DISCONNECT_DELAY)
            return it->first;
    }
    return (0);
}

void ft_irc::IrcConnectionsTimeout::addConnections(int fd)
{
    mp[fd] = getTime();
}

void ft_irc::IrcConnectionsTimeout::removeConnections(int fd)
{
    std::map<int, unsigned int>::iterator it = mp.find(fd);
    if (it != mp.end())
        mp.erase(it);
}

void ft_irc::IrcConnectionsTimeout::update(int fd)
{
    std::map<int, unsigned int>::iterator it = mp.find(fd);
    if (it != mp.end())
        it->second = getTime(); 
}

unsigned int ft_irc::IrcConnectionsTimeout::getTime()
{
    // gettimeofday(&time, NULL);
    // unsigned int out = time.tv_sec * 1000 + time.tv_usec / 1000;
    std::clock_t time = std::clock() * 1000 / CLOCKS_PER_SEC;
    return time;
}
