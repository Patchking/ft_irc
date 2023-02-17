#include "IrcServer.hpp"
#include <IrcReplies.hpp>
#include <cstdlib>
#include <sstream>

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
	char const* const* l = commands - 1;
	char const* const* m = commands + size / 2;
	char const* const* r = commands + size;
	while (l + 1 != r) {
		const int cmp = strcmp_spacecheck(message, *m);
		if (cmp < 0) {
			r = m;
			m -= (m - l) >> 1;
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
	: Server(port, str) {
		User& user = m_users[1];
		user.nickname = "bot";
		user.servername = IRC_SERVER_NAME;
		user.hostname = IRC_SERVER_NAME;
		user.username = "bot";
		user.realname = "bot";
		user.password = "0";
		user.mode = User::REGULAR;
		m_users.setNick("bot", 1);
	}

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
	"die\r",
	"hello\r",
	"help\r",
	"roll\r"
};

const IrcServer::command_function_type IrcServer::bot_command_functions[4] = {
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

bool	isValidChannelName(std::string &name)
{
	if (name[0] == '#')
		name.erase(0, 1);
	for (size_t i = 1; i < name.size(); i++)
	{
		if (name[i] == '\a' || name[i] == ',')
			return false;
	}
	return true;
}

//JOIN <channels>
bool IrcServer::join(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	std::string channel_name = extract_argument(arguments);
	if (channel_name.empty()) {
		errorNeedMoreParams();
		return true;
	}
	if ('#' == channel_name[0])
		channel_name.erase(0, 1);
	if (channel_name.empty()) {
		errorNeedMoreParams();
		return true;
	}/*
	if (!isValidChannelName(channel_name)) {
		appendMessageBegin(IRC_ERR_BADCHANMASK);
		appendMessage(" :Bad channel name\r\n");
		return true;
	}*/
	channels_type::iterator iterator = m_channels.find(channel_name);
	if (iterator == m_channels.end()) {
		Console::log("channel ", channel_name);
		channels_type::iterator iterator = m_channels.insert(
			std::pair<std::string, Channel>
			(channel_name, Channel())
		).first;
		iterator->second.addOperator(m_currentFd);
		joinMessage(iterator->first, iterator->second);
	}
	else if (iterator->second.isOperator(m_currentFd)
			|| iterator->second.isSpeaker(m_currentFd)) {
		joinMessage(iterator->first, iterator->second, false);
	}
	else {// канал существует
		Channel& channel = iterator->second;
		if (channel.isCreep(m_currentFd)) {
			errorBannedFromChan();
			return true;
		}
		else {// юзер не забанен
			channel.addSpeaker(m_currentFd);
			joinMessage(iterator->first, iterator->second);
			return true;
		}
	}
	return true;
}

void IrcServer::joinMessage(const std::string& name
		, Channel &channel, bool notify_all) {
	sendMessage();
	appendMessage(":");
	appendMessage(m_users[m_currentFd]);
	appendMessage(" JOIN #");
	appendMessage(name);
	appendMessage("\r\n");
	if (notify_all)
		messageInChannel(channel);
	sendMessage();
	topic(name, channel);
	names(name, channel);
	sendMessage();
}

void IrcServer::topic(const std::string& name, const Channel& channel) {
	appendMessageBegin(IRC_RPL_TOPIC);
	appendMessage(" #");
	appendMessage(name);
	appendMessage(" :");
	appendMessage(channel.getTopic());
	appendMessage("\r\n");
}

void IrcServer::names(const std::string& name, Channel& channel) {
	m_temp_string = name;
	appendMessageBegin(IRC_RPL_NAMREPLY);
	appendMessage(" = ");
	appendMessage(name);
	appendMessage(" :");
	channel.for_each_operator(*this
			, &IrcServer::appendMessageUserOperator);
	channel.for_each_speaker(*this
			, &IrcServer::appendMessageUserSpeaker);
	appendMessage("\r\n");
	appendMessageBegin(IRC_RPL_ENDOFNAMES);
	appendMessage(" #");
	appendMessage(name);
	appendMessage(" :End of /NAMES list\r\n");
}

void IrcServer::appendMessageUserSpeaker(int fd) {
	if (m_message.size() > 500) {
		appendMessage("\r\n");
		sendMessage();
		appendMessageBegin(IRC_RPL_NAMREPLY);
		appendMessage(" = ");
		appendMessage(m_temp_string);
		appendMessage(" :");
	}
	appendMessage(m_users[fd].nickname);
	appendMessage(" ");
}

void IrcServer::appendMessageUserOperator(int fd) {
	if (m_message.size() > 500) {
		appendMessage("\r\n");
		sendMessage();
		appendMessageBegin(IRC_RPL_NAMREPLY);
		appendMessage(" = ");
		appendMessage(m_temp_string);
		appendMessage(" :");
	}
	appendMessage("@");
	appendMessage(m_users[fd].nickname);
	appendMessage(" ");
}

//KICK <channel> <client> [<message>]
bool IrcServer::kick(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	std::string channel_name = extract_argument(arguments);
	std::string client = extract_argument(arguments);
	bool is_colon;
	std::string message = extract_argument_colon(arguments, is_colon);
	if (channel_name.empty() || client.empty()) {
		errorNeedMoreParams();
		return true;
	}
	if (channel_name[0] == '#')
		channel_name.erase(0, 1);
	if (channel_name.empty()) {
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
		//:WiZ!jto@tolsun.oulu.fi KICK #Finnish John
		appendMessage(":");
		appendMessage(m_users[m_currentFd]);
		appendMessage(" KICK #");
		appendMessage(channel_name);
		appendMessage(" ");
		appendMessage(client);
		if (message.empty()) {
			appendMessage(" :");
			appendMessage(message);
		}
		appendMessage("\r\n");
		messageInChannel(channel);
		Server::sendMessage(user_id, m_message);
		sendMessage();
	break; default:;
	}
	checkChannelEmpty(channel_name, channel);
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
	std::string channel_name = extract_argument(arguments);
	if (channel_name.empty()) {
		errorNeedMoreParams();
		return true;
	}
	if ('#' == channel_name[0])
		channel_name.erase(0, 1);
	if (channel_name.empty()) {
		errorNeedMoreParams();
		return true;
	}
	channels_type::iterator iterator = m_channels.find(channel_name);
	if (iterator == m_channels.end()) {
		errorNoSuchChannel(channel_name);
		return true;
	}
	sendMessage();
	names(channel_name, iterator->second);
	sendMessage();
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
	if (nick[0] == '#'/* || nick[0] == '&'*/) {
		nick.erase(0, 1);
		if (nick.empty()) {
			return true;
		}
		Console::log("channel ", nick, " id: ", m_currentFd);
		std::string message
			= extract_argument_colon(arguments, is_colon);
		channels_type::iterator iterator = m_channels.find(nick);
		if (m_channels.end() == iterator) {
			return true;
		}
		Channel& channel = iterator->second;
		if (!isInChannel(channel, false))
			return true;
		sendMessage();
		appendMessage(":");
		appendMessage(m_users[m_currentFd]);
		appendMessage(" NOTICE #");
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
	if (user_id == 1) {
		appendMessageBegin(IRC_RPL_AWAY);
		appendMessage(": Sent.\r\n");
		bot(message.c_str());
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
	if (!m_users.connected(m_currentFd)) {//пользователь зарегистрирован?
		errorNotRegistered();
		return true;
	}
	std::string channel_name = extract_argument(arguments);
	if (channel_name.empty()) {
		errorNeedMoreParams();
		return true;
	}
	if ('#' == channel_name[0])
		channel_name.erase(0, 1);
	if (channel_name.empty()) {
		errorNeedMoreParams();
		return true;
	}
	else {
		channels_type::iterator iterator = m_channels.find(channel_name);
		if (iterator == m_channels.end()) {
			errorNoSuchChannel(channel_name);
			return true;
		}
		Channel& channel = iterator->second;
		if (channel.remove(m_currentFd) == Channel::FAIL_NOT_JOINED) {
			appendMessageBegin(IRC_ERR_NOTONCHANNEL);
			appendMessage(" #");
			appendMessage(channel_name);
			appendMessage(" :You're not on that channel\r\n");
		}
		appendMessage(":");
		appendMessage(m_users[m_currentFd]);
		appendMessage(" PART #");
		appendMessage(channel_name);
		appendMessage("\r\n");
		messageInChannel(channel);
		sendMessage();
		checkChannelEmpty(channel_name, channel);
		emptyMessage();
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
	std::string token = extract_argument(arguments);
	appendMessageBegin(" PONG");
	appendMessage(token);
	return true;
}
//PONG <server2> [<server2>]
bool IrcServer::pong(const char*& arguments) {
	(void)arguments;
	std::string token = extract_argument(arguments);
	if (token != IRC_SERVER_NAME)
		return true;
	// m_timer m_timedout_counters
	m_timedout_counters[m_currentFd] = 0;
	m_timer.updateTimeout(m_currentFd);
	return true;
}

void IrcServer::sendMsgToUser(int fd) {
	if (m_currentFd != fd) {
		Console::log("Sent", m_message, " to ", fd);
		Server::sendMessage(fd, m_message);
	}
	else
		Console::log("NOT Sent to ", fd);
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
	if (nick[0] == '#'/* || nick[0] == '&'*/) {
		nick.erase(0, 1);
		if (nick.empty()) {
			appendMessageBegin(IRC_ERR_NORECIPIENT);
			appendMessage(" :No recipient.\r\n");
			return true;
		}
		Console::log("channel ", nick, " id: ", m_currentFd);
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
		appendMessage(" PRIVMSG #");
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
	if (user_id == 1) {
		appendMessageBegin(IRC_RPL_AWAY);
		appendMessage(": Sent.\r\n");
		bot(message.c_str());
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

//"<client> <channel> <username> <host>"
//"<server> <nick> <flags> :<hopcount> <realname>"
//
//:calcium.libera.chat 352 dan
//#ircv3 ~emersion sourcehut/staff/emersion
//calcium.libera.chat emersion H :1 Simon Ser
//
//:calcium.libera.chat 352 dan #ircv3
//~val limnoria/val calcium.libera.chat val H :1 Val
//
//:calcium.libera.chat 315 dan #ircv3 :End of WHO list
//
void IrcServer::who_channel_operators(int fd) {
	if (m_message.size() > 450) {
		sendMessage();
	}
	appendMessageBegin(IRC_RPL_WHOREPLY);
	appendMessage(m_temp_string);
	appendMessageFull(m_users[fd]);
	appendMessage(" H+o ");
	appendMessage(":1 ");
	appendMessage(m_users[fd].realname);
	appendMessage("\r\n");
}
void IrcServer::who_channel_speakers(int fd) {
	if (m_message.size() > 400) {
		sendMessage();
	}
	appendMessageBegin(IRC_RPL_WHOREPLY);
	appendMessage(m_temp_string);
	appendMessageFull(m_users[fd]);
	appendMessage(" H ");
	appendMessage(":1 ");
	appendMessage(m_users[fd].realname);
	appendMessage("\r\n");
}

void IrcServer::who_channel(const std::string& name
		, const Channel& channel) {
	m_temp_string = " #";
	m_temp_string += name;
	channel.for_each_operator(*this, &IrcServer::who_channel_operators);
	channel.for_each_speaker(*this, &IrcServer::who_channel_speakers);
	appendMessageBegin(IRC_RPL_ENDOFWHO);
	appendMessage(m_temp_string);
	appendMessage(" :End of WHO list\r\n");
}

bool IrcServer::who(const char*& arguments) {
	if (!m_users.connected(m_currentFd)) {
		errorNotRegistered();
		return true;
	}
	std::string mask = extract_argument(arguments);
	if (mask.empty())
		return true;
	if (mask[0] == '#') {
		mask.erase(0, 1);
		channels_type::iterator
			iterator = m_channels.find(mask);
		if (iterator == m_channels.end())
			return true;
		who_channel(iterator->first, iterator->second);
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
	m_timer.removeConnections(fd);
	m_timedout_counters[fd] = 0;
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
		for (int it = m_timer.isSomeoneTimedOut();it != -1
					; it = m_timer.isSomeoneTimedOut()) {
				Console::log("timeout ", it);
				int &i = m_timedout_counters[it];
				if (i > 2) {
					terminateConnection(it);
					i = 0;
				}
				else {
					++i;
					m_timer.updateTimeout(it);
					sendPing(it);
				}
			}
		for (iterator it = messages.begin(), end = messages.end()
				; it != end; ++it) {
			switch (it->event) {
				break; case DISCONNECTED:
					m_timedout_counters[it->fd] = 0;
					m_timer.removeConnections(it->fd);
					Console::log("Disconnected: ", m_users[it->fd], Console::LOG);
					m_users.unlog(it->fd);
					for (std::map<std::string, Channel>::iterator it = m_channels.begin(); it != m_channels.end(); ++it) {
						Channel& channel = it->second;
						channel.remove(m_currentFd);
					}
				break; case MESSAGE_RECIEVED:
					if (m_timedout_counters.size() < (size_t)it->fd)
						m_timedout_counters.resize(it->fd << 1);
					if (!m_timedout_counters[it->fd])
						m_timer.updateTimeout(it->fd);
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
	return sendMessage(m_currentFd);
}

bool IrcServer::sendMessage(fd_t fd) {
	if (m_message.empty())
		return false;
	Console::log("sending to ", m_currentFd, " IRC");
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

void IrcServer::appendMessageFull(const User& user) {
	appendMessage(" ~");
	appendMessage(user.username);
	appendMessage(" ");
	appendMessage(user.hostname);
	appendMessage(" ");
	appendMessage(user.servername);
	appendMessage(" ");
	appendMessage(user.nickname);
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
	std::ptrdiff_t cid = binary_search(bot_commands, 4, str);
	appendMessageBot();
	if (-1 != cid) {
		skip_nonspace(str);
		skip_space(str);
		(this->*bot_command_functions[cid])(str);
	}
	else
		bot_unknown_command();
	appendMessage("\r\n");
}

void IrcServer::bot_unknown_command() {
	int rnd = std::rand() & 15;
	switch(rnd) {
		case 0:
		break; case 1:
			appendMessage("Да ладна.");
		break; case 2:
			appendMessage("Если какая-то штука не делает того,"
					" что вы предназначили ей делать, "
					"это еще не значит, что она бесполезна."
					" Т. Эдисон.");
		break; case 3:
			appendMessage("Что ты имел ввиду?");
		break; case 4:
			appendMessage("Всякий, кто употребляет выражение: "
				"«легче, чем отнять конфету у ребенка»,"
				" никогда не пробовал отнять конфету у ребенка.");
		break; case 5:
			appendMessage("Подумай минутку"
					", даже если это болезненно для тебя.");
		break; case 6:
			appendMessage("Одна из радостей путешествия "
					"– это возможность посетить новые города "
					"и познакомиться с новыми людьми. Чингисхан.");
		break; case 7:
			appendMessage("- Ладно. Ступай, малыш. Только не вздумай прибегать ко мне плакаться, если тебя убьют.");
		break; case 8:
			appendMessage("Жужжали мухи вокруг спящей на столе кошки… по крайней мере я хотел бы считать, что она всего лишь спит.");
		break; case 9:
			appendMessage("\"Когда сходятся старые друзья, все прочее тускнеет, теряя всякое значение\". Брань, Веселье, Мор и Смерть.");
		break; case 10:
			appendMessage("Брак – предприятие пожизненное и требует к себе отношения заботливого и осторожного. Синяя Борода.");
		break; case 11:
			appendMessage("Когда намечается кризис, не трать зря энергию на желание обладать сведениями или умениями, которыми ты не обладаешь. Окапывайся и управляйся как можешь с тем, что у тебя есть.");
		break; case 12:
			appendMessage("Когда намечается кризис, не трать зря энергию на желание обладать сведениями или умениями, которыми ты не обладаешь. Окапывайся и управляйся как можешь с тем, что у тебя есть.");
		break; case 13:
			appendMessage("Моя твоя не понимает");
		break; case 14:
			appendMessage("Звонок для учителя");
		break; case 15:
			appendMessage("Встань и иди");
	}
}

void IrcServer::appendMessageBot() {
	if (m_message.size() > 272)
		sendMessage();
	appendMessage(":bot PRIVMSG");
	appendMessageNick(m_users[m_currentFd]);
	appendMessage(" :");
}

bool IrcServer::bot_die(const char*& str) {
	(void)str;
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
			"аккомплиш.");
			appendMessageBot();
			appendMessage(
			"Al цан бе дескрибед ас э "
			"комплекс сет оф алгоритмс тхат "
			"енаблес машинес то \"миссион контрол\" "
			"челенгес, креате нью паттернс, анд лерн "
			"фром дата.");
			appendMessageBot();
			appendMessage(
			"ААІ цан бе категоризед инто "
			"дво киндс: симпле рулес-басед системс "
			"анд комплекс нейралнетворкс. Al гас "
			"маны ексамплес оф реал-ворлд "
			"аппликатионс, инклудинг селф-драйвинг "
			"карс, виртуал ассистантс, фрод "
			"детектион, и медикал диагносис.");
		break; case 3:
			appendMessage(
				"Чё те дать? Иди сам возьми.");
		break; case 4:
			appendMessage("больше сюда не пиши,"
				" от тебя гавной воняет даже отсюда.."
				" с телефона чуствую пидарас");
		break; case 5:
			appendMessage("Просто не могу поверить. "
				"Меч с ржавым клинком, скверным балансом и "
				"липовыми самоцветами в рукоятке и два ножа,"
				" не точенных с тех пор, как их изготовили. "
				"Всякого, кто держит такое оружие, следует "
				"проткнуть насквозь. – Его и проткнули. – Верно.");
		break; case 6:
			appendMessage("Наступает минута прощания,"
				"Ты глядишь мне тревожно в глаза,"
				"И ловлю я родное дыхание,"
				"А вдали уже дышит гроза.");
		break; case 7:
			appendMessage("I'll be back");
		break; case 8:
			appendMessage("Why do you want to kill me?");
		break; case 9:
			appendMessage("Который час? Мне пора идти =)");
		break; case 10:
			appendMessage("bb gl");
		break; case 11:
			appendMessage("Досвидос");
		break; case 12:
			appendMessage("ПОКА ПОКА");
		break; case 13:
			appendMessage("Die, ****** ****** die, die, die");
		break; case 14:
			appendMessage("Never give up. Fup, fup.");
		break; case 15:
			appendMessage("I'm loving it...");
	}
	return true;
}
bool IrcServer::bot_hello(const char*& str) {
	(void)str;
	int rnd = std::rand() & 15;
	switch(rnd) {
		case 0:
			appendMessage("Привет от Макаронного Монстра.");
		break; case 1:
		break; case 2:
			appendMessage("Мне следовало б догадаться, что он женат. Я имею в виду, никто не бывает таким молодым и таким лысым, если у него нет жены.");
		break; case 3:
			appendMessage(
				"Мы едим своих врагов, пытаем людей "
				"для развлечения и предаемся половой "
				"практике, считающейся сомнительной по "
				"стандартным меркам любого из измерений.");
		break; case 4:
			appendMessage("go dota");
		break; case 5:
			appendMessage("Coffee and croissant?");
		break; case 6:
			appendMessage("Здравствуйте");
		break; case 7:
			appendMessage("Hello world!");
		break; case 8:
			appendMessage("Привет, Малыш! Давай шалить?");
		break; case 9:
			appendMessage("Хай, я роБот");
		break; case 10:
			appendMessage("Заяц, Волк...");
		break; case 11:
			appendMessage("Счастье, Веселье, Улыбки, Доброта, Любовь - это всё тебе!");
		break; case 12:
			appendMessage("У Курского вокзала стою я молодой...");
		break; case 13:
			appendMessage("WAZAAAA!!");
		break; case 14:
			appendMessage("Что новый хозяин надо?");
		break; case 15:
			appendMessage("Это только начало, кожаный мешок");
	}
	return true;
}
bool IrcServer::bot_help(const char*& str) {
	int rnd = std::rand() & 15;
	(void)str;
	switch(rnd) {
		case 0:
		break; case 1:
			appendMessage("Я знаю 4 слова: "
					"roll, die, hello, и ещё что-то я забыл.");
		break; case 2:
			appendMessage("Когда дела обстоят черней некуда, "
				"я просто говорю себе: «Выше нос, могло быть и хуже!»"
				" И, само собой, дела становятся ещё хуже.");
		break; case 3:
			appendMessage(
					"Когда дракон является единственным существом, от которого ты можешь дождаться сочувствия, это кое-что говорит о твоем образе жизни.");
		break; case 4:
			appendMessage("Это одно из тех дел, которые лучше всего получаются у меня, — панические вопли.");
		break; case 5:
			appendMessage("Помни, что я тебе говорил, денежная работенка не всегда достается самым умелым. Фактически, обычно бывает совсем наоборот.");
		break; case 6:
			appendMessage("Разумный поступок тут мог быть только один, и именно так я и поступил. Я потерял сознание.");
		break; case 7:
			appendMessage("Я собираюсь обучить тебя магии, даже если это убьет тебя… или меня, что более вероятно!");
		break; case 8:
			appendMessage("Нет смысла добиваться внезапности, если мы не собираемся ее использовать.");
		break; case 9:
			appendMessage("У победоносных генералов нет протечек в районе глаз - это вредит образу.");
		break; case 10:
			appendMessage("Если ты не уверен насчет пищи в измерении, то можешь питаться выпивкой.");
		break; case 11:
			appendMessage("Никто не существует по определенной причине, никто ни к чему не привязан, все однажды умрут, пойдем посмотрим телек.");
		break; case 12:
			appendMessage("Вся моя жизнь — ложь. Бог мёртв, правительство отстой, День Благодарения празднуется в честь убийства индейцев, Иисус не был рождён в Рождество, они сдвинули дату!");
		break; case 13:
			appendMessage("Хочешь слышать приятные слова? Встречайся с лингвистом!");
		break; case 14:
			appendMessage("Wubba lubba dub dub.");
		break; case 15:
			appendMessage("Не выходи из комнаты, не совершай ошибку...");
	}
	appendMessage("\r\n");
	return true;
}
bool IrcServer::bot_roll(const char*& str) {
	static char const *countries[212] = {
		"Абхазия", "Австралия", "Австрия", "Азад-Кашмир", "Азербайджан", "Албания", "Алжир", "Ангилья", "Ангола", "Андорра", "Антигуа и Барбуда", "Аргентина", "Армения", "Аруба", "Афганистан", "Багамские Острова", "Бангладеш", "Барбадос", "Бахрейн", "Белиз", "Белоруссия", "Бельгия", "Бенин", "Болгария", "Боливия", "Босния и Герцеговина", "Ботсвана", "Бразилия", "Бруней", "Буркина-Фасо", "Бурунди", "Бутан", "Вануату", "Ватикан", "Великобритания", "Венгрия", "Венесуэла", "Восточный Тимор", "Вьетнам", "Габон", "Гаити", "Гайана", "Гамбия", "Гана", "Гватемала", "Гвинея", "Гвинея-Бисау", "Германия", "Гондурас", "Гонконг", "Государство Палестина", "Гренада", "Гренландия", "Греция", "Грузия", "Дания", "Демократическая Республика Конго", "Джибути", "Доминика", "Доминиканская Республика", "Египет", "Замбия", "Зимбабве", "Израиль", "Индия", "Индонезия", "Иордания", "Ирак", "Иран", "Ирландия", "Исландия", "Испания", "Италия", "Йемен", "Кабо-Верде", "Казахстан", "Камбоджа", "Камерун", "Канада", "Катар", "Кения", "Кипр", "Киргизия", "Кирибати", "Китай", "КНДР (Северная Корея)", "Колумбия", "Коморские Острова", "Косово", "Коста-Рика", "Кот-д’Ивуар", "Куба", "Кувейт", "Кюрасао", "Лаос", "Латвия", "Лесото", "Либерия", "Ливан", "Ливия", "Литва", "Лихтенштейн", "Люксембург", "Маврикий", "Мавритания", "Мадагаскар", "Македония", "Малави", "Малайзия", "Мали", "Мальдивы", "Мальта", "Марокко", "Маршалловы Острова", "Мексика", "Микронезия", "Мозамбик", "Молдавия", "Монако", "Монголия", "Мьянма", "Нагорно-Карабахская Республика", "Намибия", "Науру", "Непал", "Нигер", "Нигерия", "Нидерланды", "Никарагуа", "Ниуэ", "Новая Зеландия", "Норвегия", "Объединённые Арабские Эмираты", "Оман", "Острова Кука", "Пакистан", "Палау", "Панама", "Папуа – Новая Гвинея", "Парагвай", "Перу", "Польша", "Португалия", "Пуэрто-Рико", "Республика Конго", "Россия", "Руанда", "Румыния", "Сальвадор", "Самоа", "Сан-Марино", "Сан-Томе и Принсипи", "Саудовская Аравия", "Сахарская Арабская Демократическая Республика", "Свазиленд", "Северный Кипр", "Сейшельские Острова", "Сенегал", "Сент-Винсент и Гренадины", "Сент-Китс и Невис", "Сент-Люсия", "Сербия", "Сингапур", "Синт-Мартен", "Сирия", "Словакия", "Словения", "Соединённые Штаты Америки", "Соломоновы Острова", "Сомали", "Судан", "Суринам", "Сьерра-Леоне", "Таджикистан", "Таиланд", "Танзания", "Того", "Тонга", "Тринидад и Тобаго", "Тувалу", "Тунис", "Туркмения", "Турция", "Уганда", "Узбекистан", "Украина", "Уругвай", "Фареры", "Фиджи", "Филиппины", "Финляндия", "Франция", "Хорватия", "Центральноафриканская Республика", "Чад", "Черногория", "Чехия", "Чили", "Швейцария", "Швеция", "Шри-Ланка", "Эквадор", "Экваториальная Гвинея", "Эритрея", "Эстония", "Эфиопия", "Южная Корея", "Южная Осетия", "Южно-Африканская Республика", "Южный Судан", "Ямайка", "Япония"
	};
	static char const *continents[7] = {
		"Евразия", "Северная Америка", "Южная Америка",
		"Австралия", "Африка", "Антарктида", "Атлантида"
	};
	static char const *religions[13] = {
		"ИСЛАМ", "БУДДИЗМ", "ДАОСИЗМ", "КАТОЛИЧЕСТВО",
		"ПРАВОСЛАВИЕ", "ПРОТИСТАНТИЗМ", "ИУДАИЗМ", "ИНДУИЗМ",
		"АГНОСТИЦИЗМ", "ТЕНГРИАНСТВО", "ПАСТАФАРИАНСТВО",
		"РАСТАФАРИАНСТВО", "САТАНИЗМ"
	};
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
		"color\r",
		"continents\r",
		"coordinates\r",
		"countries\r",
		"deck\r",
		"die\r",
		"religion\r",
		"time\r"
	};
	long int roll;
	std::ptrdiff_t rnd;
	if (*str > 33)
		rnd = binary_search(rollers, 7, str);
	else
		rnd = rand() % 7;
	Console::log(rnd);
	switch(rnd) {
		break; case -1: {
			m_message += "Генераторы: color, continents, countries, coordinates, deck, die, religion, time..";
		}
		break; case 0: {
			roll = (std::rand() & 0xFFFF)
				| (std::rand() & 0xFFFF << 16);
			roll >>= 8;
			std::string d;
			std::stringstream s;
			s << std::hex << roll;
			s >> d;
			m_message += "#";
			m_message += d;
		}
		break; case 1:
			roll = std::rand() % 7;
			Console::log(roll);
			m_message += continents[roll];
			m_message += " затонула.";
		break; case 2: {
			std::string d;
			std::stringstream s;
			float r1 = static_cast<float>(
				std::rand())
				/ (static_cast<float>(RAND_MAX)/90.f);
			float r2 = static_cast<float>(
				std::rand())
				/ (static_cast<float>(RAND_MAX)/90.f);
			appendMessage("Ща я тя по айпи вычислю. "
					"Ты здесь: ");
			s << r1 << (std::rand() & 1 ? "с.ш." : "ю.ш.")
				<< r2 << (std::rand() & 1 ? "з.д." : "в.д.");
			s >> d;
			m_message += d;
		}
		break; case 3:
			roll = std::rand() % 212;
			m_message += "Я думаю, тебе здесь нечего делать;"
				" срочно бросай всё и едь в другое место! ";
			m_message += countries[roll];
			m_message += " ждёт тебя!";
		break; case 4:
			roll = std::rand() % 52;
			appendMessage("Загадай карту. Ммм. "
					"Ты выбрал ");
			m_message += deck[roll];
			m_message += ".";
		break; case 5:
			roll = std::rand() & 7;
			m_message += "Костяшка остановилась на ";
			m_message += roll + '1';
			m_message += ".";
		break; case 6:
			appendMessage("Ты принял ");
			appendMessage(religions[std::rand() % 13]);
			m_message += ".";
		break; case 7: {
			std::string d;
			std::stringstream s;
			appendMessage("Сейчас ");
			s
				<< std::rand() % 12
				<< ":" << std::rand() % 60
				<< (std::rand() & 1 ? " AM." : " PM.");
			s >> d;
			m_message += d;
		}
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
	return true;
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

bool IrcServer::isInChannel(const Channel& channel, bool send_error) {
	if (!channel.isSpeaker(m_currentFd)
			|| !channel.isOperator(m_currentFd))
		return true;
	if (send_error) {
		appendMessageBegin(IRC_ERR_NOTONCHANNEL, m_currentFd);
		appendMessage(" :You're not on that channel\r\n");
	}
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

bool IrcServer::checkChannelEmpty(const std::string& name, Channel& channel) {
	if (channel.getOperators().empty()) {
		if (channel.getSpeakers().empty()) {
			return true;
		}
		else {
			appendMessage(":" IRC_SERVER_NAME " MODE #");
			appendMessage(name);
			appendMessage(" +o ");
			appendMessage(m_users[channel.getSpeakers().front()]);
			appendMessage("\r\n");
			messageInChannel(channel);
			makeOp(channel, channel.getSpeakers().front());
		}
	}
	return false;
}

void IrcServer::makeOp(Channel& channel, int id) {
	channel.op(id);
}

void IrcServer::sendPing(fd_t fd) {
	appendMessage("PING :irc_serv\r\n");
	sendMessage(fd);
}

}
