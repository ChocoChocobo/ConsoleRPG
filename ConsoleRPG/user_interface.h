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

void ShowProgressBar(double progressLevel, int time, const string& message, char symbol);