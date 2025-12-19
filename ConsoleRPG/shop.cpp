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
	int userInput;
	do
	{
		// Исправлено: Теперь вывод полного списка предметов будет выводиться всегда при выходе из какого-то предмета позже, что позволит видеть игроку предметы, которые ему доступны.
		if (availableItems.size() == 0) return false;
		cout << TOP_BORDER << endl;
		for (int i = 1; i <= availableItems.size(); i++)
		{
			cout << i << ". " << availableItems[i - 1].name << "." << endl;
		}

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

				// Исправлено: Теперь с помощью оператора присваивания (=) для availableItems[userInput - 1].quantity присваивается availableItems[userInput - 1].quantity - 1, а не просто считает availableItems[userInput - 1].quantity - 1, как было раньше.
				availableItems[userInput - 1].quantity -= 1;
				if (availableItems[userInput - 1].quantity <= 0)
				{
					availableItems.erase(availableItems.begin() + userInput - 1);
				}
			}
			// Исправлено: Теперь в условии nestedUserInput, который и нужен, что бы выйти из данного цикла, а не userInput, который был раньше. Так же после выхода консоль чиститься.
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