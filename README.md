# ft_irc

Привет! Кажется, я закончил физическую часть. Возможно есть утечки, но вроде как оно вообще не виснет. 

Ты можешь редактировать класс User, а также встроить свою функцию обработки логики в обозначенное в файле server.cpp место (74 строка).
Желательно мой класс трогать как можно меньше, добавть свой класс как дочерний. И еще кое-что, для вывода в консоль использую Console::log по следующим правилам:

PRINT_DEBUG - мешающие логи
PRINT_LOG - полезные логи. Например, ответ от сервера клиенту.
PRINT_GENERAL - Критическую информацию о состоянии сервера. Например, ошибка перед вылетом сервера.

Если произошла критическая ошибка, заврешай работу сервера методом abort(). Если нужно подчистить за собой данные,
перегрузи функцию и очисть уже внутри функции.
