#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>

using namespace std;

/// <summary>
/// Структура отвечает за реализацию объектов предмета и покубку предмета
/// </summary>
struct Item
{
	string name;
	string description;
	int price;
	int quantity;

	Item(string _name, string _description, int _price, int _quantity);
	void ShowInfo();
	/// <summary>
	/// Функция не отвечает ни за что. 
	/// </summary>
	/// <param name="playerGold">Количество денег у игрока</param>
	/// <returns>Возвращает false</returns>
	bool BuyItem(int playerGold);
};

#endif