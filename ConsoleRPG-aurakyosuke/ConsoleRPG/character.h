#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>
#include "item.h"
#include "dice.h"
#include "user_interface.h"

using namespace std;

struct Characteristics
{
	int strength;
	int dexterity;
	int constitution;
	int wisdom;
	int intelligence;
	int charisma;
	int armorClass;

	Characteristics();
	Characteristics(int _strength, int dexterity, int constitution, int wisdom, int intelligence, int charisma, int armorClass);
	int CountModificator(int characteristic);
	void PrintCharacteristics();
};

struct Appearance
{
	string skinColor;
	string hairColor;
};


class Character
{
private:
	
	string name;
	Appearance appearance;

	int health;
	int maxHealth;
	int healthFlasks;

	int damageFace;
	int specialCooldown;

	int gold;

	vector<Item> inventory;

	Characteristics characteristics;

	int uniqueAbilityDifficulty;
	bool minionSpawned = false;
	Character* minion = nullptr;

public:
	
	Character();
	Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold, Character& _minion, int _uniqueAbilityDifficulty);
	Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold);



	string GetName() const;
	int GetHealth() const;
	int GetMaxHealth() const;
	int GetGold() const;

	void SetHealth(int value);
	void SetGold(int value);

	void PrintStatus();
	void RemoveGold(int amount);
	void AddGold(int amount);
	bool BuyItem(int cost);
	void IncreaseHealth(int amount);
	void DecreaseHealth(int amount);
	bool CheckFleeSuccess(int difficulty);

	void BasicAttack(Character& other);
	void SpecialAttack();
	void ShowInventory();
	void Heal(int difficulty);
	bool Flee(Character& other);
};

#endif
