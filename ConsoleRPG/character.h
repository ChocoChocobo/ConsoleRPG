#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>
#include "item.h"
#include "dice.h"
#include "user_interface.h"
using namespace std;

struct Stats
{
	int armorClass;
};

struct Character
{
	string name;

	int health;
	int maxHealth;
	int healthFlasks;

	int damageFace;
	int specialCooldown;

	int gold;

	vector<Item> inventory;

	Stats stats;

	Character();
	Character(string _name, int _health, int _damageFace, int _specialCooldown, int _armorClass, int _startGold = 0);
	void PrintStatus();
	void AddGold(int amount);
	bool BuyItem(int cost);
	void BasicAttack(Character& other);
	void SpecialAttack();
	void ShowInventory();
	void IncreaseHealth(int amount);
	void DecreaseHealth(int amount);
	void Heal(int difficulty);
	bool Flee(Character& other);
	bool CheckFleeSuccess(int difficulty);
};

#endif