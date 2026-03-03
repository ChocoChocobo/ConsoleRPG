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
/// ‘ункци¤ отвечает за отображение загрузки игры.
/// </summary>
/// <param name="progressLevel">ƒлинна progress bar'а</param>
/// <param name="time">¬рем¤, до котого будет идти загрузка</param>
/// <param name="message">—ообщение, которое будет писатьс¤ при загрузке. „аще всего: "«агрузка"</param>
/// <param name="symbol">—инвол, который будет отобразатьс¤ в "progress bar". „аще всего: '#'</param>
void ShowProgressBar(double progressLevel, int time, const string& message, char symbol);

/// <summary>
/// ‘ункци¤ отвечает за отображение точек, которые будут по¤вл¤тьс¤ и пропадать, имитиру¤ загрузку
/// </summary>
/// <param name="pauseTime">¬рем¤, с какой частотой будут мигать точки (в миллисекундах)</param>
/// <param name="duration">—колько раз отработает цикл мигани¤ точек</param>
void ShowLoadingDots(chrono::milliseconds pauseTime, int duration);