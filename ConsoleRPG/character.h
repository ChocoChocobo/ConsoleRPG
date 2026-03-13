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
	/// <summary>
	/// Функция отвечает за вывод значений характеристик.
	/// </summary>
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
/// Структура отвечает за хранение описательной внешность персонажа. Нужна была для одной из ДЗ.
/// </summary>
struct Appearance
{
	string skinColor;
	string hairColor;
};

/// <summary>
/// Класс отвечает за все данные персонажа: игрока и врага
/// </summary>
class Character
{
public:
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
	/// <summary>
	/// Специальный конструктор для тех, кто умеет призывать миньёнов
	/// </summary>
	/// <param name="_name">Имя</param>
	/// <param name="_health">Максимальное и стартовое здоровье</param>
	/// <param name="_damageFace">Количетво граней куба урона</param>
	/// <param name="_specialCooldown">Время перезарядки специальной атаки (в ходах)</param>
	/// <param name="_startGold">Стартовое золото</param>
	/// <param name="_minion">Ссылка на миньёна, которого будет призывать персонаж</param>
	/// <param name="_uniqueAbilityDifficulty">Хз честно</param>
	Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold, Character& _minion, int _uniqueAbilityDifficulty);
	/// <summary>
	/// Конструктор для игрока и обычного врага
	/// </summary>
	/// <param name="_name">Имя</param>
	/// <param name="_health">Максимальное и стартовое здоровье</param>
	/// <param name="_damageFace">Количетво граней куба урона</param>
	/// <param name="_specialCooldown">Время перезарядки специальной атаки (в ходах)</param>
	/// <param name="_startGold">Стартовое золото</param>
	Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold);

	// Вспомогательные функции
	
	/// <summary>
	/// Функция отвечает за вывод информации о персонаже
	/// </summary>
	void PrintStatus();
	/// <summary>
	/// Вспомогательная функция, отвечающая за вычитание денег у персонажа
	/// </summary>
	/// <param name="amount">Сколько вычитать</param>
	void RemoveGold(int amount);
	/// <summary>
	/// Вспомогательная функция, отвечающая за прибавление денег персонажу
	/// </summary>
	/// <param name="amount">Сколько денег прибавлять</param>
	void AddGold(int amount);
	/// <summary>
	/// Вспомогательная функция, которая отвечает за покупку предмета
	/// </summary>
	/// <param name="cost">Стоимость этого предмета</param>
	/// <returns>Если успешно возвращает true, иначе false</returns>
	bool BuyItem(int cost);
	/// <summary>
	/// Вспомогательная функция, отвечающая за прибавление текущих хитов персонажу
	/// </summary>
	/// <param name="amount">Сколько прибавлять</param>
	void IncreaseHealth(int amount);
	/// <summary>
	/// Вспомогательная функция, отвечающая за отнятие текущих хитов персонажу
	/// </summary>
	/// <param name="amount">Сколько отнять</param>
	void DecreaseHealth(int amount);
	/// <summary>
	/// Вспомогательная функция, отвечающая за проверку на побег персонажа от своего врага
	/// </summary>
	/// <param name="difficulty">Сложность проверки</param>
	/// <returns>Возвращает true если удачно, иначе false</returns>
	bool CheckFleeSuccess(int difficulty);

	// Функции, которые должны быть описаны как состояния
	
	/// <summary>
	/// Функция отвечает за основную атаку персонажа
	/// </summary>
	/// <param name="other">Персонаж, по которому атакуют</param>
	void BasicAttack(Character& other);
	/// <summary>
	/// нет.
	/// </summary>
	void SpecialAttack();
	/// <summary>
	/// Функция отвечает за вывод предметов в инвентаре
	/// </summary>
	void ShowInventory();
	/// <summary>
	/// Функция отвечает за попытку излечиться. Она тратит healthFlasks
	/// </summary>
	/// <param name="difficulty">Сложность излечения</param>
	void Heal(int difficulty);
	/// <summary>
	/// Функция отвечает за попытку сбежать от врага. Чем больше хитов у врага тем больше сложность
	/// </summary>
	/// <param name="other">Тот, от кого пытаются сбежать</param>
	/// <returns>Если успешно возвращает true, иначе false</returns>
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