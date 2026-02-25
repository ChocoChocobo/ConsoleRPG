#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>

using namespace std;

struct Item
{
	string name;
	string description;
	int price;
	int quantity;

	Item(string _name, string _description, int _price, int _quantity);
	void ShowInfo();
	bool BuyItem(int playerGold);
};

#endif