#include "IrcConnectionsTimeout.hpp"

ft_irc::IrcConnectionsTimeout::IrcConnectionsTimeout() : priv_update(getTime())
{

}

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
        if (curtime - it->second > DISCONNECT_DELAY) {
            return it->first; 
        }
    }
    return (-1);
}

bool ft_irc::IrcConnectionsTimeout::isTimedOut(int fd)
{
    if (getTime() - priv_update > DISCONNECT_DELAY)
        return true;
    return false;
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

void ft_irc::IrcConnectionsTimeout::updateTimeout(int fd)
{
    // std::map<int, unsigned int>::iterator it = mp.find(fd);
    // if (it != mp.end())
    //     it->second = getTime();
    // else 
    mp[fd] = getTime();
}

void ft_irc::IrcConnectionsTimeout::updatePing()
{
    priv_update = getTime();
}

unsigned int ft_irc::IrcConnectionsTimeout::getTime()
{
    // gettimeofday(&time, NULL);
    // unsigned int out = time.tv_sec * 1000 + time.tv_usec / 1000;
    std::time_t time = std::time(NULL) * 1000;
    return time;
}
