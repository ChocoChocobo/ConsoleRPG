#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>
#include "item.h"
#include "dice.h"
#include "user_interface.h"
using namespace std;

// В структуре character находятся все характеристики + описание перса
// Это редактируется в отдельном файле редакторе персонажа

// 1. Игрок распределяет сам статы - делаем. 8, 10, 12, 13, 14, 15
// 2. Программа бросает кубик на характеристики

// При внедрении классов необходимо определять тип куба и модификатора, используемого при атаке

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

// Спрайты персонажей находятся в файлах
// LoadSprite(enum state)
struct VisualsASCII
{
	void ShowSprite()
	{
		
	}
};
  
struct Appearance
{
	string physique;
	string skinColor;
	string eyeColor;
	string earShape;
	string hairType;
	string mouthType;
	string weapon;
	string armor;
	string tail;
	string navel;
	string skinTexture;
	string hands;
	string specialMarks;

	Appearance(string _physique, string _skinColor, string _eyeColor,
		string _earShape, string _hairType, string _mouthType,
		string _weapon, string _armor, string _tail, string _navel,
		string _skinTexture, string _hands, string _specialMarks);
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

	Characteristics characteristics;

	int uniqueAbilityDifficulty;
	bool minionSpawned = false;
	Character* minion = nullptr;

	VisualsASCII visualsASCII;

	Character();
	Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold, Character& _minion, int _uniqueAbilityDifficulty);
	Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold);
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
};

#endif