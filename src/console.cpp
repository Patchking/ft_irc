#include "console.h"

int Console::print_level = 0;

void Console::set_log_level(int level)
{
    print_level = level;
}

void Console::log(std::string msg, int level)
{
    if (level >= print_level)
        std::cout << msg << std::endl;
}

void abort()
{
    exit(0);
}
