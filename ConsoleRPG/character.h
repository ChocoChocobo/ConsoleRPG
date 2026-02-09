#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>
#include "item.h"
#include "dice.h"
#include "user_interface.h"
using namespace std;

// Â ñòðóêòóðå character íàõîäÿòñÿ âñå õàðàêòåðèñòèêè + îïèñàíèå ïåðñà
// Ýòî ðåäàêòèðóåòñÿ â îòäåëüíîì ôàéëå ðåäàêòîðå ïåðñîíàæà

// 1. Èãðîê ðàñïðåäåëÿåò ñàì ñòàòû - äåëàåì. 8, 10, 12, 13, 14, 15
// 2. Ïðîãðàììà áðîñàåò êóáèê íà õàðàêòåðèñòèêè

// Ïðè âíåäðåíèè êëàññîâ íåîáõîäèìî îïðåäåëÿòü òèï êóáà è ìîäèôèêàòîðà, èñïîëüçóåìîãî ïðè àòàêå

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

// Ñïðàéòû ïåðñîíàæåé íàõîäÿòñÿ â ôàéëàõ
// LoadSprite(enum state)
struct VisualsASCII
{
	void ShowSprite()
	{
		
	}
};
  
// character.h - добаил  структуру Appearance
struct Appearance {
    // Основные поля внешности
    string skinColor;
    string hairColor;
    string hairStyle;
    string eyeColor;
    string facialHair;
    string scars;
    string tattoos;
    string clothingStyle;
    string accessories;
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
