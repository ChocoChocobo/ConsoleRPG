#include "shop.h"
#include "user_interface.h"
#include <iostream>

Shop::Shop(vector<Item> _availableItems, string _name)
{
	name = _name;
	availableItems = _availableItems;
}

bool Shop::ShowItems()
{
	// Я переделал
	if (availableItems.size() == 0) return false;
	cout << TOP_BORDER << endl;
	for (int i = 0; i < availableItems.size(); i++)
	{
		cout << i << ". " << availableItems[i].name << "." << endl;
	}

	int userInput;
	do
	{
		cout << endl << "Введите номер предмета для его осмотра (или '0' для выхода): ";
		cin >> userInput;

		availableItems[userInput].ShowInfo();

	} while (userInput != 0);

	return true;
}