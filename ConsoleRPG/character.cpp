#include "character.h"
#include <cmath>
#include <iostream>

using namespace std;

/// <summary>
/// Конструктор по умолчанию. Инициализирует характеристики базовыми значениями.
/// </summary>
Characteristics::Characteristics() : strength(15), dexterity(14), constitution(13),
wisdom(12), intelligence(10), charisma(8), armorClass(12) {
}

/// <summary>
/// Конструктор с явным указанием всех характеристик.
/// </summary>
/// <param name="_strength">Значение силы.</param>
/// <param name="_dexterity">Значение ловкости.</param>
/// <param name="_constitution">Значение телосложения.</param>
/// <param name="_wisdom">Значение мудрости.</param>
/// <param name="_intelligence">Значение интеллекта.</param>
/// <param name="_charisma">Значение харизмы.</param>
/// <param name="_armorClass">Значение класса доспехов.</param>
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

/// <summary>
/// Рассчитывает модификатор характеристики по правилам RPG.
/// </summary>
/// <param name="characteristic">Текущее числовое значение характеристики.</param>
/// <returns>Округленный вниз модификатор характеристики.</returns>
int Characteristics::CountModificator(int characteristic)
{
	return floor((characteristic - 10) / 2);
}

/// <summary>
/// Выводит список всех текущих характеристик персонажа в консоль.
/// </summary>
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

/// <summary>
/// Конструктор по умолчанию для создания безымянного персонажа со стартовыми параметрами.
/// </summary>
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

/// <summary>
/// Конструктор для создания персонажа, у которого есть призванный прислужник (миньон).
/// </summary>
/// <param name="_name">Имя персонажа.</param>
/// <param name="_health">Максимальное и текущее здоровье.</param>
/// <param name="_damageFace">Грань кубика для расчета базового урона.</param>
/// <param name="_specialCooldown">Время перезарядки специальной атаки.</param>
/// <param name="_startGold">Начальное количество золота.</param>
/// <param name="_minion">Ссылка на объект миньона.</param>
/// <param name="_uniqueAbilityDifficulty">Сложность проверки для уникальной способности.</param>
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

/// <summary>
/// Конструктор для создания одиночного персонажа без миньона.
/// </summary>
/// <param name="_name">Имя персонажа.</param>
/// <param name="_health">Максимальное и текущее здоровье.</param>
/// <param name="_damageFace">Грань кубика для расчета базового урона.</param>
/// <param name="_specialCooldown">Время перезарядки специальной атаки.</param>
/// <param name="_startGold">Начальное количество золота.</param>
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

/// <summary>
/// Возвращает имя персонажа.
/// </summary>
/// <returns>Строка с именем персонажа.</returns>
string Character::GetName() const { return name; }

/// <summary>
/// Возвращает текущее здоровье персонажа.
/// </summary>
/// <returns>Текущее количество единиц здоровья.</returns>
int Character::GetHealth() const { return health; }

/// <summary>
/// Возвращает максимальное здоровье персонажа.
/// </summary>
/// <returns>Максимально возможное количество единиц здоровья.</returns>
int Character::GetMaxHealth() const { return maxHealth; }

/// <summary>
/// Возвращает текущее количество золота у персонажа.
/// </summary>
/// <returns>Количество золотых монет.</returns>
int Character::GetGold() const { return gold; }

/// <summary>
/// Устанавливает текущее здоровье персонажа.
/// </summary>
/// <param name="value">Новое значение здоровья.</param>
void Character::SetHealth(int value) { health = value; }

/// <summary>
/// Устанавливает текущее количество золота у персонажа.
/// </summary>
/// <param name="value">Новое количество золота.</param>
void Character::SetGold(int value) { gold = value; }


/// <summary>
/// Выводит в консоль текущий статус персонажа: здоровье, золото и количество зелий.
/// </summary>
void Character::PrintStatus()
{
	cout << name << " — HP: " << health << "/" << maxHealth;
	cout << " | Золото: " << gold << endl;
	cout << "На данный момент у " << name << " " << healthFlasks << " зелий лечения" << endl;
}

/// <summary>
/// Добавляет золото персонажу и выводит сообщение об этом.
/// </summary>
/// <param name="amount">Количество добавляемого золота.</param>
void Character::AddGold(int amount)
{
	gold += amount;
	cout << name << " получает " << amount << " золота!" << endl;
}

/// <summary>
/// Отнимает золото у персонажа без вывода сообщений.
/// </summary>
/// <param name="amount">Количество отнимаемого золота.</param>
void Character::RemoveGold(int amount)
{
	gold -= amount;
}

/// <summary>
/// Попытка купить предмет за золото.
/// </summary>
/// <param name="cost">Стоимость предмета.</param>
/// <returns>True, если золота хватило и покупка успешна; иначе False.</returns>
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

/// <summary>
/// Восстанавливает здоровье персонажа, не превышая максимальный лимит.
/// </summary>
/// <param name="amount">Количество восстанавливаемого здоровья.</param>
void Character::IncreaseHealth(int amount)
{
	health += amount;
	if (health > maxHealth) health = maxHealth;
}

/// <summary>
/// Наносит урон здоровью персонажа, не опуская его ниже нуля.
/// </summary>
/// <param name="amount">Количество отнимаемого здоровья.</param>
void Character::DecreaseHealth(int amount)
{
	health -= amount;
	if (health < 0) health = 0;
}


/// <summary>
/// Совершает базовую атаку по противнику с броском кубика урона.
/// </summary>
/// <param name="other">Ссылка на цель атаки.</param>
void Character::BasicAttack(Character& other)
{
	cout << name << " атакует " << other.GetName() << "..." << endl;
	int damageRoll = RollDice(damageFace);
	other.DecreaseHealth(damageRoll);
	cout << other.GetName() << " получает " << damageRoll << " урона!" << endl;
}

/// <summary>
/// Активирует специальную атаку персонажа.
/// </summary>
void Character::SpecialAttack()
{

	cout << name << " использует специальную атаку!" << endl;
}

/// <summary>
/// Выводит в консоль пронумерованный список предметов в инвентаре персонажа.
/// </summary>
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

/// <summary>
/// Тратит одно зелье лечения и восстанавливает персонажу треть от его максимального здоровья.
/// </summary>
/// <param name="difficulty">Сложность применения (в текущей логике метода не используется).</param>
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

/// <summary>
/// Попытка персонажа сбежать из боя на основе уровня здоровья противника.
/// </summary>
/// <param name="other">Ссылка на противника, от которого совершается побег.</param>
/// <returns>True, если здоровье противника ниже 50%; иначе False.</returns>
bool Character::Flee(Character& other)
{
	int healthPercent = int((double(other.GetHealth()) / double(other.GetMaxHealth())) * 100);
	cout << name << " пытается убежать от " << other.GetName() << "..." << endl;
	return healthPercent < 50; // простой пример
}

/// <summary>
/// Проверяет успешность совершения побега по броску кубика.
/// </summary>
/// <param name="difficulty">Сложность проверки побега.</param>
/// <returns>True во всех случаях (заглушка).</returns>
bool Character::CheckFleeSuccess(int difficulty)
{

	return true;
}
