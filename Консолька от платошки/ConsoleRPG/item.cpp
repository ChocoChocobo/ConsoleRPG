#include "item.h"

Item::Item(string _name, string _description, int _price, int _quantity)
{
	name = _name;
	description = _description;
	price = _price;
	quantity = _quantity;
}

void Item::ShowInfo()
{
	cout << "Название: " << name << "." << endl;
	cout << "Описание: " << description << "." << endl;
	cout << "Стоимость: " << price << " голды." << endl;
	cout << "Количество: " << quantity << "." << endl;

}

bool Item::BuyItem(int playerGold)
{
	return false;
}