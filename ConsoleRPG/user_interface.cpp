#include "user_interface.h"

void ShowProgressBar(double progressLevel, int time, const string& message, char symbol)
{
	system("cls");

	string progressBar;

	cout << message << endl;

	for (double percentage = 0; percentage <= 100; percentage += progressLevel)
	{
		progressBar.insert(0, 1, symbol);
		cout << "\r [" << ceil(percentage) << '%' << "] " << progressBar;
		this_thread::sleep_for(chrono::milliseconds(time));
	}
	cout << "\n\n";

	system("cls");
}