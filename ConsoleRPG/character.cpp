#include <iostream>
#include "character.h"
#include <cmath>

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
	cout << "\t----Ваши текущие характеристики----" << endl;
	cout << "Сила: " << strength << endl;
	cout << "Ловкость: " << dexterity << endl;
	cout << "Телосложение: " << constitution << endl;
	cout << "Интеллект: " << intelligence << endl;
	cout << "Мудрость: " << wisdom << endl;
	cout << "Харизма: " << charisma << endl;
	cout << "Класс доспехов: " << armorClass << endl;
	cout << TOP_BORDER << endl;
}

// --------- Character

Character::Character(string _name, int _health, int _damageFace, int _specialCooldown, int _startGold)
{
	name = _name;
	health = _health;
	damageFace = _damageFace;
	maxHealth = health;
	healthFlasks = 3;
	specialCooldown = _specialCooldown;
	
	gold = _startGold;
}

void Character::PrintStatus()
{
	cout << endl << name << " –— HP: " << health << "/" << maxHealth;

	cout << " | Золото: " << gold;

	if (specialCooldown > 0) cout << " | Особая атака недоступна (" << specialCooldown << ")" << endl;
	else cout << endl;
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
		cout << name << " покупает предмет за " << cost << " золота!" << endl;
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
	cout << endl << name << " пытается атаковать " << other.name << "..." << endl;

	Results result = CheckSuccess(this, characteristics.strength, other.characteristics.armorClass);

	int damageRoll;
	switch (result)
	{
	case 1:
		damageRoll = RollDice(damageFace);
		other.DecreaseHealth(damageRoll);
		cout << name << " наносит " << damageRoll << " урона!" << endl;
		break;
	case 2:
		cout << name << " промахивается O_O" << endl;
		break;
	case 3:
		damageRoll = RollDice(damageFace * 2);
		other.DecreaseHealth(damageRoll);
		cout << name << " СТИРАЕТ С ЛИЦА ЗЕМЛИ НА " << damageRoll << " УРОНА!" << endl;
		break;
	case 4:
		damageRoll = RollDice(damageFace);
		DecreaseHealth(damageRoll);
		cout << name << " подскользнулся на банановой кожуре и сломал позвоночник на " << damageRoll << " урона :U" << endl;
		break;
	default:
		break;
	}
}

void Character::SpecialAttack()
{

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

		cout << endl << "Введите номер предмета для его осмотра (или '0' для выхода): " << endl;
		cin >> userInput;

		if (userInput == 0) continue;
		while (true)
		{
			cout << SEPARATOR_LINE << endl;
			inventory[userInput - 1].ShowInfo();
			Item chosenItem = inventory[userInput - 1];
			cout << endl << "Введите 1 для применения предмета (или '0' для выхода): " << endl;
			int nestedUserInput;
			cin >> nestedUserInput;
			if (nestedUserInput == 1)
			{
				inventory[userInput - 1].quantity -= 1;
				if (inventory[userInput - 1].quantity <= 0)
				{
					inventory.erase(inventory.begin() + userInput - 1);
					// PLACEHOLDER
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
		cout << "У вас не осталось зелий лечения!" << endl;
		return;
	}

	cout << name << " пытается исцелиться..." << endl;

	Results result = CheckSuccess(this, characteristics.wisdom, difficulty);

	int healAmount;
	switch (result)
	{
	case 1:
		healthFlasks--;
		healAmount = maxHealth / 3;
		IncreaseHealth(healAmount);
		cout << name << " восстанавливает " << healAmount << " HP!" << endl;
		break;
	case 2:
		healthFlasks--;
		cout << name << " проливает целебную жидкость мимо рта." << endl;
		break;
	case 3:
		healthFlasks--;
		healAmount = maxHealth / 2;
		IncreaseHealth(healAmount);
		cout << name << " восстанавливает " << healAmount << " HP!" << endl;
		break;
	case 4:
		healthFlasks--;
		healAmount = maxHealth / 3;
		DecreaseHealth(healAmount);
		cout << "Во время того, как " << name << " судорожно пил склянку, он поперхнулся и потерял" << healAmount << " HP :o" << endl;
		break;
	default:
		cout << name << " пропускает свой ход!" << endl;
		break;
	}
}

bool Character::Flee(Character& other)
{
	int currentHealthPercent = (double(other.health) / double(other.maxHealth)) * 100;

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
		cout << name << " сбежал, пожав хвост!" << endl;
		return true;
	case 2:
		cout << "У " << name << " сбежали глаза, а он остался..." << endl;
		return false;
	case 3:
		cout << name << " не только удалось сбежать, но и воспрять духами!" << endl;
		healthFlasks++;
		Heal(8);
		return true;
	case 4:
		cout << name << " засмотрелся на противника и подскользнулся на своих глазах." << name << "завораживает его вид..." << endl;
		DecreaseHealth(RollDice(4));
		return false;
	default:
		cout << "Что-то пошло не так в FleeCheckSuccess!" << endl;
		return false;
	}
}

// --------- Appearance

Appearance::Appearance(string _physique, string _skinColor, string _eyeColor,
	string _earShape, string _hairType, string _mouthType,
	string _weapon, string _armor, string _tail, string _navel,
	string _skinTexture, string _hands, string _specialMarks)
{
	physique = _physique;
	skinColor = _skinColor;
	eyeColor = _eyeColor;
	earShape = _earShape;
	hairType = _hairType;
	mouthType = _mouthType;
	weapon = _weapon;
	armor = _armor;
	tail = _tail;
	navel = _navel;
	skinTexture = _skinTexture;
	hands = _hands;
	specialMarks = _specialMarks;
}