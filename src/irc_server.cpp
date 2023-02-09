#include <IrcServer.hpp>
#include <IrcReplies.hpp>

namespace ft_irc {

static inline
void skip_space(const char*& str) {
	for (;' ' == *str; ++str);
}

static inline
void skip_nonspace(const char*& str) {
	for (;*str && *str != ' ' && *str != '\n'; ++str);
}

static inline
bool obtain_word(const char*& begin, const char*& end) {
	skip_space(begin);
	end = begin;
	skip_nonspace(end);
	return end != begin;
}

static inline
void skip_line(char const*& str) {
	for (;*str && *str != '\n';++str);
	while ('\n' == *str)
		++str;
}

IrcServer::IrcServer(int port, const char *str)
	: Server(port, str){}

const char *const IrcServer::commands[46] = {
		"ADMIN", "AWAY", "CONNECT", "DIE", "ERROR", "INFO", "INVITE", "ISON"
			, "JOIN", "KICK", "KILL", "LINKS", "LIST", "LUSER", "MODE", "MOTD"
			, "NAMES", "NICK", "NOTICE", "OPER", "PART", "PASS", "PING", "PONG"
			, "PRIVMSG", "QUIT", "REHASH", "RESTART", "SERVICE", "SERVLIST"
			, "SERVER", "SQUERY", "SQUIT", "STATS", "SUMMON", "TIME"
			, "TOPIC", "TRACE", "USER", "USERHOST", "USERS", "VERSION"
			, "WALLOPS", "WHO", "WHOIS", "WHOWAS"
};

const IrcServer::command_function_type IrcServer::command_functions[46] = {
		&IrcServer::admin, &IrcServer::away, &IrcServer::connect
		, &IrcServer::die, &IrcServer::error, &IrcServer::info
		, &IrcServer::invite, &IrcServer::ison, &IrcServer::join
		, &IrcServer::kick, &IrcServer::kill, &IrcServer::links
		, &IrcServer::list, &IrcServer::luser, &IrcServer::mode
		, &IrcServer::motd, &IrcServer::names, &IrcServer::nick
		, &IrcServer::notice, &IrcServer::oper, &IrcServer::part
		, &IrcServer::pass, &IrcServer::ping, &IrcServer::pong
		, &IrcServer::privmsg, &IrcServer::quit, &IrcServer::rehash
		, &IrcServer::restart, &IrcServer::service, &IrcServer::servlist
		, &IrcServer::server, &IrcServer::squery, &IrcServer::squit
		, &IrcServer::stats, &IrcServer::summon, &IrcServer::time
		, &IrcServer::topic, &IrcServer::trace, &IrcServer::user
		, &IrcServer::userhost, &IrcServer::users, &IrcServer::version
		, &IrcServer::wallops, &IrcServer::who, &IrcServer::whois
		, &IrcServer::whowas
};
//ADMIN [<server>]
	bool IrcServer::admin(const char*& arguments) {
		(void)arguments;
		return true;
	}
//AWAY [<message>]
	bool IrcServer::away(const char*& arguments) {
		(void)arguments;
		return true;
	}
//CONNECT <target server> [<port> [<remote server>]] (RFC 1459)
//<target server> <port> [<remote server>] ( RFC 2812)
	bool IrcServer::connect(const char*& arguments) {
		(void)arguments;
		return true;
	}
//DIE 	Tells the server to shut down.[5] 	RFC 281
	bool IrcServer::die(const char*& arguments) {
		(void)arguments;
		return true;
	}
//ERROR <error message>
	bool IrcServer::error(const char*& arguments) {
		(void)arguments;
		return true;
	}
//INFO [<target>]
	bool IrcServer::info(const char*& arguments) {
		(void)arguments;
		return true;
	}
//INVITE <nickname> <channel>
	bool IrcServer::invite(const char*& arguments) {
		(void)arguments;
		return true;
	}
//ISON <nicknames>
	bool IrcServer::ison(const char*& arguments) {
		(void)arguments;
		return true;
	}
//JOIN <channels> [<keys>]
	bool IrcServer::join(const char*& arguments) {
		(void)arguments;
		return true;
	}
//KICK <channel> <client> [<message>]
	bool IrcServer::kick(const char*& arguments) {
		(void)arguments;
		return true;
	}
//KILL <client> <comment> [<remote server> [<server mask>]]
	bool IrcServer::kill(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::links(const char*& arguments) {
		(void)arguments;
		return true;
	}
//LIST [<channels> [<server>]]
	bool IrcServer::list(const char*& arguments) {
		(void)arguments;
		return true;
	}
//LUSERS [<mask> [<server>]]
	bool IrcServer::luser(const char*& arguments) {
		(void)arguments;
		return true;
	}
//MODE <nickname> <flags> (user)
//<channel> <flags> [<args>]
	bool IrcServer::mode(const char*& arguments) {
		(void)arguments;
		return true;
	}
//MOTD [<server>]
	bool IrcServer::motd(const char*& arguments) {
		(void)arguments;
		return true;
	}
//NAMES [<channels>] (RFC 1459)
//[<channels> [<server>]] ( RFC 2812)
	bool IrcServer::names(const char*& arguments) {
		(void)arguments;
		return true;
	}
//NICK <nickname> [<hopcount>] (RFC 1459)
//<nickname>
	bool IrcServer::nick(const char*& arguments) {
		const char *end;
		if (m_users.connected(m_currentFd)) {
			errorAlreadyRegistered();
			return true;
		}
		skip_space(arguments);
		end = arguments;
		skip_nonspace(arguments);
		m_Nick.append(arguments, end);
		return true;
	}
//NOTICE <msgtarget> <message>
	bool IrcServer::notice(const char*& arguments) {
		(void)arguments;
		return true;
	}
//OPER <username> <password>
	bool IrcServer::oper(const char*& arguments) {
		(void)arguments;
		return true;
	}
//PART <channels>
	bool IrcServer::part(const char*& arguments) {
		(void)arguments;
		return true;
	}
//PASS <password>
	bool IrcServer::pass(const char*& arguments) {
		const char *end;
		if (m_users.connected(m_currentFd)) {
			errorAlreadyRegistered();
			return true;
		}
		obtain_word(arguments, end);
		if (':' == *arguments)
			++arguments;
		if (arguments == end) {
			appendMessage(":");
			appendMessageSelf();
			appendMessage(IRC_ERR_NEEDMOREPARAMS);
			appendMessage(" * :Need more parameters.\n");
			return true;
		}
		std::string password(arguments, end);
		arguments = end;
		skip_line(arguments);
		if (Server::getPassword() != password){
			appendMessage(":");
			appendMessageSelf();
			appendMessage(IRC_ERR_PASSWDMISMATCH);
			appendMessage(" * :Password mismatch.\n");
			return false;
		}
		return true;
	}
//PING <server1> [<server2>]
	bool IrcServer::ping(const char*& arguments) {
		(void)arguments;
		return true;
	}
//PONG <server2> [<server2>]
	bool IrcServer::pong(const char*& arguments) {
		(void)arguments;
		return true;
	}
//PRIVMSG <msgtarget> <message>
	bool IrcServer::privmsg(const char*& arguments) {
		(void)arguments;
		return true;
	}
//QUIT [<message>]
	bool IrcServer::quit(const char*& arguments) {
		(void)arguments;
		return true;
	}
//REHASH
	bool IrcServer::rehash(const char*& arguments) {
		(void)arguments;
		return true;
	}
//RESTART
	bool IrcServer::restart(const char*& arguments) {
		(void)arguments;
		return true;
	}
//SERVICE <nickname> <reserved> <distribution> <type> <reserved> <info>
	bool IrcServer::service(const char*& arguments) {
		(void)arguments;
		return true;
	}
//SERVLIST [<mask> [<type>]]
	bool IrcServer::servlist(const char*& arguments) {
		(void)arguments;
		return true;
	}
//SERVER <servername> <hopcount> <info>
	bool IrcServer::server(const char*& arguments) {
		(void)arguments;
		return true;
	}
//SQUERY <servicename> <text>
	bool IrcServer::squery(const char*& arguments) {
		(void)arguments;
		return true;
	}
//SQUIT <server> <comment>
	bool IrcServer::squit(const char*& arguments) {
		(void)arguments;
		return true;
	}
//STATS <query> [<server>]
	bool IrcServer::stats(const char*& arguments) {
		(void)arguments;
		return true;
	}
//SUMMON <user> [<server>] (RFC 1459)
//<user> [<server> [<channel>]] (RFC 2812)
	bool IrcServer::summon(const char*& arguments) {
		(void)arguments;
		return true;
	}
//TIME [<server>]
	bool IrcServer::time(const char*& arguments) {
		(void)arguments;
		return true;
	}
//TOPIC <channel> [<topic>]
	bool IrcServer::topic(const char*& arguments) {
		(void)arguments;
		return true;
	}
//TRACE [<target>]
	bool IrcServer::trace(const char*& arguments) {
		(void)arguments;
		return true;
	}
//USER <username> <hostname> <servername> <realname> (RFC 1459)
//<user> <mode> <unused> <realname> (RFC 2812)
	bool IrcServer::user(const char*& arguments) {
		const char *end;
		int shift;
		bool success = true;
		m_users.logUser()
		[ID](( m_currentFd ))
		[USERNAME](( obtain_word(arguments, end)
				, std::string(arguments, end) ))
		[HOSTNAME](( obtain_word(arguments, end)
				, std::string(arguments, end) ))
		[SERVERNAME](( obtain_word(arguments, end)
				, std::string(arguments, end) ))
		[REALNAME](( obtain_word(arguments, end)
				, shift = (':' == *arguments ? skip_line(end), 1 : 0)
				, std::string(arguments + shift, end) ))
		[MODE](( User::REGULAR ));
		arguments = end;
		if (m_users.getTemp().username.empty()
			|| m_users.getTemp().hostname.empty()
			|| m_users.getTemp().servername.empty()
			|| m_users.getTemp().realname.empty()) {
			appendMessage(":");
			appendMessageSelf();
			appendMessage(IRC_ERR_NEEDMOREPARAMS);
			if (m_users[m_currentFd].nickname.empty())
				appendMessage(" * ");
			else {
				appendMessage(" ");
				appendMessage(m_users[m_currentFd].nickname);
			}
			appendMessage(" :Need more parameters.\n");
			success = false;
		}
		if (m_users.logStatus() & IrcUsers::ID_ALREADY_USED) {
			errorAlreadyRegistered();
			success = false;
		}
		if (success) {
			greet();
			success = false;
		}
		return true;
	}
//USERHOST <nickname> [<nickname> <nickname> ...]
	bool IrcServer::userhost(const char*& arguments) {
		(void)arguments;
		return true;
	}
//USERS [<server>]
	bool IrcServer::users(const char*& arguments) {
		(void)arguments;
		return true;
	}
//VERSION [<server>]
	bool IrcServer::version(const char*& arguments) {
		(void)arguments;
		return true;
	}
//WALLOPS <message>
	bool IrcServer::wallops(const char*& arguments) {
		(void)arguments;
		return true;
	}
//WHO [<name> ["o"]]
	bool IrcServer::who(const char*& arguments) {
		(void)arguments;
		return true;
	}
//WHOIS [<server>] <nicknames>
	bool IrcServer::whois(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::whowas(const char*& arguments) {
		(void)arguments;
		return true;
	}

static inline
int strcmp_spacecheck(const char* lhs, const char* rhs) {
	while (*lhs == *rhs)
		++lhs, ++rhs;
	if (*lhs < 33 && *rhs < 33)
		return 0;
	return *lhs - *rhs;
}

void IrcServer::handleCommand(const std::string& message_string) {
	const char *message = message_string.c_str();
	Console::log("handle command [", message, "]");
	while (*message) {
		char const* const* l = commands;
		char const* const* m = commands + sizeof commands / sizeof *commands / 2;
		char const* const* r = commands + sizeof commands / sizeof *commands;
		bool found = false;
		while (l + 1 != r) {
			const int cmp = strcmp_spacecheck(message, *m);
			if (cmp < 0) {
				r = m;
				m -= (m - l + 1) >> 1;
			}
			else if (cmp > 0) {
				l = m;
				m += (r - m) >> 1;
			}
			else {
				found = true;
				break;
			}
		}
		if (!found) {
			found = !strcmp_spacecheck(message, *m);
		}
		if (found) {
			int command_id = m - commands;
			Console::log("command ", *m, " id: ", command_id);
			skip_nonspace(message);
			if (!(this->*command_functions[command_id])(message)) {
				Console::log("command finished");
				sendMessage();
				terminateConnection();
				return;
			}
			Console::log("command finished");
			sendMessage();
		}
		else {
			Console::log("invalid command ", message);
			skip_line(message);
		}
	}
}

inline
void IrcServer::terminateConnection() {
	terminateConnection(m_currentFd);
}
inline
void IrcServer::terminateConnection(fd_t fd) {
	Server::terminateConnection(fd);
	m_users.unlog(fd);
}

void IrcServer::setCurrent(const message_type& message) {
	m_currentFd = message.fd;
}

void IrcServer::run() {
	for (;;) {
		typedef std::vector<message_type>::const_iterator iterator;
		const std::vector<message_type>& messages = Server::getMessage();
		Console::log("messages recieved: ", messages.size());
		for (iterator it = messages.begin(), end = messages.end()
				; it != end; ++it) {
			switch (it->event) {
				break; case DISCONNECTED:
					Console::log("disconnected event recieved #", it->fd);
					m_users.unlog(it->fd);
				break; case MESSAGE_RECIEVED:
					Console::log("message event recieved #", it->fd);
					setCurrent(*it);
					handleCommand(it->message);
				break; case SERVER_TERMINATED:
					return;
			}
			it->message.clear();
		}
		usleep(700000);
	}
}

void IrcServer::appendMessage(const char *message) {
	m_message += message;
}

void IrcServer::appendMessage(const std::string& message) {
		m_message += message;
}
void IrcServer::emptyMessage() {
	m_message.clear();
}

void IrcServer::sendMessage() {
	Console::log("in send[", m_currentFd, "] {\n", m_message, "}");
	Server::sendMessage(m_currentFd, m_message.c_str());
	Console::log("in send");
	emptyMessage();
}

void IrcServer::sendMessage(fd_t fd) {
	Server::sendMessage(fd, m_message.c_str());
	emptyMessage();
}

void IrcServer::appendMessageSelf() {
	appendMessage("42irc_serv");
}

void IrcServer::appendMessage(const User& user) {
	if (user.nickname.size())
		appendMessage(user.nickname);
	else
		appendMessage("*");
	if (user.username.size()) {
		appendMessage("!");
		appendMessage(user.username);
	}
	if (user.hostname.size()) {
		appendMessage("@");
		appendMessage(user.username);
	}
}

void IrcServer::endMessage() {
	appendMessage("\n");
}

void IrcServer::greet() {
	appendMessage(":");
	appendMessageSelf();
	appendMessage(IRC_RPL_WELCOME);
	appendMessage(" ");
	appendMessage(m_users[m_currentFd].nickname);
	appendMessage(" :Welcome and some other crap.\n");
}

void IrcServer::errorAlreadyRegistered() {
	appendMessage(":");
	appendMessageSelf();
	appendMessage(IRC_ERR_ALREADYREGISTRED);
	appendMessage(" * ");
	appendMessage(m_users[m_currentFd].nickname);
	appendMessage(" :Connection already registered.\n");
}

}
