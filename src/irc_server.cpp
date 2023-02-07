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
		(void)arguments;
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
		(void)arguments;
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
//<user> <mode> <unused> <realname> ( RFC 2812)
	bool IrcServer::user(const char*& arguments) {
		(void)arguments;
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
