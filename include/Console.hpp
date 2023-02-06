#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
namespace ft_irc {
class Console {
public:
	enum Level {
		 ALL = 0         // Зарезервированно. Подходит для всего
		, DEBUG = 1       // Печатать все возможные логи
		, LOG = 2         // Печатать основные логи. Не печатать частые и мешающие логи
		, GENERAL = 3     // Печатать только критическую информацию о состоянии сервера
	};
public:
	void static set_log_level(Level level);
	//c++11 parody on template <class... Args>
	template<class Arg>
	bool static log(const Arg& arg, Level level = DEBUG) {
		if (level >= m_level)
			std::cout << arg << '\n';
		return std::cout.good();
	}
	template<class Arg1, class Arg2>
	bool static log(const Arg1& arg1
			, const Arg2& arg2
			, Level level = DEBUG) {
		pre_log();
		if (level >= m_level)
			std::cout << arg1 << arg2 << '\n';
		post_log();
		return std::cout.good();
	}
	template<class Arg1
		, class Arg2
		, class Arg3>
	bool static log(const Arg1& arg1
			, const Arg2& arg2
			, const Arg3& arg3
			, Level level = DEBUG) {
		pre_log();
		if (level >= m_level)
			std::cout << arg1 << arg2 << arg3 << '\n';
		post_log();
		return std::cout.good();
	}
	template<class Arg1
		, class Arg2
		, class Arg3
		, class Arg4>
	bool static log(const Arg1& arg1
			, const Arg2& arg2
			, const Arg3& arg3
			, const Arg4& arg4
			, Level level = DEBUG) {
		pre_log();
		if (level >= m_level)
			std::cout << arg1 << arg2 << arg3 << arg4 << '\n';
		post_log();
		return std::cout.good();
	}
	template<class Arg1
		, class Arg2
		, class Arg3
		, class Arg4
		, class Arg5>
	bool static log(const Arg1& arg1
			, const Arg2& arg2
			, const Arg3& arg3
			, const Arg4& arg4
			, const Arg5& arg5
			, Level level = DEBUG) {
		pre_log();
		if (level >= m_level)
			std::cout << arg1 << arg2 << arg3 << arg4 << arg5 << '\n';
		post_log();
		return std::cout.good();
	}
	template<class Arg1
		, class Arg2
		, class Arg3
		, class Arg4
		, class Arg5
		, class Arg6>
	bool static log(const Arg1& arg1
			, const Arg2& arg2
			, const Arg3& arg3
			, const Arg4& arg4
			, const Arg5& arg5
			, const Arg6& arg6
			, Level level = DEBUG) {
		pre_log();
		if (level >= m_level)
			std::cout << arg1 << arg2 << arg3 << arg4 << arg5 << arg6 << '\n';
		post_log();
		return std::cout.good();
	}
	template<class Arg1
		, class Arg2
		, class Arg3
		, class Arg4
		, class Arg5
		, class Arg6
		, class Arg7>
	bool static log(const Arg1& arg1
			, const Arg2& arg2
			, const Arg3& arg3
			, const Arg4& arg4
			, const Arg5& arg5
			, const Arg6& arg6
			, const Arg7& arg7
			, Level level = DEBUG) {
		pre_log();
		if (level >= m_level)
			std::cout << arg1 << arg2 << arg3 << arg4 << arg5 << arg6
				<< arg7 << '\n';
		post_log();
		return std::cout.good();
	}
	template<class Arg1
		, class Arg2
		, class Arg3
		, class Arg4
		, class Arg5
		, class Arg6
		, class Arg7
		, class Arg8>
	bool static log(const Arg1& arg1
			, const Arg2& arg2
			, const Arg3& arg3
			, const Arg4& arg4
			, const Arg5& arg5
			, const Arg6& arg6
			, const Arg7& arg7
			, const Arg8& arg8
			, Level level = DEBUG) {
		pre_log();
		if (level >= m_level)
			std::cout << arg1 << arg2 << arg3 << arg4 << arg5 << arg6
				<< arg7 << arg8 << '\n';
		post_log();
		return std::cout.good();
	}
	template<class Arg1
		, class Arg2
		, class Arg3
		, class Arg4
		, class Arg5
		, class Arg6
		, class Arg7
		, class Arg8
		, class Arg9>
	bool static log(const Arg1& arg1
			, const Arg2& arg2
			, const Arg3& arg3
			, const Arg4& arg4
			, const Arg5& arg5
			, const Arg6& arg6
			, const Arg7& arg7
			, const Arg8& arg8
			, const Arg9& arg9
			, Level level = DEBUG) {
		pre_log();
		if (level >= m_level)
			std::cout << arg1 << arg2 << arg3 << arg4 << arg5 << arg6
				<< arg7 << arg8 << arg9 << '\n';
		post_log();
		return std::cout.good();
	}
	template<class Arg1
		, class Arg2
		, class Arg3
		, class Arg4
		, class Arg5
		, class Arg6
		, class Arg7
		, class Arg8
		, class Arg9
		, class Arg10>
	bool static log(const Arg1& arg1
			, const Arg2& arg2
			, const Arg3& arg3
			, const Arg4& arg4
			, const Arg5& arg5
			, const Arg6& arg6
			, const Arg7& arg7
			, const Arg8& arg8
			, const Arg9& arg9
			, const Arg10& arg10
			, Level level = DEBUG) {
		pre_log();
		if (level >= m_level)
			std::cout << arg1 << arg2 << arg3 << arg4 << arg5 << arg6
				<< arg7 << arg8 << arg9 << arg10 << '\n';
		post_log();
		return std::cout.good();
	}
private:
	//Если нужно сделать что-то до или после логирования
	//, то логику можно прописать сюда.
	static void pre_log(){}
	static void post_log(){}
private:
	static Level m_level; // default = 0
};
}
#endif
