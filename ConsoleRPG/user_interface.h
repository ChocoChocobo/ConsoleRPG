#pragma once
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>
#include <iostream>
using namespace std;

#define TOP_BORDER "======================================="
#define SEPARATOR_LINE "---------------------------------------"
#define PAUSE_5_SECONDS this_thread::sleep_for(chrono::seconds(5))
#define PAUSE_1_SECONDS this_thread::sleep_for(chrono::seconds(1))

/// <summary>
/// Функция отображения индикатора прогресса в консоли.
/// Визуализирует процесс выполнения действия [1, 2, 3, 4, 7, 8, 9].
/// </summary>
/// <param name="progressLevel">
/// Уровень прогресса от 0 до 1.
/// </param>
/// <param name="time">
/// Время отображения прогресса.
/// </param>
/// <param name="message">
/// Сообщение, сопровождающее индикатор.
/// </param>
/// <param name="symbol">
/// Символ заполнения индикатора.
/// </param>
void ShowProgressBar(double progressLevel, int time, const string& message, char symbol);

/// <summary>
/// Функция отображения анимации загрузки в виде точек.
/// Используется для визуального ожидания выполнения процесса [1, 2, 3, 4, 7, 8, 9].
/// </summary>
/// <param name="pauseTime">
/// Время паузы между появлением точек.
/// </param>
/// <param name="duration">
/// Общая продолжительность анимации.
/// </param>
void ShowLoadingDots(chrono::milliseconds pauseTime, int duration);