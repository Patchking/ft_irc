#include <IrcServer.hpp>
#include <IrcReplies.hpp>

namespace ft_irc {

static inline
int strcmp_spacecheck(const char* lhs, const char* rhs) {
	while (*lhs == *rhs)
		++lhs, ++rhs;
	if (*lhs < 33 && *rhs < 33)
		return 0;
	return *lhs - *rhs;
}

static inline
std::ptrdiff_t binary_search(const char*const* commands
		, size_t size
		, const char* message) {
	char const* const* l = commands;
	char const* const* m = commands + size / 2;
	char const* const* r = commands + size;
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
			return m - commands;
		}
	}
	if (!strcmp_spacecheck(message, *m))
		return m - commands;
	return -1;
}

static inline
void skip_space(const char*& str) {
	for (;' ' == *str; ++str);
}

static inline
void skip_nonspace(const char*& str) {
	for (;; ++str) {
		switch(*str) {
			case '\0':
			case '\r':
			case '\n':
			case ' ':
				return;
			break; default:
				;
		}
	}
}

static inline
bool obtain_word(const char*& begin, const char*& end) {
	skip_space(begin);
	end = begin;
	skip_nonspace(end);
	return end != begin;
}

static inline
std::string extract_argument(const char*& message) {
	char const *end;
	obtain_word(message, end);
	if (message == end)
		return "";
	std::string ret(message, end);
	message = end;
	return ret;
}

static inline
void skip_line(char const*& str) {
	for (;;++str) {
		switch(*str) {
			case '\0':
			case '\r':
			case '\n':
				return;
			break; default:
				;
		}
	}
}

static inline
std::string extract_argument_colon(const char*& message) {
	char const *end;
	skip_space(message);
	if (*message == ':') {
		++message;
		end = message;
		skip_line(end);
		if (message == end)
			return "";
		std::string ret(message, end);
		message = end;
		return ret;
	}
	obtain_word(message, end);
	if (message == end)
		return "";
	std::string ret(message, end);
	message = end;
	return ret;
}

static inline
void next_line(char const*& str) {
	skip_line(str);
	while ('\n' == *str || '\r' == *str)
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
		std::string nick = extract_argument(arguments);
		if (nick.empty() || nick == "*") {
			appendMessage(":");
			appendMessageSelf();
			appendMessage(IRC_ERR_NONICKNAMEGIVEN);
			appendMessage(" * :No nickname parameter.\r\n");
		}
		m_users.changeUser(m_currentFd)
			[NICKNAME](nick);
		if (m_users.logStatus() & IrcUsers::NICK_ALREADY_USED) {
			appendMessage(":");
			appendMessageSelf();
			appendMessage(IRC_ERR_NICKNAMEINUSE);
			if (m_users[m_currentFd].nickname.empty())
				appendMessage(" * ");
			else
				appendMessage(m_users[m_currentFd].nickname);
			appendMessage(" ");
			appendMessage(nick);
			appendMessage(" :Nickname in use.\r\n");
		}
		if (registerUser())
			greet();
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
		if (m_users.connected(m_currentFd)) {
			errorAlreadyRegistered();
			return true;
		}
		std::string password = extract_argument_colon(arguments);
		m_users.changeUser(m_currentFd)
			[PASSWORD](password);
		if (password.empty()) {
			appendMessage(":");
			appendMessageSelf();
			appendMessage(IRC_ERR_NEEDMOREPARAMS);
			appendMessage(" * :Need more parameters.\r\n");
		}
		if (Server::getPassword() != password) {
			Console::log("password mismatch (", password, ")");
			m_users[m_currentFd].password.clear();
			appendMessage(":");
			appendMessageSelf();
			appendMessage(IRC_ERR_PASSWDMISMATCH);
			appendMessage(" * :Password mismatch.\r\n");
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
		bool success = true;
		m_users.logUser()
		[ID](m_currentFd)
		[USERNAME](extract_argument(arguments))
		[HOSTNAME](extract_argument(arguments))
		[SERVERNAME](extract_argument(arguments))
		[REALNAME](extract_argument_colon(arguments));
		if (m_users.getTemp().username.empty()
			|| m_users.getTemp().hostname.empty()
			|| m_users.getTemp().servername.empty()
			|| m_users.getTemp().realname.empty()
			) {
			appendMessage(":");
			appendMessageSelf();
			appendMessage(IRC_ERR_NEEDMOREPARAMS);
			appendMessageNick(m_users[m_currentFd]);
			appendMessage(" :Need more parameters.\r\n");
			success = false;
		}
		if (m_users[m_currentFd].nickname.empty()
				|| m_users[m_currentFd].nickname == "*")
			success = false;
		if (m_users.logStatus() & IrcUsers::ID_ALREADY_USED) {
			errorAlreadyRegistered();
			success = false;
		}
		if (success && registerUser())
			greet();
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

bool IrcServer::handleCommand(const std::string& message_string) {
	const char *message = message_string.c_str();
	Console::log("handle command ", message);
	while (*message) {
		std::ptrdiff_t cid = binary_search(commands, 46, message);
		if (-1 != cid) {
			Console::log("command ", commands[cid], " id: ", cid);
			skip_nonspace(message);
			if (!(this->*command_functions[cid])(message)) {
				sendMessage();
				return false;
			}
			next_line(message);
			sendMessage();
		}
		else {
			next_line(message);
			Console::log("invalid command ", message);
		}
	}
	return true;
}

inline
void IrcServer::terminateConnection() {
	terminateConnection(m_currentFd);
}
inline
void IrcServer::terminateConnection(fd_t fd) {
	Console::log("Disconnected ", m_users[fd], Console::LOG);
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
		if (messages.size())
			Console::log("messages recieved: ", messages.size(), Console::LOG);
		for (iterator it = messages.begin(), end = messages.end()
				; it != end; ++it) {
			switch (it->event) {
				break; case DISCONNECTED:
					Console::log("Disconnected: ", m_users[it->fd], Console::LOG);
					m_users.unlog(it->fd);
				break; case MESSAGE_RECIEVED:
					setCurrent(*it);
					if (handleCommand(it->message))
						it->message.clear();
					else
						terminateConnection();
				break; case SERVER_TERMINATED:
					return;
			}
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
	Console::log("in send[", m_currentFd, "] {\n\t", m_message, "}", Console::ALL);
	Server::sendMessage(m_currentFd, m_message.c_str());
	emptyMessage();
}

void IrcServer::sendMessage(fd_t fd) {
	Server::sendMessage(fd, m_message.c_str());
	emptyMessage();
}

void IrcServer::appendMessageSelf() {
	appendMessage(IRC_SERVER_NAME);
}

void IrcServer::appendMessageNick(const User& user) {
	if (user.nickname.empty())
		appendMessage(" *");
	else {
		appendMessage(" ");
		appendMessage(user.nickname);
	}
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
		appendMessage(user.hostname);
	}
}

void IrcServer::endMessage() {
	appendMessage("\n");
}

void IrcServer::greet() {
	appendMessage(":");
	appendMessageSelf();
	appendMessage(IRC_RPL_WELCOME);
	appendMessageNick(m_users[m_currentFd]);
	appendMessage(" :Welcome and some other crap.\r\n");
}

void IrcServer::errorAlreadyRegistered() {
	appendMessage(":");
	appendMessageSelf();
	appendMessage(IRC_ERR_ALREADYREGISTRED);
	appendMessageNick(m_users[m_currentFd]);
	appendMessage(" :Connection already registered.\r\n");
}

bool IrcServer::registerUser() {
	User& user = m_users[m_currentFd];
	if (user.nickname.empty()
	|| user.username.empty()
	|| user.hostname.empty()
	|| user.servername.empty()
	|| user.realname.empty()
	|| user.password.empty())
		return false;
	user.mode = User::REGULAR;
	return true;
}

}
