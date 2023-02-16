#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include "IrcUsers.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include <vector>

#define IRC_SERVER_NAME "irc_serv"

namespace ft_irc {

class IrcServer : public Server {
	public:/*
	enum Command {
		ADMIN, AWAY, CONNECT, DIE, ERROR, INFO, INVITE, ISON
			, JOIN, KICK, KILL, LINKS, LIST, LUSER, MODE, MOTD
			, NAMES, NICK, NOTICE, OPER, PART, PASS, PING, PONG
			, PRIVMSG, QUIT, REHASH, RESTART, SERVICE, SERVLIST
			, SERVER, SQUERY, SQUIT, STATS, SUMMON, TIME
			, TOPIC, TRACE, USER, USERHOST, USERS, VERSION, WALLOPS
			, WHO, WHOIS, WHOWAS
	};*/

	typedef std::map<std::string, Channel> channels_type;
	typedef bool (IrcServer::*const command_function_type)(const char*&);
	//typedef Command command_type;
	typedef Server::message_type message_type;

	IrcServer(int port, const char* password);
	~IrcServer();

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
	bool lusers(const char*& arguments);
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
	bool handleCommand(const std::string& message_string);
	void terminateConnection();
	void terminateConnection(fd_t fd);
	void setCurrent(const message_type& message);
	void run();

	static const char *const commands[46];
	static const command_function_type command_functions[46];
	private:
	User& currentUser();

	void appendMessage(const char *message);
	void appendMessage(const std::string& message);

	void emptyMessage();
	bool sendMessage();
	bool sendMessage(fd_t);
	void messageFrom(const User& user);
	void appendMessage(const User& user);
	void appendMessageSelf();
	void appendMessageNick(const User&);
	void endMessage();
	void appendMessageBegin(const char *code, int fd);
	void appendMessageBegin(const char *code);
	void errorNeedMoreParams();
	void errorNotRegistered();
	void errorBannedFromChan();
	void notification(const char *rpl, std::string str);
	void messageInChannel(std::string channel_name);
	void sendMsgToUser(int fd);

	void greet();
	void errorAlreadyRegistered();
	bool registerUser();

	void motd_start();
	void motd();
	void motd_end();
	private:
	IrcUsers m_users;
	channels_type m_channels;
	std::string m_message;
	fd_t m_currentFd;
};

}//namespace ft_irc

#endif
