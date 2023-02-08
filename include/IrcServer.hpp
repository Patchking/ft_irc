#pragma once

#include "Server.hpp"
#include <vector>

namespace ft_irc {


class IrcServer : public Server {
	public:
	enum Command {
		ADMIN, AWAY, CONNECT, DIE, ERROR, INFO, INVITE, ISON
			, JOIN, KICK, KILL, LINKS, LIST, LUSER, MODE, MOTD
			, NAMES, NICK, NOTICE, OPER, PART, PASS, PING, PONG
			, PRIVMSG, QUIT, REHASH, RESTART, SERVICE, SERVLIST
			, SERVER, SQUERY, SQUIT, STATS, SUMMON, TIME
			, TOPIC, TRACE, USER, USERHOST, USERS, VERSION, WALLOPS
			, WHO, WHOIS, WHOWAS
	};
	struct user_type {
		std::string username;
		std::string hostname;
		std::string servername;
		std::string realname;
		std::string password;
		std::string nickname;
		enum Mode {
			REG, OP
		} mode;
	};

	typedef std::map<fd_t, user_type> users_type;
	typedef bool (IrcServer::*const command_function_type)(const char*&);
	typedef Command command_type;
	typedef Server::message_type message_type;

	IrcServer(int port, const char* password);

	bool admin(const char*& arguments);
	bool away(const char*& arguments);
	bool connect(const char*& arguments);
	bool die(const char*& arguments);
	bool error(const char*& arguments);
	bool info(const char*& arguments);
	bool invite(const char*& arguments);
	bool ison(const char*& arguments);
	bool join(const char*& arguments);
	bool kick(const char*& arguments);
	bool kill(const char*& arguments);
	bool links(const char*& arguments);
	bool list(const char*& arguments);
	bool luser(const char*& arguments);
	bool mode(const char*& arguments);
	bool motd(const char*& arguments);
	bool names(const char*& arguments);
	bool nick(const char*& arguments);
	bool notice(const char*& arguments);
	bool oper(const char*& arguments);
	bool part(const char*& arguments);
	bool pass(const char*& arguments);
	bool ping(const char*& arguments);
	bool pong(const char*& arguments);
	bool privmsg(const char*& arguments);
	bool quit(const char*& arguments);
	bool rehash(const char*& arguments);
	bool restart(const char*& arguments);
	bool service(const char*& arguments);
	bool servlist(const char*& arguments);
	bool server(const char*& arguments);
	bool squery(const char*& arguments);
	bool squit(const char*& arguments);
	bool stats(const char*& arguments);
	bool summon(const char*& arguments);
	bool time(const char*& arguments);
	bool topic(const char*& arguments);
	bool trace(const char*& arguments);
	bool user(const char*& arguments);
	bool userhost(const char*& arguments);
	bool users(const char*& arguments);
	bool version(const char*& arguments);
	bool wallops(const char*& arguments);
	bool who(const char*& arguments);
	bool whois(const char*& arguments);
	bool whowas(const char*& arguments);

	public:
	void handleCommand(const char *message);
	void terminateConnection();
	void terminateConnection(fd_t fd);
	void run();

	static const char *const commands[46];
	static const command_function_type command_functions[46];
	private:
	user_type& currentUser();
	private:
	users_type m_users;
	users_type::iterator m_currentUser;
	fd_t m_currentFd;
};

}//namespace ft_irc
