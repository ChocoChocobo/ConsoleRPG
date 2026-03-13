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

/// <summary>
/// Структура, ответственная за хранение набора характеристик персонажа и расчёт модификатора.
/// </summary>
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
	/// <summary>
	/// Функция ответствена за расчёт модификатора конкретной характеристики по её значению.
	/// </summary>
	/// <param name="characteristic">Значение характеристики, по которой будет считаться модификатор</param>
	/// <returns>Возвращает модификатор характеристики</returns>
	int CountModificator(int characteristic);
	void PrintCharacteristics();
};

// Спрайты персонажей находятся в файлах
// LoadSprite(enum state)

/// <summary>
/// Должн аотвечать за анимацию в стиле ASCII
/// </summary>
struct VisualsASCII
{
	void ShowSprite()
	{

	}
};

/// <summary>
/// Структура отвечает за описательную внешность персонажа
/// </summary>
struct Appearance
{
	string skinColor;
	string hairColor;
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

	// Вспомогательные функции
	void PrintStatus();
	void RemoveGold(int amount);
	void AddGold(int amount);
	bool BuyItem(int cost);
	void IncreaseHealth(int amount);
	void DecreaseHealth(int amount);
	bool CheckFleeSuccess(int difficulty);

	// Функции, которые должны быть описаны как состояния
	void BasicAttack(Character& other);
	void SpecialAttack();
	void ShowInventory();
	void Heal(int difficulty);
	bool Flee(Character& other);
};

class CharacterContext;
class CharacterState
{
public:
	~CharacterState() {}
	// Публичный метод, позволяющий переключиться на конкретное состояние
	void SetContext(CharacterContext* context)
	{
		this->context = context;
	}
	// Handle-функция ответственна за возможность справиться с вызовом другой функции
	virtual void HandleChangeState() = 0;
	virtual void HandleAction(Character* character, Character* other, int difficulty) = 0;
protected:
	CharacterContext* context;
};

class CharacterContext
{
public:
	CharacterContext(CharacterState* state)
	{
		this->TransitionToState(state);
	}
	// Контекст позволяет изменять состояние объекта с помощью этой функции
	void TransitionToState(CharacterState* state);
	void RequestChangeState()
	{
		this->state->HandleChangeState();
	}
	void RequestAction()
	{
		this->state->HandleAction(character, other, dificulty);
	}
	~CharacterContext()
	{
		delete state;
	}
private:
	CharacterState* state;

	Character* character;
	Character* other;
	int dificulty;
};

class BasicAttackState : public CharacterState
{
public:
	void HandleChangeState() override;
	void HandleAction(Character* character, Character* other, int difficulty) override;
};

class SpecialAttackState : public CharacterState
{
	void HandleChangeState() override;
	void HandleAction(Character* character, Character* other, int difficulty) override;
};

class ShowInventoryState : public CharacterState
{
	void HandleChangeState() override;
	void HandleAction(Character* character, Character* other, int difficulty) override;
};

class HealState : public CharacterState
{
	void HandleChangeState() override;
	void HandleAction(Character* character, Character* other, int difficulty) override;
};

class FleeState : public CharacterState
{
	void HandleChangeState() override;
	void HandleAction(Character* character, Character* other, int difficulty) override;
};
#endif