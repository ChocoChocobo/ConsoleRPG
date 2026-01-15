#include "user_interface.h"

void ShowProgressBar(int time, const string& message, char symbol)
{
	system("cls");

	string progressBar;
	const double PROGRESS_LEVEL = 1.42;

	cout << message << "\n\n";

	for (double percentage = 0; percentage <= 100; percentage += PROGRESS_LEVEL)
	{
		progressBar.insert(0, 1, symbol);
		cout << "\r [" << ceil(percentage) << '%' << "] " << progressBar;
		this_thread::sleep_for(chrono::milliseconds(time));
	}
	cout << "\n\n";

	system("cls");
}