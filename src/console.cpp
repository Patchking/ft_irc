#include "Console.hpp"

namespace ft_irc {

void Console::set_log_level(Console::Level level)
{
	m_level = level;
}

Console::Level Console::m_level = Console::ALL;
}
