#include <iostream>
#include "character.h"

Character::Character(string _name, int _health, int _damageFace, int _specialCooldown, int _armorClass, int _startGold)
{
	name = _name;
	health = _health;
	damageFace = _damageFace;
	maxHealth = health;
	healthFlasks = 3;
	specialCooldown = _specialCooldown;
	stats.armorClass = _armorClass;

	// ДОБАВЛЕНО: ИНИЦИАЛИЗАЦИЯ ВАЛЮТЫ
	gold = _startGold;
}

void Character::PrintStatus()
{
	cout << endl << name << " –— HP: " << health << "/" << maxHealth;

	// ДОБАВЛЕНО: ВЫВОД КОЛИЧЕСТВА ЗОЛОТА
	cout << " | Золото: " << gold;

	if (specialCooldown > 0) cout << " | Особая атака недоступна (" << specialCooldown << ")" << endl;
	else cout << endl;
	cout << "На данный момент у " << name << " " << healthFlasks << " зелий лечения" << endl;
}

// ДОБАВЛЕНО: МЕТОД ДЛЯ ПОЛУЧЕНИЯ ЗОЛОТА
void Character::AddGold(int amount)
{
	gold += amount;
	cout << name << " получает " << amount << " золота!" << endl;
}

// ДОБАВЛЕНО: МЕТОД ДЛЯ ПОКУПКИ ПРЕДМЕТОВ
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

	Results result = CheckSuccess(other.stats.armorClass);

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

	Results result = CheckSuccess(difficulty);

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
	Results result = CheckSuccess(difficulty);
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