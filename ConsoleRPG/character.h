#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>
#include <string>
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
	Characteristics(int _strength, int _dexterity, int _constitution, int _wisdom, int _intelligence, int _charisma, int _armorClass);
	int CountModificator(int characteristic);
	void PrintCharacteristics();
};

struct VisualsASCII
{
	void ShowSprite()
	{
		
	}
};
  
struct Appearance
{
	string skinColor;
	string hairColor;
	string eyeColor;
	string height;
	string bodyType;
	
	// Конструкторы
	Appearance();
	Appearance(string _skinColor, string _hairColor, string _eyeColor, string _height, string _bodyType);
	
	// Методы
	void PrintAppearance();
	void RandomizeAppearance();
};

struct Character
{
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

	VisualsASCII visualsASCII;

	// Конструкторы
	Character();
	Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold, Character& _minion, int _uniqueAbilityDifficulty);
	Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold);
	Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold, string _skinColor, string _hairColor, string _eyeColor, string _height, string _bodyType);
	
	// Методы
	void PrintStatus();
	void RemoveGold(int amount);
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
	void PrintFullInfo(); // Новый метод для вывода полной информации с внешностью
};

#endif
