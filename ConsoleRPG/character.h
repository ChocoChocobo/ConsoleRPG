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
private:
    int strength;
    int dexterity;
    int constitution;
    int wisdom;
    int intelligence;
    int charisma;
    int armorClass;

public:
    Characteristics();
    Characteristics(int _strength, int _dexterity, int _constitution, int _wisdom, int _intelligence, int _charisma, int _armorClass);

    int CountModificator(int characteristic);
    void PrintCharacteristics();

    int GetStrength() const { return strength; }
    void SetStrength(int value) { strength = value; }

    int GetDexterity() const { return dexterity; }
    void SetDexterity(int value) { dexterity = value; }

    int GetConstitution() const { return constitution; }
    void SetConstitution(int value) { constitution = value; }

    int GetWisdom() const { return wisdom; }
    void SetWisdom(int value) { wisdom = value; }

    int GetIntelligence() const { return intelligence; }
    void SetIntelligence(int value) { intelligence = value; }

    int GetCharisma() const { return charisma; }
    void SetCharisma(int value) { charisma = value; }

    int GetArmorClass() const { return armorClass; }
    void SetArmorClass(int value) { armorClass = value; }
};

// Ñïðàéòû ïåðñîíàæåé íàõîäÿòñÿ â ôàéëàõ
// LoadSprite(enum state)
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

    Characteristics characteristics;

    int uniqueAbilityDifficulty;
    bool minionSpawned;
    Character* minion;

    vector<Item> inventory;
    VisualsASCII visualsASCII;

public:
 	Character();
    Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold);
    Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold, Character& _minion, int _uniqueAbilityDifficulty);

    void PrintStatus();
    void AddGold(int amount);
    void RemoveGold(int amount);
    bool BuyItem(int cost);
    void BasicAttack(Character& other);
    void SpecialAttack();
    void ShowInventory();
    void IncreaseHealth(int amount);
    void DecreaseHealth(int amount);
    void Heal(int difficulty);
    bool Flee(Character& other);
    bool CheckFleeSuccess(int difficulty);

    string GetName() const { return name; }
    void SetName(const string& n) { name = n; }

    int GetHealth() const { return health; }
    void SetHealth(int value) { health = value; if (health > maxHealth) health = maxHealth; if (health < 0) health = 0; }

    int GetMaxHealth() const { return maxHealth; }
    void SetMaxHealth(int value) { maxHealth = value; }

    int GetHealthFlasks() const { return healthFlasks; }
    void SetHealthFlasks(int value) { healthFlasks = value; }

    int GetGold() const { return gold; }
    void SetGold(int value) { gold = value; }

    int GetDamageFace() const { return damageFace; }
    void SetDamageFace(int value) { damageFace = value; }

    int GetSpecialCooldown() const { return specialCooldown; }
    void SetSpecialCooldown(int value) { specialCooldown = value; }

    Characteristics GetCharacteristics() const { return characteristics; }
    void SetCharacteristics(const Characteristics& c) { characteristics = c; }

    Character* GetMinion() const { return minion; }
    void SetMinion(Character* m) { minion = m; minionSpawned = (m != nullptr); }

    bool IsMinionSpawned() const { return minionSpawned; }

    vector<Item>& GetInventory() { return inventory; }
};


#endif
