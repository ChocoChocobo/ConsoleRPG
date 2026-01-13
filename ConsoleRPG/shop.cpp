#include "shop.h"
#include "user_interface.h"
#include <iostream>

Shop::Shop(Character& _player, vector<Item>& _availableItems, string _name) : availableItems(_availableItems), player(_player), name(_name)
{
	/*availableItems = _availableItems;
	player = _player;
	name = _name;*/
}

bool Shop::ShowItems()
{
	system("cls");
	cout << "Добро пожаловать в магазин " << name << "!" << endl;
	int userInput;
	do
	{
		if (availableItems.size() == 0) return false;
		cout << TOP_BORDER << endl;
		for (int i = 1; i <= availableItems.size(); i++)
		{
			cout << i << ". " << availableItems[i - 1].name << "." << endl;
		}
		cout << endl << "У игрока деняк: " << player.gold << endl;

		cout << endl << "Введите номер предмета для его осмотра (или '0' для выхода): " << endl;
		cin >> userInput;

		if (userInput == 1301)
		{
			system("curl ASCII.live/can-you-hear-me");
		}

		if (userInput == 0) continue;
		while (true)
		{
			system("cls");
			availableItems[userInput - 1].ShowInfo();
			cout << endl << "У игрока деняк: " << player.gold << endl;
			Item chosenItem = availableItems[userInput - 1];
			cout << endl << "Введите 1 для покупки предмета (или '0' для выхода): " << endl;
			int nestedUserInput;
			cin >> nestedUserInput;
			if (nestedUserInput == 1)
			{
				if (player.gold < chosenItem.price)
				{
					cout << "Нет деняк!" << endl;
					continue;
				}

				player.gold -= chosenItem.price;
				player.inventory.push_back(chosenItem);
				cout << endl << "У игрока деняк: " << player.gold << endl;
				cout << endl;

				chosenItem.quantity -= 1;
				if (chosenItem.quantity <= 0)
				{
					availableItems.erase(availableItems.begin() + userInput - 1);
					system("cls");
					break;
				}
			}

			else if (nestedUserInput == 0)
			{
				system("cls");
				break;
			}
		}
	} while (userInput != 0);

	system("cls");
	return true;
}