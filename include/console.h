#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>

#define PRINT_ALL 0         // Зарезервированно. Подходит для всего
#define PRINT_DEGUB 1       // Печатать все возможные логи
#define PRINT_LOG 2         // Печатать основные логи. Не печатать частые и мешающие логи
#define PRINT_GENERAL 3     // Печатать только критическую информацию о состоянии сервера

class Console
{
public:
    void static set_log_level(int level);
    void static log(std::string msg, int level = PRINT_DEGUB);
private:
    static int print_level; // default = 0
};

void abort();

#endif
