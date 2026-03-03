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

/// <summary>
/// Структура, которая отвечает за магазин и вывод содержимого магазина в консоль
/// </summary>
struct Shop
{
	string name;
	vector<Item>& availableItems;
	Character& player;

	Shop(Character& _player, vector<Item>& _availableItems, string _name = "Дремучая Ива");

	/// <summary>
	/// Функция, которая отвечает за вывод содержимого магазина в консоль
	/// </summary>
	/// <returns>Если магазин пуст, вернёт false, иначе отработает и вернёт true</returns>
	bool ShowItems();

	//Item BuyItem(Item _chosenItem);
};

#endif