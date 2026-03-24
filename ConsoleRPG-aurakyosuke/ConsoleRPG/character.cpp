#include "character.h"
#include <cmath>
#include <iostream>

using namespace std;

Characteristics::Characteristics() : strength(15), dexterity(14), constitution(13),
	wisdom(12), intelligence(10), charisma(8), armorClass(12) {}

Characteristics::Characteristics(int _strength, int _dexterity, int _constitution,
	int _wisdom, int _intelligence, int _charisma, int _armorClass)
{
	strength = _strength;
	dexterity = _dexterity;
	constitution = _constitution;
	wisdom = _wisdom;
	intelligence = _intelligence;
	charisma = _charisma;
	armorClass = _armorClass;
}

int Characteristics::CountModificator(int characteristic)
{
	return floor((characteristic - 10) / 2);
}

void Characteristics::PrintCharacteristics()
{
	cout << "---- Ваши текущие характеристики ----" << endl;
	cout << "Сила: " << strength << endl;
	cout << "Ловкость: " << dexterity << endl;
	cout << "Телосложение: " << constitution << endl;
	cout << "Интеллект: " << intelligence << endl;
	cout << "Мудрость: " << wisdom << endl;
	cout << "Харизма: " << charisma << endl;
	cout << "Класс доспехов: " << armorClass << endl;
}

// Character конструкторы

Character::Character()
{
	name = "Безымянный";
	health = 10;
	maxHealth = health;
	healthFlasks = 3;
	damageFace = 4;
	specialCooldown = 0;
	gold = 10;
	uniqueAbilityDifficulty = 10;
	minion = nullptr;
	minionSpawned = false;
	appearance.skinColor = "Не выбран";
	appearance.hairColor = "Не выбран";
}

Character::Character(string _name, int _health, int _damageFace, int _specialCooldown,
	int _startGold, Character& _minion, int _uniqueAbilityDifficulty)
{
	name = _name;
	health = _health;
	damageFace = _damageFace;
	maxHealth = health;
	healthFlasks = 3;
	specialCooldown = _specialCooldown;
	minion = &_minion;
	uniqueAbilityDifficulty = _uniqueAbilityDifficulty;
	gold = _startGold;
}

Character::Character(string _name, int _health, int _damageFace, int _specialCooldown,
	int _startGold)
{
	name = _name;
	health = _health;
	damageFace = _damageFace;
	maxHealth = health;
	healthFlasks = 3;
	specialCooldown = _specialCooldown;
	gold = _startGold;
}


// GET / SET

string Character::GetName() const { return name; }
int Character::GetHealth() const { return health; }
int Character::GetMaxHealth() const { return maxHealth; }
int Character::GetGold() const { return gold; }
void Character::SetHealth(int value) { health = value; }
void Character::SetGold(int value) { gold = value; }


void Character::PrintStatus()
{
	cout << name << " — HP: " << health << "/" << maxHealth;
	cout << " | Золото: " << gold << endl;
	cout << "На данный момент у " << name << " " << healthFlasks << " зелий лечения" << endl;
}

void Character::AddGold(int amount)
{
	gold += amount;
	cout << name << " получает " << amount << " золота!" << endl;
}

void Character::RemoveGold(int amount)
{
	gold -= amount;
}

bool Character::BuyItem(int cost)
{
	if (gold >= cost)
	{
		gold -= cost;
		cout << name << " купил предмет за " << cost << " золота!" << endl;
		return true;
	}
	else
	{
		cout << "Недостаточно золота! Нужно: " << cost << ", есть: " << gold << endl;
		return false;
	}
}

void Character::IncreaseHealth(int amount)
{
	health += amount;
	if (health > maxHealth) health = maxHealth;
}

void Character::DecreaseHealth(int amount)
{
	health -= amount;
	if (health < 0) health = 0;
}


void Character::BasicAttack(Character& other)
{
	cout << name << " атакует " << other.GetName() << "..." << endl;
	int damageRoll = RollDice(damageFace);
	other.DecreaseHealth(damageRoll);
	cout << other.GetName() << " получает " << damageRoll << " урона!" << endl;
}

void Character::SpecialAttack()
{
	
	cout << name << " использует специальную атаку!" << endl;
}

void Character::ShowInventory()
{
	if (inventory.empty())
	{
		cout << "В инвентаре нет предметов!" << endl;
		return;
	}

	for (size_t i = 0; i < inventory.size(); i++)
	{
		cout << i + 1 << ". " << inventory[i].name << endl;
	}
}

void Character::Heal(int difficulty)
{
	if (healthFlasks <= 0)
	{
		cout << "У " << name << " нет зелий лечения!" << endl;
		return;
	}
	healthFlasks--;
	IncreaseHealth(maxHealth / 3);
	cout << name << " восстанавливает здоровье!" << endl;
}

bool Character::Flee(Character& other)
{
	int healthPercent = int((double(other.GetHealth()) / double(other.GetMaxHealth())) * 100);
	cout << name << " пытается убежать от " << other.GetName() << "..." << endl;
	return healthPercent < 50; // простой пример
}

bool Character::CheckFleeSuccess(int difficulty)
{
	
	return true;
}
