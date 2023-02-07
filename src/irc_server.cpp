#include <IrcServer.hpp>
#include <Spaceship.hpp>

namespace ft_irc {

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

	bool IrcServer::admin(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::away(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::connect(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::die(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::error(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::info(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::invite(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::ison(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::join(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::kick(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::kill(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::links(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::list(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::luser(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::mode(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::motd(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::names(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::nick(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::notice(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::oper(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::part(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::pass(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::ping(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::pong(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::privmsg(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::quit(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::rehash(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::restart(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::service(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::servlist(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::server(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::squery(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::squit(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::stats(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::summon(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::time(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::topic(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::trace(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::user(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::userhost(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::users(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::version(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::wallops(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::who(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::whois(const char*& arguments) {
		(void)arguments;
		return true;
	}
	bool IrcServer::whowas(const char*& arguments) {
		(void)arguments;
		return true;
	}

/*
ADMIN 	ADMIN [<server>]
AWAY 	AWAY [<message>]
CONNECT 	CONNECT <target server> [<port> [<remote server>]] (RFC 1459)
CONNECT <target server> <port> [<remote server>] ( RFC 2812)
DIE 	DIE 	Tells the server to shut down.[5] 	RFC 281
ERROR 	ERROR <error message>
INFO 	INFO [<target>]
INVITE 	INVITE <nickname> <channel>
ISON 	ISON <nicknames>
JOIN 	JOIN <channels> [<keys>]
KICK 	KICK <channel> <client> [<message>]
KILL 	KILL <client> <comment>
LINKS [<remote server> [<server mask>]]
LIST 	LIST [<channels> [<server>]]
LUSERS 	LUSERS [<mask> [<server>]]
MODE 	MODE <nickname> <flags> (user)
MODE <channel> <flags> [<args>]
MOTD 	MOTD [<server>]
NAMES 	NAMES [<channels>] (RFC 1459)
NAMES [<channels> [<server>]] ( RFC 2812)
NICK 	NICK <nickname> [<hopcount>] (RFC 1459)
NICK <nickname>
NOTICE 	NOTICE <msgtarget> <message>
OPER 	OPER <username> <password>
PART 	PART <channels>
PASS 	PASS <password>
PING 	PING <server1> [<server2>]
PONG 	PONG <server2> [<server2>]
PRIVMSG 	PRIVMSG <msgtarget> <message>
QUIT 	QUIT [<message>]
REHASH 	REHASH
RESTART 	RESTART
SERVICE 	SERVICE <nickname> <reserved> <distribution> <type> <reserved> <info>
SERVLIST 	SERVLIST [<mask> [<type>]]
SERVER 	SERVER <servername> <hopcount> <info>
SQUERY 	SQUERY <servicename> <text>
SQUIT 	SQUIT <server> <comment>
STATS 	STATS <query> [<server>]
SUMMON 	SUMMON <user> [<server>] (RFC 1459)
SUMMON <user> [<server> [<channel>]] (RFC 2812)
TIME 	TIME [<server>]
TOPIC 	TOPIC <channel> [<topic>]
TRACE 	TRACE [<target>]
USER 	USER <username> <hostname> <servername> <realname> (RFC 1459)
USER <user> <mode> <unused> <realname> ( RFC 2812)
USERHOST 	USERHOST <nickname> [<nickname> <nickname> ...]
USERS 	USERS [<server>]
VERSION 	VERSION [<server>]
WALLOPS 	WALLOPS <message>
WHO 	WHO [<name> ["o"]]
WHOIS 	WHOIS [<server>] <nicknames>
WHOWAS 	WHOWAS <nickname> [<count> [<server>]]
*/
static inline
void skip_space(const char*& str) {
	for (;std::isspace(*str); ++str);
}
static inline
void skip_nonspace(const char*& str) {
	for (;*str && !std::isspace(*str); ++str);
}

static inline
int strcmp_spacecheck(const char* lhs, const char* rhs) {
	while (*lhs == *rhs)
		++lhs, ++rhs;
	if (*lhs < 33 && *rhs < 33)
		return 0;
	return *lhs - *rhs;
}

void IrcServer::handleCommand(const char *message) {
	skip_space(message);
	while (*message) {
		char const* const* l = commands;
		char const* const* m = commands + sizeof commands / (sizeof *commands * 2);
		char const* const* r = commands + sizeof commands / (sizeof *commands);
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
		if (!found)
			found = !strcmp_spacecheck(message, *m);
		if (found) {
			int command_id = m - commands;
			skip_nonspace(message);
			(this->*command_functions[command_id])(message);
		}
	}
}

}
