#pragma once
#include "IrcUser.hpp"
#include <map>
#include <vector>
#include <string>

#include <Console.hpp>

namespace ft_irc {
enum ID_ENUM{ID};
enum USERNAME_ENUM{USERNAME};
enum NICKNAME_ENUM{NICKNAME};
enum SERVERNAME_ENUM{SERVERNAME};
enum HOSTNAME_ENUM{HOSTNAME};
enum REALNAME_ENUM{REALNAME};
enum PASSWORD_ENUM{PASSWORD};
enum MODE_ENUM{MODE};
class IrcUsers {
	public:
		class PipelineUser;

		template<class T>
		class PipelineUserAssign {
			public:
			PipelineUserAssign(PipelineUser& user, T& a):user(user),a(a){}
			PipelineUser& operator ()(const T& a) {
				this->a = a;
				return user;
			}
			private:
			PipelineUser& user;
			T& a;
		};

		class PipelineUser {
			public:
			typedef void(IrcUsers::*callback_type)(PipelineUser&);
			public:
			PipelineUser(IrcUsers& users, User& user, callback_type callback
					, int id = 0)
				: users(users)
				, user(user)
				, callback(callback)
				, id(id){
			};
			PipelineUserAssign<int> operator [] (ID_ENUM) {
				return PipelineUserAssign<int>(*this, id);
			}
			PipelineUserAssign<std::string> operator [] (USERNAME_ENUM) {
				return PipelineUserAssign<std::string>(*this, user.username);
			}
			PipelineUserAssign<std::string> operator [] (NICKNAME_ENUM) {
				return PipelineUserAssign<std::string>(*this, user.nickname);
			}
			PipelineUserAssign<std::string> operator [] (SERVERNAME_ENUM) {
				return PipelineUserAssign<std::string>(*this, user.servername);
			}
			PipelineUserAssign<std::string> operator [] (REALNAME_ENUM) {
				return PipelineUserAssign<std::string>(*this, user.realname);
			}
			PipelineUserAssign<std::string> operator [] (HOSTNAME_ENUM) {
				return PipelineUserAssign<std::string>(*this, user.hostname);
			}
			PipelineUserAssign<std::string> operator [] (PASSWORD_ENUM) {
				return PipelineUserAssign<std::string>(*this, user.password);
			}
			PipelineUserAssign<User::Mode> operator [] (MODE_ENUM) {
				return PipelineUserAssign<User::Mode>(*this, user.mode);
			}
			~PipelineUser() {
				(users.*callback)(*this);
			};
			private:
			friend class IrcUsers;
			IrcUsers& users;
			User& user;
			callback_type callback;
			int id;
		};

		enum {
			SUCCESS = 0
			, NICK_ALREADY_USED = 0x1
			, ID_ALREADY_USED = 0x2
			, ID_NOT_USED = 0x4
			, NOT_FULL_DATA = 0x8
		};

	public:
		typedef std::map<std::string, int> users_map_type;
		typedef std::vector<User> container_type;

	public:
		void unlog(int id) {
			if (id < 0 || m_users.size() <= static_cast<size_t>(id)) {
				return;
			}
			User& user = m_users[id];
			users_map_type::iterator iterator = m_usersMap.find(user.nickname);
			if (iterator != m_usersMap.end())
				m_usersMap.erase(iterator);
			clearUser(user);
		}

		PipelineUser changeUser(int id) {
			ensureUsersSize(id);
			m_tempid = id;/*
			if (id < 0 || m_users.size() < static_cast<size_t>(id)) {
				m_logStatus = ID_NOT_USED;
				return PipelineUser(*this, m_TempUser, &IrcUsers::ignore);
			}*/
			User& user = m_users[id];
			/*
			if (User::DISCONNECTED == user.mode) {
				m_logStatus = ID_NOT_USED;
				return PipelineUser(*this, m_TempUser, &IrcUsers::ignore);
			}*/
			m_TempUser.nickname = user.nickname;
			return PipelineUser(*this, user, &IrcUsers::changeUserApply, id);
		}

		PipelineUser logUser() {
			clearUser(m_TempUser);
			return PipelineUser(*this, m_TempUser, &IrcUsers::apply);
		}

		int logStatus() {
			return m_logStatus;
		}

		int find(const std::string& nick) const {
			users_map_type::const_iterator iterator = m_usersMap.find(nick);
			if (m_usersMap.end() == iterator) {
				return -1;
			}
			return iterator->second;
		}

		User& operator[](int id) {
			ensureUsersSize(id);
			return m_users[id];
		}

		const User& operator[](int id) const {
			return m_users.at(id);
		}

		const User& getTemp() const {
			return m_TempUser;
		}

		bool connected(int id) const {
			if (id < 0)
				return false;
			if (static_cast<size_t>(id) > m_users.size())
				return false;
			return m_users[id].mode != User::DISCONNECTED;
		}

		void online(int id) {
			ensureUsersSize(id);
			m_users[id].mode = User::REGULAR;
		}

		void offline(int id) {
			ensureUsersSize(id);
			m_users[id].mode = User::DISCONNECTED;
		}

	private:
		void ignore(PipelineUser& pipeling) {
			(void)pipeling;
		}

		void changeUserApply(PipelineUser& pipeling) {
			m_logStatus = SUCCESS;
			if (pipeling.id != m_tempid) {
				pipeling.id = m_tempid;
				ensureUsersSize(pipeling.id);
				if (m_users[pipeling.id].mode != User::DISCONNECTED)
					m_logStatus |= ID_ALREADY_USED;
			}
			if (m_TempUser.nickname != pipeling.user.nickname) {
				users_map_type::iterator iterator
					= m_usersMap.find(pipeling.user.nickname);
				if (iterator != m_usersMap.end()) {
					m_logStatus |= NICK_ALREADY_USED;
					pipeling.user.nickname = m_TempUser.nickname;
				}
				else {
					users_map_type::iterator iterator
						= m_usersMap.find(m_TempUser.nickname);
					if (iterator != m_usersMap.end())
						m_usersMap.erase(iterator);
					m_usersMap[pipeling.user.nickname]
						= pipeling.id;
				}
			}
		}

		void apply(PipelineUser& pipeling) {
			if (-1 < find(pipeling.user.nickname)) {
				m_logStatus = NICK_ALREADY_USED;
				return;
			}
			ensureUsersSize(pipeling.id);
			User& user = m_users[pipeling.id];
			ensureUsersSize(pipeling.id);
			if (user.mode != User::DISCONNECTED) {
				m_logStatus = ID_ALREADY_USED;
				return;
			}
			copyNonEmpty(user, m_TempUser);
			if (pipeling.user.nickname.size())
				m_usersMap[pipeling.user.nickname]
					= pipeling.id;
			m_logStatus = SUCCESS;
		}

		void ensureUsersSize(int size) {
			if (size < 0)
				return;
			++size;
			if (m_users.size() <= static_cast<size_t>(size)) {
				size_t new_size = m_users.size() << 1;
				new_size = new_size > static_cast<size_t>(size)
					? new_size : size;
				m_users.resize(new_size);
			}
		}

		static void copyNonEmpty(User& dest, User& src) {
			if (src.nickname.size())
				dest.nickname = src.nickname;
			if (src.hostname.size())
				dest.hostname = src.hostname;
			if (src.servername.size())
				dest.servername = src.servername;
			if (src.username.size())
				dest.username = src.username;
			if (src.realname.size())
				dest.realname = src.realname;
			dest.mode = src.mode;
		}

		static void clearUser(User& user) {
			user.nickname.clear();
			user.hostname.clear();
			user.servername.clear();
			user.username.clear();
			user.realname.clear();
			user.password.clear();
			user.mode = User::DISCONNECTED;
		}

	private:
		friend class IrcUsers::PipelineUser;
		container_type m_users;
		users_map_type m_usersMap;
		int m_logStatus;
		User m_TempUser;
		int m_tempid;
};
}
