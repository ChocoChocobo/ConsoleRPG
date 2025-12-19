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
	// Переделать!
	if (availableItems.size() == 0) return false;
	cout << TOP_BORDER << endl;
	for (int i = 1; i <= availableItems.size(); i++)
	{
		cout << i << ". " << availableItems[i - 1].name << "." << endl;
	}

	int userInput;
	do
	{
		// 1. Виден весь список предметов
		// 2. Игрок может детально осмотреть предмет -> нажать кнопку купить или выход во все предметы
		// Прим.: предмет сразу добавляется в инвентарь
		cout << endl << "Введите номер предмета для его осмотра (или '0' для выхода): " << endl;
		cin >> userInput;

		if (userInput == 0) continue;
		while (true)
		{
			availableItems[userInput - 1].ShowInfo();
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
				cout << endl << "У игрока денег: " << player.gold << endl;

				availableItems[userInput - 1].quantity - 1;
				if (availableItems[userInput - 1].quantity <= 0)
				{
					availableItems.erase(availableItems.begin() + userInput - 1);
				}
			}
			else if (userInput == 0) break;
		}

	} while (userInput != 0);

	system("cls");
	return true;
}