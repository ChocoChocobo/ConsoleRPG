#ifndef SHOP_H
#define SHOP_H
#include <string>
#include <vector>
#include "item.h"
#include "character.h"

using namespace std;

// Список предметов только с названиями
// Варианты выбора: по индексу предмета, последнее  0
// При выборе предмета отображается его описание
// Принять отменить кнопки
struct Shop
{
	string name;
	vector<Item>& availableItems;
	Character& player;

	Shop(Character& _player, vector<Item>& _availableItems, string _name = "Дремучая Ива");
	bool ShowItems();
	//Item BuyItem(Item _chosenItem);
};

#endif