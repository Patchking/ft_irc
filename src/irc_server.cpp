#include <IrcServer.hpp>
#include <IrcReplies.hpp>
#include <cstdlib>

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
void skip_space(const char*& str) {
	for (;' ' == *str; ++str);
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
std::string extract_argument_colon(const char*& message, bool& colon) {
	char const *end;
	skip_space(message);
	if (*message == ':') {
		colon = true;
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

const char *const IrcServer::bot_commands[4] = {
	"die",
	"hello",
	"help",
	"roll"
};

const IrcServer::command_function_type IrcServer::bot_command_functions[46] = {
	&IrcServer::bot_die,
	&IrcServer::bot_hello,
	&IrcServer::bot_help,
	&IrcServer::bot_roll,
};

const IrcServer::command_function_type IrcServer::command_functions[46] = {
		&IrcServer::admin, &IrcServer::away, &IrcServer::connect
		, &IrcServer::die, &IrcServer::error, &IrcServer::info
		, &IrcServer::invite, &IrcServer::ison, &IrcServer::join
		, &IrcServer::kick, &IrcServer::kill, &IrcServer::links
		, &IrcServer::list, &IrcServer::lusers, &IrcServer::mode
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
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//AWAY [<message>]
bool IrcServer::away(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//CONNECT <target server> [<port> [<remote server>]] (RFC 1459)
//<target server> <port> [<remote server>] ( RFC 2812)
bool IrcServer::connect(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//DIE 	Tells the server to shut down.[5] 	RFC 281
bool IrcServer::die(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//ERROR <error message>
bool IrcServer::error(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//INFO [<target>]
bool IrcServer::info(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//INVITE <nickname> <channel>
bool IrcServer::invite(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//ISON <nicknames>
bool IrcServer::ison(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}

bool	isValidChannelName(const std::string &name)
{
	if (name[0] != '#' && name[0] != '&')
		return false;
	for (size_t i = 1; i < name.size(); i++)
	{
		if (name[i] == ' ' || name[i] == 7 || name[i] == 0 \
			|| name[i] == 13 || name[i] == 10 || name[i] == ',')
			return false;
	}
	return true;
}

//JOIN <channels>
bool IrcServer::join(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {//пользователь зарегистрирован?
		errorNotRegistered();
		return true;
	}
	std::string channel_name = extract_argument(arguments);
	std::string channel_name_after_space = extract_argument(arguments);//если есть пробел в названии канала
	if (channel_name.empty()) {
		errorNeedMoreParams();
		return true;
	}
	if (!isValidChannelName(channel_name) || !channel_name_after_space.empty()) {
		appendMessageBegin(IRC_ERR_BADCHANMASK);
		appendMessage(" : Bad channel name\r\n");
		return true;
	}
	channels_type::iterator iterator = m_channels.find(channel_name);
	if (iterator == m_channels.end()) {// канала ещё нет
		channels_type::iterator iterator = m_channels.insert(
			std::pair<std::string, Channel>
			(channel_name, Channel())
		).first;
		iterator->second.addOperator(m_currentFd);
		notification(IRC_RPL_NAMREPLY, " " +  m_users[m_currentFd].nickname + " is joining the channel " + channel_name + "\r\n");
	}
	else {// канал существует
		if (iterator->second.isCreep(m_currentFd)) {// пользователь забанен
			errorBannedFromChan();
			return true;
		}
		else if (iterator->second.isSpeaker(m_currentFd) || iterator->second.isOperator(m_currentFd)){// юзер уже в канале
			notification(IRC_RPL_NAMREPLY, " " + m_users[m_currentFd].nickname + " is already in the channel " + channel_name + "\r\n");
			return true;
		}
		else {// юзер не забанен
			iterator->second.addSpeaker(m_currentFd);
			notification(IRC_RPL_NAMREPLY, " " + m_users[m_currentFd].nickname + " is joining the channel " + channel_name + "\r\n");//сообщение, то что он добавлен в канал +
			// разослал всем в канале сообщение о добавлении нового пользователя
			channels_type::iterator iterator = m_channels.find(channel_name);
			Channel& channel = iterator->second;
			messageInChannel(channel);
			return true;
		}
	}
	return true;
}
//KICK <channel> <client> [<message>]
bool IrcServer::kick(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	std::string channel_name = extract_argument(arguments);
	std::string client = extract_argument(arguments);
	bool	is_colon;
	std::string message = extract_argument_colon(arguments, is_colon);
	if (channel_name.empty() || client.empty()) {
		errorNeedMoreParams();
		return true;
	}
	channels_type::iterator iterator = m_channels.find(channel_name);
	if (iterator == m_channels.end()) {
		appendMessageBegin(IRC_ERR_NOSUCHCHANNEL);
		appendMessage(" :No such channel\r\n");
		return true;
	}
	Channel& channel = iterator->second;
	if (!isChannelOperator(channel))
		return true;
	int save = m_currentFd;
	int user_id = m_users.find(client);
	switch (channel.remove(user_id)) {
	break; case Channel::FAIL_NOT_JOINED:
		appendMessageBegin(IRC_ERR_USERNOTINCHANNEL);
		appendMessage(" ");
		appendMessage(client);
		appendMessage(" ");
		appendMessage(channel_name);
		appendMessage(" :They aren't on that channel\r\n");
	break; case Channel::REMOVED_SPEAKER:
	case Channel::REMOVED_OPERATOR:
		appendMessage(":");
		appendMessage(m_users[m_currentFd]);
		appendMessage(" KICK ");
		appendMessage(channel_name);
		appendMessage(" ");
		appendMessage(client);
		appendMessage(" :");
		if (message.empty())
			appendMessage(message);
		else
			appendMessage("Kick hammer");
		appendMessage("\r\n");
		m_currentFd = -1;
		messageInChannel(channel);
		m_currentFd = save;
		sendMessage(user_id);
	break; default:;
	}
	checkChannelEmpty(channel);
	return true;
}
//KILL <nickname> <comment>
bool IrcServer::kill(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	std::string nickname = extract_argument(arguments);
	bool	is_colon;
	std::string comment = extract_argument_colon(arguments, is_colon);
	if (nickname.empty() || comment.empty()) {// проверка аргументов
		errorNeedMoreParams();
		return true;
		// проверка сущ юзера
		// проверка на опрератора 
	}

	return true;
}
bool IrcServer::links(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//LIST [<channels> [<server>]]
bool IrcServer::list(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//LUSERS [<mask> [<server>]]
bool IrcServer::lusers(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//MODE <nickname> <flags> (user)
//<channel> <flags> [<args>]
bool IrcServer::mode(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//MOTD [<server>]
bool IrcServer::motd(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//NAMES [<channels>] (RFC 1459)
//[<channels> [<server>]] ( RFC 2812)
bool IrcServer::names(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//NICK <nickname> [<hopcount>] (RFC 1459)
//<nickname>
bool IrcServer::nick(const char*& arguments) {
	std::string nick = extract_argument(arguments);
	if (nick.empty() || nick == "*") {
		appendMessageBegin(IRC_ERR_NONICKNAMEGIVEN, -1);
		appendMessage(" :No nickname parameter.\r\n");
	}
	m_users.changeUser(m_currentFd)
		[NICKNAME](nick);
	if (m_users.logStatus() & IrcUsers::NICK_ALREADY_USED) {
		appendMessageBegin(IRC_ERR_NICKNAMEINUSE);
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
	if (!m_users.connected(m_currentFd)) {
		return true;
	}
	std::string nick = extract_argument(arguments);
	if (nick.empty()) {
		return true;
	}
	bool is_colon;
	if (nick[0] == '#'/* || nick[0] == '&'*/) {//сообщение в канал
		std::string message
			= extract_argument_colon(arguments, is_colon);
		channels_type::iterator iterator = m_channels.find(nick);
		if (m_channels.end() == iterator) {
			return true;
		}
		Channel& channel = iterator->second;
		if (!isInChannel(channel))
			return true;
		sendMessage();
		appendMessage(":");
		appendMessage(m_users[m_currentFd]);
		appendMessage(" NOTICE ");
		appendMessage(nick);
		appendMessage(" :");
		appendMessage(message);
		appendMessage("\r\n");
		messageInChannel(channel);
		emptyMessage();
		return true;
	}
	int user_id = m_users.find(nick);
	if (user_id < 0) {
		return true;
	}
	std::string message = extract_argument_colon(arguments, is_colon);
	if (message.empty()) {
		return true;
	}
	User& user = m_users[user_id];
	appendMessage(":");
	appendMessage(m_users[m_currentFd]);
	appendMessage(" NOTICE");
	appendMessageNick(user);
	appendMessage(" :");
	appendMessage(message);
	appendMessage("\r\n");
	if (sendMessage(user_id)) {
		//appendMessageBegin(IRC_RPL_AWAY);
		//appendMessage(": Sent.\r\n");
	}
	return true;
}
//OPER <username> <password>
bool IrcServer::oper(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//PART <channels>
bool IrcServer::part(const char*& arguments) {
	// (void)arguments;
	if (!m_users.connected(m_currentFd)) {//пользователь зарегистрирован?
		errorNotRegistered();
		return true;
	}
	std::string channel_name = extract_argument(arguments);
	std::string channel_name_after_space = extract_argument(arguments);//если есть пробел в названии канала
	if (channel_name.empty()) {
		errorNeedMoreParams();
		return true;
	}
	if (!isValidChannelName(channel_name) || !channel_name_after_space.empty()) {
		appendMessageBegin(IRC_ERR_BADCHANMASK);
		appendMessage(" : Bad channel name\r\n");
		return true;
	}
	else {
		channels_type::iterator iterator = m_channels.find(channel_name);
		iterator->second.remove(m_currentFd);
		// notification(IRC_RPL_NAMREPLY, " " + m_users[m_currentFd].nickname + " leave channel " + channel_name + "\r\n");
		appendMessage(m_users[m_currentFd].nickname + " leave channel " + channel_name + "\r\n");//сообщение, то что он покинул канал
		// разослал всем в канале сообщение об удалении пользователя
		Channel& channel = iterator->second;
		messageInChannel(channel);
		return true;
	}
	return true;
}
//PASS <password>
bool IrcServer::pass(const char*& arguments) {
	if (m_users.connected(m_currentFd)) {
		errorAlreadyRegistered();
		return true;
	}
	bool is_colon;
	std::string password = extract_argument_colon(arguments, is_colon);
	m_users.changeUser(m_currentFd)
		[PASSWORD](password);
	if (password.empty()) {
		errorNeedMoreParams();
	}
	if (Server::getPassword() != password) {
		m_users[m_currentFd].password.clear();
		appendMessageBegin(IRC_ERR_PASSWDMISMATCH);
		appendMessage(" :Password mismatch.\r\n");
	}
	return true;
}
//PING <server1> [<server2>]
bool IrcServer::ping(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//PONG <server2> [<server2>]
bool IrcServer::pong(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}

void IrcServer::sendMsgToUser(int fd) {
	if (m_currentFd != fd)// сейчас отправитель получает сообщение тоже
		Server::sendMessage(fd, m_message);
}

void IrcServer::messageInChannel(const Channel& channel) {
	channel.for_each(*this, &IrcServer::sendMsgToUser);
}

//PRIVMSG <msgtarget> <message>
bool IrcServer::privmsg(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	std::string nick = extract_argument(arguments);
	if (nick.empty()) {
		appendMessageBegin(IRC_ERR_NORECIPIENT);
		appendMessage(" :No recipient.\r\n");
		return true;
	}
	bool is_colon;
	if (nick[0] == '#'/* || nick[0] == '&'*/) {//сообщение в канал
		std::string message
			= extract_argument_colon(arguments, is_colon);
		channels_type::iterator iterator = m_channels.find(nick);
		if (m_channels.end() == iterator) {
			errorNoSuchChannel(nick);
			return true;
		}
		Channel& channel = iterator->second;
		if (!isInChannel(channel))
			return true;
		sendMessage();
		appendMessage(":");
		appendMessage(m_users[m_currentFd]);
		appendMessage(" PRIVMSG ");
		appendMessage(nick);
		appendMessage(" :");
		appendMessage(message);
		appendMessage("\r\n");
		messageInChannel(channel);
		emptyMessage();
		return true;
	}
	int user_id = m_users.find(nick);
	if (user_id < 0) {
		appendMessageBegin(IRC_ERR_NOSUCHNICK);
		appendMessage(" :No such nick.\r\n");
		return true;
	}
	std::string message = extract_argument_colon(arguments, is_colon);
	if (message.empty()) {
		appendMessageBegin(IRC_ERR_NOTEXTTOSEND);
		appendMessage(" :Message must not be empty.\r\n");
		return true;
	}
	User& user = m_users[user_id];
	appendMessage(":");
	appendMessage(m_users[m_currentFd]);
	appendMessage(" PRIVMSG");
	appendMessageNick(user);
	appendMessage(" :");
	appendMessage(message);
	appendMessage("\r\n");
	if (sendMessage(user_id)) {
		appendMessageBegin(IRC_RPL_AWAY);
		appendMessage(": Sent.\r\n");
	}
	return true;
}
//QUIT [<message>]
bool IrcServer::quit(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//REHASH
bool IrcServer::rehash(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//RESTART
bool IrcServer::restart(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//SERVICE <nickname> <reserved> <distribution> <type> <reserved> <info>
bool IrcServer::service(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//SERVLIST [<mask> [<type>]]
bool IrcServer::servlist(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//SERVER <servername> <hopcount> <info>
bool IrcServer::server(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//SQUERY <servicename> <text>
bool IrcServer::squery(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//SQUIT <server> <comment>
bool IrcServer::squit(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//STATS <query> [<server>]
bool IrcServer::stats(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//SUMMON <user> [<server>] (RFC 1459)
//<user> [<server> [<channel>]] (RFC 2812)
bool IrcServer::summon(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//TIME [<server>]
bool IrcServer::time(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//TOPIC <channel> [<topic>]
bool IrcServer::topic(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//TRACE [<target>]
bool IrcServer::trace(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//USER <username> <hostname> <servername> <realname> (RFC 1459)
//<user> <mode> <unused> <realname> (RFC 2812)
bool IrcServer::user(const char*& arguments) {
	bool success = true;
	bool is_colon;
	m_users.logUser()
	[ID](m_currentFd)
	[USERNAME](extract_argument(arguments))
	[HOSTNAME](extract_argument(arguments))
	[SERVERNAME](extract_argument(arguments))
	[REALNAME](extract_argument_colon(arguments, is_colon));
	if (m_users.getTemp().username.empty()
		|| m_users.getTemp().hostname.empty()
		|| m_users.getTemp().servername.empty()
		|| m_users.getTemp().realname.empty()
		) {
		errorNeedMoreParams();
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
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//USERS [<server>]
bool IrcServer::users(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//VERSION [<server>]
bool IrcServer::version(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//WALLOPS <message>
bool IrcServer::wallops(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//WHO [<name> ["o"]]
bool IrcServer::who(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
//WHOIS [<server>] <nicknames>
bool IrcServer::whois(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}
bool IrcServer::whowas(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	(void)arguments;
	return true;
}

bool IrcServer::handleCommand(const std::string& message_string) {
	const char *message = message_string.c_str();
	while (*message) {
		std::ptrdiff_t cid = binary_search(commands, 46, message);
		if (-1 != cid) {
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
		// usleep(700000);
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

bool IrcServer::sendMessage() {
	if (m_message.empty())
		return false;
	Server::sendMessage(m_currentFd, m_message.c_str());
	emptyMessage();
	return true;
}

bool IrcServer::sendMessage(fd_t fd) {
	if (m_message.empty())
		return false;
	Server::sendMessage(fd, m_message.c_str());
	emptyMessage();
	return true;
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

void IrcServer::motd_start() {
	appendMessageBegin(IRC_RPL_MOTDSTART);
	appendMessage(" :Message of the day.\r\n");
}

void IrcServer::motd() {
	appendMessageBegin(IRC_RPL_MOTD);
	appendMessage(" :Welcome and some other crap.\r\n");
}

void IrcServer::motd_end() {
	appendMessageBegin(IRC_RPL_ENDOFMOTD);
	appendMessage(" :End of message of the day.\r\n");
}

void IrcServer::bot(const char *str) {
	std::ptrdiff_t cid = binary_search(commands, 46, str);
	if (-1 != cid) {
		skip_nonspace(str);
		(this->*command_functions[cid])(str);
	}
	else
		bot_unknown_command();
}
void IrcServer::bot_unknown_command() {
	int rnd = std::rand() & 15;
	switch(rnd) {
		case 0:
			appendMessage("больше сюда не пиши,"
				" от тебя гавной воняет даже отсюда.."
				" с телефона чуствую пидарас\r\n");
		break; case 1:
			appendMessage("Да ладна.");
		break; case 2:
			appendMessage("");
		break; case 3:
			appendMessage("");
		break; case 4:
			appendMessage("");
		break; case 5:
			appendMessage("");
		break; case 6:
			appendMessage("");
		break; case 7:
			appendMessage("");
		break; case 8:
			appendMessage("");
		break; case 9:
			appendMessage("");
		break; case 10:
			appendMessage("");
		break; case 11:
			appendMessage("");
		break; case 12:
			appendMessage("");
		break; case 13:
			appendMessage("");
		break; case 14:
			appendMessage("");
		break; case 15:
			appendMessage("");
	}
}

void IrcServer::appendMessageBot() {
	if (m_message.size() > 272)
		sendMessage();
	appendMessage(":bot PRIVMSG ");
	appendMessageNick(m_users[m_currentFd]);
	appendMessage(" :");
}

void IrcServer::bot_die(const char*& str) {
	int rnd = std::rand() & 15;
	switch(rnd) {
		case 0:
			appendMessage("Сам умри.\r\n");
		break; case 1:
			appendMessage("Ублюдок, как у тебя вообще "
				"наглости хватает писать такое в "
				"год 435-летия Воронежа.\r\n");
		break; case 2:
			appendMessage(
			"Суре, Артифициал Интелидженс (AI) "
			"реферс ту машинес тхат аре проограмед "
			"то преформ таске тхат ординарили "
			"реекуир хуман интелидженс то "
			"аккомплиш.\r\n");
			appendMessageBot();
			appendMessage(
			"Al цан бе дескрибед ас э "
			"комплекс сет оф алгоритмс тхат "
			"енаблес машинес то \"миссион контрол\" "
			"челенгес, креате нью паттернс, анд лерн "
			"фром дата.\r\n");
			appendMessageBot();
			appendMessage(
			"ААІ цан бе категоризед инто "
			"дво киндс: симпле рулес-басед системс "
			"анд комплекс нейралнетворкс. Al гас "
			"маны ексамплес оф реал-ворлд "
			"аппликатионс, инклудинг селф-драйвинг "
			"карс, виртуал ассистантс, фрод "
			"детектион, и медикал диагносис.\r\n");
		break; case 3:
			appendMessage(
				"Чё те дать? Иди сам возьми.\r\n");
		break; case 4:
			appendMessage("");
		break; case 5:
			appendMessage("");
		break; case 6:
			appendMessage("");
		break; case 7:
			appendMessage("");
		break; case 8:
			appendMessage("");
		break; case 9:
			appendMessage("");
		break; case 10:
			appendMessage("");
		break; case 11:
			appendMessage("");
		break; case 12:
			appendMessage("");
		break; case 13:
			appendMessage("");
		break; case 14:
			appendMessage("");
		break; case 15:
			appendMessage("");
	}
}
void IrcServer::bot_hello(const char*& str) {
	(void)str;
	int rnd = std::rand() & 15;
	switch(rnd) {
		case 0:
		break; case 1:
		break; case 2:
			appendMessage("");
		break; case 3:
			appendMessage("");
		break; case 4:
			appendMessage("");
		break; case 5:
			appendMessage("");
		break; case 6:
			appendMessage("");
		break; case 7:
			appendMessage("");
		break; case 8:
			appendMessage("");
		break; case 9:
			appendMessage("");
		break; case 10:
			appendMessage("");
		break; case 11:
			appendMessage("");
		break; case 12:
			appendMessage("");
		break; case 13:
			appendMessage("");
		break; case 14:
			appendMessage("");
		break; case 15:
			appendMessage("");
	}
}
void IrcServer::bot_help(const char*& str) {
	int rnd = std::rand() & 15;
	(void)str;
	switch(rnd) {
		case 0:
			appendMessage("Сам умри.");
		break; case 1:
			appendMessage("Я знаю 4 слова: "
					"roll, die, hello, ");
		break; case 2:
			appendMessage("");
		break; case 3:
			appendMessage("");
		break; case 4:
			appendMessage("");
		break; case 5:
			appendMessage("");
		break; case 6:
			appendMessage("");
		break; case 7:
			appendMessage("");
		break; case 8:
			appendMessage("");
		break; case 9:
			appendMessage("");
		break; case 10:
			appendMessage("");
		break; case 11:
			appendMessage("");
		break; case 12:
			appendMessage("");
		break; case 13:
			appendMessage("");
		break; case 14:
			appendMessage("");
		break; case 15:
			appendMessage("");
	}
}
void IrcServer::bot_roll(const char*& str) {
	static char const *deck[52] = {
	"2♠️", "3♠️", "4♠️", "5♠️", "6♠️", "7♠️", "8♠️",
	"9♠️", "10♠️", "J♠️", "Q♠️", "K♠️", "A♠️",
	"2♥️", "3♥️", "4♥️", "5♥️", "6♥️", "7♥️", "8♥️",
	"9♥️", "10♥️", "J♥️", "Q♥️", "K♥️", "A♥️",
	"2♦️", "3♦️", "4♦️", "5♦️", "6♦️", "7♦️", "8♦️",
	"9♦️", "10♦️", "J♦️", "Q♦️", "K♦️", "A♦️",
	"2♣️", "3♣️", "4♣️", "5♣️", "6♣️", "7♣️", "8♣️",
	"9♣️", "10♣️", "J♣️", "Q♣️", "K♣️", "A♣️"
	};
	static char const *rollers[] = {
		"die", "deck", ""
	};
	int roll;
	std::ptrdiff_t rnd
		= binary_search(rollers, 2, str);
	if (rnd == -1) {
		m_message += "Генераторы: die, deck, religion";
	}
	switch(rnd) {
		case 0:
			roll = std::rand() & 7;
			m_message += "Костяшка остановилась на ";
			m_message += roll + 1;
		break; case 1:
			roll = std::rand() % 52;
			appendMessage("Загадай карту. Ммм. "
					"Ты выбрал ");
			m_message += deck[roll];
		break; case 2: {
			float r1 = static_cast<float>(
				std::rand())
				/ (static_cast<float>(RAND_MAX)/90.f);
			float r2 = static_cast<float>(
				std::rand())
				/ (static_cast<float>(RAND_MAX)/90.f);
			appendMessage("Ща я тя по айпи вычислю. "
					"Ты здесь: ");
			m_message += r1;
			m_message += std::rand() & 1 ? "с.ш." : "ю.ш.";
			m_message += r2;
			m_message += std::rand() & 1 ? "з.д." : "в.д.";
		}
		break; case 3:
			appendMessage("");
		break; case 4:
			appendMessage("");
		break; case 5:
			appendMessage("");
		break; case 6:
			appendMessage("");
		break; case 7:
			appendMessage("");
		break; case 8:
			appendMessage("");
		break; case 9:
			appendMessage("");
		break; case 10:
			appendMessage("");
		break; case 11:
			appendMessage("");
		break; case 12:
			appendMessage("");
		break; case 13:
			appendMessage("");
		break; case 14:
			appendMessage("");
		break; case 15:
			appendMessage("");
	}
	appendMessage(".\r\n");
}

IrcServer::~IrcServer()
{

}

void IrcServer::greet() {
	motd_start();
	motd();
	motd_end();
	/*
	appendMessageBegin(IRC_RPL_WELCOME);
	appendMessage(" :Welcome and some other crap.\r\n");
	*/
}

void IrcServer::errorAlreadyRegistered() {
	appendMessageBegin(IRC_ERR_ALREADYREGISTRED);
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

void IrcServer::appendMessageBegin(const char *code, int fd) {
	if (m_message.size() > 272)
		sendMessage();
	appendMessage(":");
	appendMessageSelf();
	appendMessage(code);
	if (fd > -1)
		appendMessageNick(m_users[fd]);
	else
		appendMessage(" *");
}

void IrcServer::appendMessageBegin(const char *code) {
	appendMessageBegin(code, m_currentFd);
}

void IrcServer::errorNeedMoreParams() {
	appendMessageBegin(IRC_ERR_NEEDMOREPARAMS, m_currentFd);
	appendMessage(" :Need more parameters.\r\n");
}

void IrcServer::errorNotRegistered() {
	appendMessageBegin(IRC_ERR_NOTREGISTERED, m_currentFd);
	appendMessage(" :Register with PASS <password> NICK <nick>"
		"USER <user> <host> <server> :<realname>\r\n");
}

void IrcServer::errorNoSuchChannel(const std::string& channel_name) {
	appendMessageBegin(IRC_ERR_NOSUCHCHANNEL, m_currentFd);
	appendMessage(channel_name);
	appendMessage(" :No such channel\r\n");
}

void IrcServer::errorBannedFromChan() {
	appendMessageBegin(IRC_ERR_BANNEDFROMCHAN, m_currentFd);
	appendMessage(" :Cannot join channel (+b)\r\n");
}

bool IrcServer::isInChannel(const Channel& channel) {
	if (channel.isSpeaker(m_currentFd)
			|| channel.isOperator(m_currentFd))
		return true;
	appendMessageBegin(IRC_ERR_NOTONCHANNEL, m_currentFd);
	appendMessage(" :You're not on that channel\r\n");
	return false;
}

bool IrcServer::isChannelOperator(const Channel& channel) {
	if (!channel.isOperator(m_currentFd)) {
		if (!channel.isSpeaker(m_currentFd)) {
			appendMessageBegin(IRC_ERR_NOTONCHANNEL, m_currentFd);
			appendMessage(" :You're not on that channel\r\n");
			return false;
		}
		appendMessageBegin(IRC_ERR_CHANOPRIVSNEEDED);
		appendMessage(" :You're not channel operator\r\n");
		return false;
	}
	return true;
}

void IrcServer::notification(const char *rpl, std::string str) {
	appendMessageBegin(rpl, m_currentFd);
	appendMessage(str);
}

bool IrcServer::checkChannelEmpty(Channel& channel) {
	if (channel.getOperators().empty()) {
		if (channel.getSpeakers().empty())
			return true;
		else
			makeOp(channel, channel.getSpeakers().front());
	}
	return false;
}

void IrcServer::makeOp(Channel& channel, int id) {
	channel.op(id);
}

}
