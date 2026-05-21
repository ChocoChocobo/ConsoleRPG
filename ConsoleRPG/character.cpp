#include <iostream>
#include "character.h"
#include <cmath>
#include <random>
#include <vector>

// -------- Characteristics

Characteristics::Characteristics() : strength(15), dexterity(14), constitution(13), wisdom(12), intelligence(10), charisma(8), armorClass(12) {}

Characteristics::Characteristics(int _strength, int _dexterity, int _constitution, int _wisdom, int _intelligence, int _charisma, int _armorClass)
{
	strength = _strength;
	dexterity = _dexterity;
	constitution = _constitution;
	intelligence = _intelligence;
	wisdom = _wisdom;
	charisma = _charisma;
	armorClass = _armorClass;
}

int Characteristics::CountModificator(int characteristic)
{
	return floor((characteristic - 10) / 2);
}

void Characteristics::PrintCharacteristics()
{
	cout << TOP_BORDER << endl;
	cout << "\t----Таблица характеристик----" << endl;
	cout << "Сила: " << strength << endl;
	cout << "Ловкость: " << dexterity << endl;
	cout << "Телосложение: " << constitution << endl;
	cout << "Интеллект: " << intelligence << endl;
	cout << "Мудрость: " << wisdom << endl;
	cout << "Харизма: " << charisma << endl;
	cout << "Класс брони: " << armorClass << endl;
	cout << TOP_BORDER << endl;
}

// --------- Appearance Constructors and Methods

Appearance::Appearance()
{
	skinColor = "светлая";
	hairColor = "русые";
	eyeColor = "голубые";
	height = "средний";
	bodyType = "атлетичное";
}

Appearance::Appearance(string _skinColor, string _hairColor, string _eyeColor, string _height, string _bodyType)
{
	skinColor = _skinColor;
	hairColor = _hairColor;
	eyeColor = _eyeColor;
	height = _height;
	bodyType = _bodyType;
}

void Appearance::PrintAppearance()
{
	cout << TOP_BORDER << endl;
	cout << "\t----Внешность персонажа----" << endl;
	cout << "Цвет кожи: " << skinColor << endl;
	cout << "Цвет волос: " << hairColor << endl;
	cout << "Цвет глаз: " << eyeColor << endl;
	cout << "Рост: " << height << endl;
	cout << "Телосложение: " << bodyType << endl;
	cout << TOP_BORDER << endl;
}

void Appearance::RandomizeAppearance()
{
	vector<string> skinColors = {"светлая", "смуглая", "темная", "оливковая", "бледная", "загорелая"};
	vector<string> hairColors = {"русые", "шатены", "блондинистые", "рыжие", "черные", "седые", "каштановые"};
	vector<string> eyeColors = {"голубые", "зеленые", "карие", "серые", "янтарные", "фиолетовые", "синие"};
	vector<string> heights = {"низкий", "средний", "высокий", "очень высокий", "гигантский"};
	vector<string> bodyTypes = {"худое", "атлетичное", "мускулистое", "коренастое", "полное", "сутулое"};
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> skinDist(0, skinColors.size() - 1);
	uniform_int_distribution<> hairDist(0, hairColors.size() - 1);
	uniform_int_distribution<> eyeDist(0, eyeColors.size() - 1);
	uniform_int_distribution<> heightDist(0, heights.size() - 1);
	uniform_int_distribution<> bodyDist(0, bodyTypes.size() - 1);
	
	skinColor = skinColors[skinDist(gen)];
	hairColor = hairColors[hairDist(gen)];
	eyeColor = eyeColors[eyeDist(gen)];
	height = heights[heightDist(gen)];
	bodyType = bodyTypes[bodyDist(gen)];
}

// --------- Character

Character::Character()
{
	name = "Неизвестный";
	health = 10;
	maxHealth = health;
	healthFlasks = 3;
	damageFace = 4;
	specialCooldown = 0;
	gold = 10;
	uniqueAbilityDifficulty = 10;
	minion = nullptr;
	minionSpawned = false;
	// Установка внешности по умолчанию
	appearance.skinColor = "светлая";
	appearance.hairColor = "русые";
	appearance.eyeColor = "голубые";
	appearance.height = "средний";
	appearance.bodyType = "атлетичное";
}

Character::Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold, Character& _minion, int _uniqueAbilityDifficulty)
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
	// Установка внешности по умолчанию
	appearance.skinColor = "светлая";
	appearance.hairColor = "русые";
	appearance.eyeColor = "голубые";
	appearance.height = "средний";
	appearance.bodyType = "атлетичное";
}

Character::Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold)
{
	name = _name;
	health = _health;
	damageFace = _damageFace;
	maxHealth = health;
	healthFlasks = 3;
	specialCooldown = _specialCooldown;
	gold = _startGold;
	// Установка внешности по умолчанию
	appearance.skinColor = "светлая";
	appearance.hairColor = "русые";
	appearance.eyeColor = "голубые";
	appearance.height = "средний";
	appearance.bodyType = "атлетичное";
}

// Новый конструктор с полной внешностью
Character::Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold, 
					 string _skinColor, string _hairColor, string _eyeColor, string _height, string _bodyType)
{
	name = _name;
	health = _health;
	damageFace = _damageFace;
	maxHealth = health;
	healthFlasks = 3;
	specialCooldown = _specialCooldown;
	gold = _startGold;
	appearance.skinColor = _skinColor;
	appearance.hairColor = _hairColor;
	appearance.eyeColor = _eyeColor;
	appearance.height = _height;
	appearance.bodyType = _bodyType;
	uniqueAbilityDifficulty = 10;
	minion = nullptr;
	minionSpawned = false;
}

void Character::PrintStatus()
{
	cout << endl << name << " на HP: " << health << "/" << maxHealth;

	// Добавление: отображение золота
	cout << " | Золото: " << gold;

	if (specialCooldown > 0) cout << " | Перезарядка способности (" << specialCooldown << ")" << endl;
	else cout << endl;
	cout << "У " << name << " " << healthFlasks << " фласки здоровья" << endl;
}

// Новый метод для вывода полной информации
void Character::PrintFullInfo()
{
	PrintStatus();
	appearance.PrintAppearance();
}

void Character::AddGold(int amount)
{
	gold += amount;
	cout << name << " получил " << amount << " золота!" << endl;
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

void Character::BasicAttack(Character& other)
{
	cout << endl << name << " атакует " << other.name << "..." << endl;

	Results result = CheckSuccess(this, characteristics.strength, other.characteristics.armorClass);

	int damageRoll;
	switch (result)
	{
	case 1:
		damageRoll = RollDice(damageFace);
		other.DecreaseHealth(damageRoll);
		cout << name << " нанес " << damageRoll << " урона!" << endl;
		break;
	case 2:
		cout << name << " промахнулся O_O" << endl;
		break;
	case 3:
		damageRoll = RollDice(damageFace * 2);
		other.DecreaseHealth(damageRoll);
		cout << name << " нанес сокрушительный удар на " << damageRoll << " урона!" << endl;
		break;
	case 4:
		damageRoll = RollDice(damageFace);
		DecreaseHealth(damageRoll);
		cout << name << " споткнулся на ровном месте и нанес себе " << damageRoll << " урона :U" << endl;
		break;
	default:
		break;
	}
}

void Character::SpecialAttack()
{
	// Будет реализовано позже
}

void Character::ShowInventory()
{
	int userInput;
	do
	{
		if (inventory.size() <= 0)
		{
			cout << "В инвентаре нет предметов!" << endl;
			return;
		}

		for (int i = 1; i <= inventory.size(); i++)
		{
			cout << i << ". " << inventory[i - 1].name << "." << endl;
		}

		cout << endl << "Выберите номер предмета или нажмите '0' для выхода: " << endl;
		cin >> userInput;

		if (userInput == 0) continue;
		while (true)
		{
			cout << SEPARATOR_LINE << endl;
			inventory[userInput - 1].ShowInfo();
			Item chosenItem = inventory[userInput - 1];
			cout << endl << "Нажмите 1 для использования предмета (или '0' для выхода): " << endl;
			int nestedUserInput;
			cin >> nestedUserInput;
			if (nestedUserInput == 1)
			{
				inventory[userInput - 1].quantity -= 1;
				if (inventory[userInput - 1].quantity <= 0)
				{
					inventory.erase(inventory.begin() + userInput - 1);
					break;
				}
			}
			else if (nestedUserInput == 0)
			{
				system("cls");
				break;
			}
		}

		cout << TOP_BORDER << endl;
	} while (userInput != 0);

	system("cls");
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

void Character::Heal(int difficulty)
{
	if (healthFlasks == 0)
	{
		cout << "У вас не осталось фласок здоровья!" << endl;
		return;
	}

	cout << name << " использует лекарство..." << endl;

	Results result = CheckSuccess(this, characteristics.wisdom, difficulty);

	int healAmount;
	switch (result)
	{
	case 1:
		healthFlasks--;
		healAmount = maxHealth / 3;
		IncreaseHealth(healAmount);
		cout << name << " восстановил " << healAmount << " HP!" << endl;
		break;
	case 2:
		healthFlasks--;
		cout << name << " выпил обычную воду вместо лекарства." << endl;
		break;
	case 3:
		healthFlasks--;
		healAmount = maxHealth / 2;
		IncreaseHealth(healAmount);
		cout << name << " восстановил " << healAmount << " HP!" << endl;
		break;
	case 4:
		healthFlasks--;
		healAmount = maxHealth / 3;
		DecreaseHealth(healAmount);
		cout << "Вы думали, что " << name << " пьет лекарство, но это оказался яд -" << healAmount << " HP :o" << endl;
		break;
	default:
		cout << name << " не смог вылечиться!" << endl;
		break;
	}
}

bool Character::Flee(Character& other)
{
	int currentHealthPercent = int((double(other.health) / double(other.maxHealth)) * 100);

	if (currentHealthPercent >= 0 && currentHealthPercent <= 20)
	{
		return CheckFleeSuccess(3);
	}
	else if (currentHealthPercent >= 20 && currentHealthPercent <= 40)
	{
		return CheckFleeSuccess(7);
	}
	else if (currentHealthPercent >= 40 && currentHealthPercent <= 60)
	{
		return CheckFleeSuccess(14);
	}
	else if (currentHealthPercent >= 60 && currentHealthPercent <= 80)
	{
		return CheckFleeSuccess(15);
	}
	else
	{
		return CheckFleeSuccess(19);
	}
}

bool Character::CheckFleeSuccess(int difficulty)
{
	Results result = CheckSuccess(this, characteristics.dexterity, difficulty);
	switch (result)
	{
	case 1:
		cout << name << " сбежал, ура-ура!" << endl;
		return true;
	case 2:
		cout << "У " << name << " подкосились ноги, но не сбежал..." << endl;
		return false;
	case 3:
		cout << name << " не смог далеко убежать, но нашел фласку!" << endl;
		healthFlasks++;
		Heal(8);
		return true;
	case 4:
		cout << name << " споткнулся о камень и переломал себе ноги. " << name << " умирает..." << endl;
		DecreaseHealth(RollDice(4));
		return false;
	default:
		cout << "Что-то пошло не так в FleeCheckSuccess!" << endl;
		return false;
	}
}
