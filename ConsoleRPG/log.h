#pragma once
#include <iostream>
using namespace std;

/// <summary>
/// Функция вывода сообщения в консоль с числовым значением.
/// Используется для логирования игровых событий [1, 2, 3, 4, 7, 8, 9].
/// </summary>
/// <param name="message">
/// Текст сообщения.
/// </param>
/// <param name="value">
/// Числовое значение, связанное с сообщением.
/// </param>
void PrintConsoleMessage(string message, int value)
{
    cout << " " << message << value << endl;
}