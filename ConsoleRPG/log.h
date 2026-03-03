#pragma once
#include <iostream>
using namespace std;

/// <summary>
/// Оно не надо лол. Отвечает за логирование, которое можно делать cout'ом
/// </summary>
/// <param name="message">Отвечает за сообщение в консоли</param>
/// <param name="value">Отвечат за значение цифры, хз, может код ошибки</param>
void PrintConsoleMessage(string message, int value)
{
	cout << " " << message << value << endl;
}