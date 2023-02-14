#pragma once
#define IRC_RPL_WELCOME " 001"
#define IRC_RPL_YOURHOST " 002"
#define IRC_RPL_CREATED " 003"
#define IRC_RPL_MYINFO " 004"
#define IRC_RPL_ISUPPORT " 005"
#define IRC_RPL_BOUNCE " 010"
#define IRC_RPL_MAP " 015"
#define IRC_RPL_MAPEND " 017"
#define IRC_RPL_MAPSTART " 018"
#define IRC_RPL_HELLO " 020"
#define IRC_RPL_YOURID " 042"
#define IRC_RPL_SAVENICK " 043"
#define IRC_RPL_TRACELINK " 200"
#define IRC_RPL_TRACECONNECTING " 201"
#define IRC_RPL_TRACEHANDSHAKE " 202"
#define IRC_RPL_TRACEUNKNOWN " 203"
#define IRC_RPL_TRACEOPERATOR " 204"
#define IRC_RPL_TRACEUSER " 205"
#define IRC_RPL_TRACESERVER " 206"
#define IRC_RPL_TRACESERVICE " 207"
#define IRC_RPL_TRACENEWTYPE " 208"
#define IRC_RPL_TRACECLASS " 209"
#define IRC_RPL_STATSLINKINFO " 211"
#define IRC_RPL_STATSCOMMANDS " 212"
#define IRC_RPL_STATSCLINE " 213"
#define IRC_RPL_STATSNLINE " 214"
#define IRC_RPL_STATSILINE " 215"
#define IRC_RPL_STATSKLINE " 216"
#define IRC_RPL_STATSQLINE " 217"
#define IRC_RPL_STATSYLINE " 218"
#define IRC_RPL_ENDOFSTATS " 219"
#define IRC_RPL_UMODEIS " 221"
#define IRC_RPL_SERVICEINFO " 231"
#define IRC_RPL_ENDOFSERVICES " 232"
#define IRC_RPL_SERVICE " 233"
#define IRC_RPL_SERVLIST " 234"
#define IRC_RPL_SERVLISTEND " 235"
#define IRC_RPL_STATSIAUTH " 239"
#define IRC_RPL_STATSVLINE " 240"
#define IRC_RPL_STATSLLINE " 241"
#define IRC_RPL_STATSUPTIME " 242"
#define IRC_RPL_STATSOLINE " 243"
#define IRC_RPL_STATSHLINE " 244"
#define IRC_RPL_STATSSLINE " 245"
#define IRC_RPL_STATSPING " 246"
#define IRC_RPL_STATSBLINE " 247"
#define IRC_RPL_STATSDEFINE " 248"
#define IRC_RPL_STATSDEBUG " 249"
#define IRC_RPL_STATSDLINE " 250"
#define IRC_RPL_LUSERCLIENT " 251"
#define IRC_RPL_LUSEROP " 252"
#define IRC_RPL_LUSERUNKNOWN " 253"
#define IRC_RPL_LUSERCHANNELS " 254"
#define IRC_RPL_LUSERME " 255"
#define IRC_RPL_ADMINME " 256"
#define IRC_RPL_ADMINLOC1 " 257"
#define IRC_RPL_ADMINLOC2 " 258"
#define IRC_RPL_ADMINEMAIL " 259"
#define IRC_RPL_TRACELOG " 261"
#define IRC_RPL_TRACEEND " 262"
#define IRC_RPL_TRYAGAIN " 263"
#define IRC_RPL_LOCALUSERS " 265"
#define IRC_RPL_GLOBALUSERS " 266"
#define IRC_RPL_NONE " 300"
#define IRC_RPL_AWAY " 301"
#define IRC_RPL_USERHOST " 302"
#define IRC_RPL_ISON " 303"
#define IRC_RPL_TEXT " 304"
#define IRC_RPL_UNAWAY " 305"
#define IRC_RPL_NOWAWAY " 306"
#define IRC_RPL_WHOISUSER " 311"
#define IRC_RPL_WHOISSERVER " 312"
#define IRC_RPL_WHOISOPERATOR " 313"
#define IRC_RPL_WHOWASUSER " 314"
#define IRC_RPL_ENDOFWHO " 315"
#define IRC_RPL_WHOISCHANOP " 316"
#define IRC_RPL_WHOISIDLE " 317"
#define IRC_RPL_ENDOFWHOIS " 318"
#define IRC_RPL_WHOISCHANNELS " 319"
#define IRC_RPL_LISTSTART " 321"
#define IRC_RPL_LIST " 322"
#define IRC_RPL_LISTEND " 323"
#define IRC_RPL_CHANNELMODEIS " 324"
#define IRC_RPL_UNIQOPIS " 325"
#define IRC_RPL_NOTOPIC " 331"
#define IRC_RPL_TOPIC " 332"
#define IRC_RPL_TOPIC_WHO_TIME " 333"
#define IRC_RPL_INVITING " 341"
#define IRC_RPL_SUMMONING " 342"
#define IRC_RPL_REOPLIST " 344"
#define IRC_RPL_ENDOFREOPLIST " 345"
#define IRC_RPL_INVITELIST " 346"
#define IRC_RPL_ENDOFINVITELIST " 347"
#define IRC_RPL_EXCEPTLIST " 348"
#define IRC_RPL_ENDOFEXCEPTLIST " 349"
#define IRC_RPL_VERSION " 351"
#define IRC_RPL_WHOREPLY " 352"
#define IRC_RPL_NAMREPLY " 353"
#define IRC_RPL_KILLDONE " 361"
#define IRC_RPL_CLOSING " 362"
#define IRC_RPL_CLOSEEND " 363"
#define IRC_RPL_LINKS " 364"
#define IRC_RPL_ENDOFLINKS " 365"
#define IRC_RPL_ENDOFNAMES " 366"
#define IRC_RPL_BANLIST " 367"
#define IRC_RPL_ENDOFBANLIST " 368"
#define IRC_RPL_ENDOFWHOWAS " 369"
#define IRC_RPL_INFO " 371"
#define IRC_RPL_MOTD " 372"
#define IRC_RPL_INFOSTART " 373"
#define IRC_RPL_ENDOFINFO " 374"
#define IRC_RPL_MOTDSTART " 375"
#define IRC_RPL_ENDOFMOTD " 376"
#define IRC_RPL_YOUREOPER " 381"
#define IRC_RPL_REHASHING " 382"
#define IRC_RPL_YOURESERVICE " 383"
#define IRC_RPL_MYPORTIS " 384"
#define IRC_RPL_NOTOPERANYMORE " 385"
#define IRC_RPL_TIME " 391"
#define IRC_RPL_USERSSTART " 392"
#define IRC_RPL_USERS " 393"
#define IRC_RPL_ENDOFUSERS " 394"
#define IRC_RPL_NOUSERS " 395"
#define IRC_ERR_NOSUCHNICK " 401"
#define IRC_ERR_NOSUCHSERVER " 402"
#define IRC_ERR_NOSUCHCHANNEL " 403"
#define IRC_ERR_CANNOTSENDTOCHAN " 404"
#define IRC_ERR_TOOMANYCHANNELS " 405"
#define IRC_ERR_WASNOSUCHNICK " 406"
#define IRC_ERR_TOOMANYTARGETS " 407"
#define IRC_ERR_NOSUCHSERVICE " 408"
#define IRC_ERR_NOORIGIN " 409"
#define IRC_ERR_NORECIPIENT " 411"
#define IRC_ERR_NOTEXTTOSEND " 412"
#define IRC_ERR_NOTOPLEVEL " 413"
#define IRC_ERR_WILDTOPLEVEL " 414"
#define IRC_ERR_BADMASK " 415"
#define IRC_ERR_TOOMANYMATCHES " 416"
#define IRC_ERR_UNKNOWNCOMMAND " 421"
#define IRC_ERR_NOMOTD " 422"
#define IRC_ERR_NOADMININFO " 423"
#define IRC_ERR_FILEERROR " 424"
#define IRC_ERR_NONICKNAMEGIVEN " 431"
#define IRC_ERR_ERRONEOUSNICKNAME " 432"
#define IRC_ERR_NICKNAMEINUSE " 433"
#define IRC_ERR_SERVICENAMEINUSE " 434"
#define IRC_ERR_SERVICECONFUSED " 435"
#define IRC_ERR_NICKCOLLISION " 436"
#define IRC_ERR_UNAVAILRESOURCE " 437"
#define IRC_ERR_USERNOTINCHANNEL " 441"
#define IRC_ERR_NOTONCHANNEL " 442"
#define IRC_ERR_USERONCHANNEL " 443"
#define IRC_ERR_NOLOGIN " 444"
#define IRC_ERR_SUMMONDISABLED " 445"
#define IRC_ERR_USERSDISABLED " 446"
#define IRC_ERR_NOTREGISTERED " 451"
#define IRC_ERR_NEEDMOREPARAMS " 461"
#define IRC_ERR_ALREADYREGISTRED " 462"
#define IRC_ERR_NOPERMFORHOST " 463"
#define IRC_ERR_PASSWDMISMATCH " 464"
#define IRC_ERR_YOUREBANNEDCREEP " 465"
#define IRC_ERR_YOUWILLBEBANNED " 466"
#define IRC_ERR_KEYSET " 467"
#define IRC_ERR_CHANNELISFULL " 471"
#define IRC_ERR_UNKNOWNMODE " 472"
#define IRC_ERR_INVITEONLYCHAN " 473"
#define IRC_ERR_BANNEDFROMCHAN " 474"
#define IRC_ERR_BADCHANNELKEY " 475"
#define IRC_ERR_BADCHANMASK " 476"
#define IRC_ERR_NOCHANMODES " 477"
#define IRC_ERR_BANLISTFULL " 478"
#define IRC_ERR_NOPRIVILEGES " 481"
#define IRC_ERR_CHANOPRIVSNEEDED " 482"
#define IRC_ERR_CANTKILLSERVER " 483"
#define IRC_ERR_RESTRICTED " 484"
#define IRC_ERR_UNIQOPRIVSNEEDED " 485"
#define IRC_ERR_NOOPERHOST " 491"
#define IRC_ERR_NOSERVICEHOST " 492"
#define IRC_ERR_STATSKLINE " 499"
#define IRC_ERR_UMODEUNKNOWNFLAG " 501"
#define IRC_ERR_USERSDONTMATCH " 502"
#define IRC_RPL_ETRACEFULL " 708"
#define IRC_RPL_ETRACEEN " 759"

#include <string>
#include <ctime>
#include "IrcUser.hpp"

namespace ft_irc {

class IrcReply {
	public:
		IrcReply(const std::string& irc, const std::string& version);
		std::string rpl_welcome(const User&);
		std::string rpl_yourhost(const User&);
		std::string rpl_created(const User&);
		std::string rpl_myinfo(const User&);
		std::string rpl_isupport(const User&);
		std::string rpl_map(const User&);
		std::string rpl_mapstart(const User&);
		std::string rpl_hello(const User&);
		std::string rpl_yourid(const User&);
		std::string rpl_savenick(const User&);
		std::string rpl_tracelink(const User&);
		std::string rpl_traceconnecting(const User&);
		std::string rpl_tracehandshake(const User&);
		std::string rpl_traceunknown(const User&);
		std::string rpl_traceoperator(const User&);
		std::string rpl_traceuser(const User&);
		std::string rpl_traceserver(const User&);
		std::string rpl_traceservice(const User&);
		std::string rpl_tracenewtype(const User&);
		std::string rpl_traceclass(const User&);
		std::string rpl_statslinkinfo(const User&);
		std::string rpl_statscommands(const User&);
		std::string rpl_statscline(const User&);
		std::string rpl_statsnline(const User&);
		std::string rpl_statsiline(const User&);
		std::string rpl_statskline(const User&);
		std::string rpl_statsqline(const User&);
		std::string rpl_statsyline(const User&);
		std::string rpl_endofstats(const User&);
		std::string rpl_umodeis(const User&);
		std::string rpl_serviceinfo(const User&);
		std::string rpl_endofservices(const User&);
		std::string rpl_servise(const User&);
		std::string rpl_servlist(const User&);
		std::string rpl_servlistend(const User&);
		std::string rpl_statsiauth(const User&);
		std::string rpl_statsvline(const User&);
		std::string rpl_statslline(const User&);
		std::string rpl_statsuptime(const User&);
		std::string rpl_statsoline(const User&);
		std::string rpl_statshline(const User&);
		std::string rpl_statssline(const User&);
		std::string rpl_statsping(const User&);
		std::string rpl_statsbline(const User&);
		std::string rpl_statsdefine(const User&);
		std::string rpl_statsdebug(const User&);
		std::string rpl_statsdline(const User&);
		std::string rpl_luserclient(const User&);
		std::string rpl_luserop(const User&);
		std::string rpl_luserunknown(const User&);
		std::string rpl_luserchannels(const User&);
		std::string rpl_luserme(const User&);
		std::string rpl_adminme(const User&);
		std::string rpl_adminloc1(const User&);
		std::string rpl_adminloc2(const User&);
		std::string rpl_adminemail(const User&);
		std::string rpl_tracelog(const User&);
		std::string rpl_traceend(const User&);
		std::string rpl_tryagain(const User&);
		std::string rpl_localusers(const User&);
		std::string rpl_globalusers(const User&);
		std::string rpl_none(const User&);
		std::string rpl_away(const User&);
		std::string rpl_userhost(const User&);
		std::string rpl_ison(const User&);
		std::string rpl_text(const User&);
		std::string rpl_unaway(const User&);
		std::string rpl_nowaway(const User&);
		std::string rpl_whoisuser(const User&);
		std::string rpl_whoisserver(const User&);
		std::string rpl_whoisoperator(const User&);
		std::string rpl_whowasuser(const User&);
		std::string rpl_endofwho(const User&);
		std::string rpl_whoischanop(const User&);
		std::string rpl_whoisidle(const User&);
		std::string rpl_endofwhois(const User&);
		std::string rpl_whoischannels(const User&);
		std::string rpl_liststart(const User&);
		std::string rpl_list(const User&);
		std::string rpl_listend(const User&);
		std::string rpl_channelmodeis(const User&);
		std::string rpl_uniqopis(const User&);
		std::string rpl_notopic(const User&);
		std::string rpl_topic(const User&);
		std::string rpl_topic_who_time(const User&);
		std::string rpl_inviting(const User&);
		std::string rpl_summoning(const User&);
		std::string rpl_reoplist(const User&);
		std::string rpl_endofreoplist(const User&);
		std::string rpl_invitelist(const User&);
		std::string rpl_endofinvitelist(const User&);
		std::string rpl_exceptlist(const User&);
		std::string rpl_endofexceptlist(const User&);
		std::string rpl_version(const User&);
		std::string rpl_whoreply(const User&);
		std::string rpl_namreply(const User&);
		std::string rpl_killdone(const User&);
		std::string rpl_closing(const User&);
		std::string rpl_closeend(const User&);
		std::string rpl_links(const User&);
		std::string rpl_endoflinks(const User&);
		std::string rpl_endofnames(const User&);
		std::string rpl_banlist(const User&);
		std::string rpl_endofbanlist(const User&);
		std::string rpl_endofwhowas(const User&);
		std::string rpl_info(const User&);
		std::string rpl_motd(const User&);
		std::string rpl_infostart(const User&);
		std::string rpl_endofinfo(const User&);
		std::string rpl_motdstart(const User&);
		std::string rpl_endofmotd(const User&);
		std::string rpl_youreoper(const User&);
		std::string rpl_rehashing(const User&);
		std::string rpl_youreservice(const User&);
		std::string rpl_myportis(const User&);
		std::string rpl_notoperanymore(const User&);
		std::string rpl_time(const User&);
		std::string rpl_usersstart(const User&);
		std::string rpl_users(const User&);
		std::string rpl_endofusers(const User&);
		std::string rpl_nousers(const User&);
		std::string err_nosuchnick(const User&);
		std::string err_nosuchserver(const User&);
		std::string err_nosuchchannel(const User&);
		std::string err_cannotsendtochan(const User&);
		std::string err_toomanychannels(const User&);
		std::string err_wasnosuchnick(const User&);
		std::string err_toomanytargets(const User&);
		std::string err_nosuchservice(const User&);
		std::string err_noorigin(const User&);
		std::string err_norecipient(const User&);
		std::string err_notexttosend(const User&);
		std::string err_notoplevel(const User&);
		std::string err_wildtoplevel(const User&);
		std::string err_badmask(const User&);
		std::string err_toomanymatches(const User&);
		std::string err_unknowncommand(const User&);
		std::string err_nomotd(const User&);
		std::string err_noadmininfo(const User&);
		std::string err_fileerror(const User&);
		std::string err_nonicknamegiven(const User&);
		std::string err_erroneousnickname(const User&);
		std::string err_nicknameinuse(const User&);
		std::string err_servicenameinuse(const User&);
		std::string err_serviceconfused(const User&);
		std::string err_nickcollision(const User&);
		std::string err_unavailresource(const User&);
		std::string err_usernotinchannel(const User&);
		std::string err_notonchannel(const User&);
		std::string err_useronchannel(const User&);
		std::string err_nologin(const User&);
		std::string err_summondisabled(const User&);
		std::string err_usersdisabled(const User&);
		std::string err_notregistered(const User&);
		std::string err_needmoreparams(const User&);
		std::string err_alreadyregistred(const User&);
		std::string err_nopermforhost(const User&);
		std::string err_passwdmismatch(const User&);
		std::string err_yourebannedcreep(const User&);
		std::string err_youwillbebanned(const User&);
		std::string err_keyset(const User&);
		std::string err_channelisfull(const User&);
		std::string err_unknownmode(const User&);
		std::string err_inviteonlychan(const User&);
		std::string err_bannedfromchan(const User&);
		std::string err_badchannelkey(const User&);
		std::string err_badchanmask(const User&);
		std::string err_nochanmodes(const User&);
		std::string err_banlistfull(const User&);
		std::string err_noprivileges(const User&);
		std::string err_chanoprivsneeded(const User&);
		std::string err_cantkillserver(const User&);
		std::string err_restricted(const User&);
		std::string err_uniqoprivsneeded(const User&);
		std::string err_nooperhost(const User&);
		std::string err_noservicehost(const User&);
		std::string err_statskline(const User&);
		std::string err_umodeunknownflag(const User&);
		std::string err_usersdontmatch(const User&);
		std::string rpl_etracefull(const User&);
		std::string rpl_etraceen(const User&);
	private:
		std::string irc;
		std::string version;
		std::clock_t clock;
};
}
