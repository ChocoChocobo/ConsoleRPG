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
	cout << "\t----Âàøè òåêóùèå õàðàêòåðèñòèêè----" << endl;
	cout << "Ñèëà: " << strength << endl;
	cout << "Ëîâêîñòü: " << dexterity << endl;
	cout << "Òåëîñëîæåíèå: " << constitution << endl;
	cout << "Èíòåëëåêò: " << intelligence << endl;
	cout << "Ìóäðîñòü: " << wisdom << endl;
	cout << "Õàðèçìà: " << charisma << endl;
	cout << "Êëàññ äîñïåõîâ: " << armorClass << endl;
	cout << TOP_BORDER << endl;
}

// --------- Character
class Character {
private:
    string name;
    int health;
    int maxHealth;
    int damage;
    int level;
    int experience;
    int defense;

public:
    // Конструктор
    Character(string charName, int initialHealth, int initialDamage);
    
    // Геттеры (только чтение)
    string getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getDamage() const;
    int getLevel() const;
    int getExperience() const;
    int getDefense() const;
    
    // Сеттеры (контролируемое изменение)
    void setName(const string& newName);
    void setHealth(int newHealth);
    void setDamage(int newDamage);
    void setLevel(int newLevel);
    void setDefense(int newDefense);
    
    // Методы для управления опытом
    void addExperience(int exp);
    void levelUp();
    
    // Методы для управления здоровьем
    void takeDamage(int damageAmount);
    void heal(int healAmount);
    bool isAlive() const;
    
    // Остальные публичные методы
    void displayInfo() const;
    void attack(Character& target);
};

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
}

void Character::PrintStatus()
{
	cout << endl << name << " –— HP: " << health << "/" << maxHealth;

	// ÄÎÁÀÂËÅÍÎ: ÂÛÂÎÄ ÊÎËÈ×ÅÑÒÂÀ ÇÎËÎÒÀ
	cout << " | Çîëîòî: " << gold;

	if (specialCooldown > 0) cout << " | Îñîáàÿ àòàêà íåäîñòóïíà (" << specialCooldown << ")" << endl;
	else cout << endl;
	cout << "Íà äàííûé ìîìåíò ó " << name << " " << healthFlasks << " çåëèé ëå÷åíèÿ" << endl;
}

// ÄÎÁÀÂËÅÍÎ: ÌÅÒÎÄ ÄËß ÏÎËÓ×ÅÍÈß ÇÎËÎÒÀ
void Character::AddGold(int amount)
{
	gold += amount;
	cout << name << " ïîëó÷àåò " << amount << " çîëîòà!" << endl;
}

// ÄÎÁÀÂËÅÍÎ: ÌÅÒÎÄ ÄËß ÎÒÍÈÌÀÍÈß ÇÎËÎÒÀ (ÌÎÆÅÒ ÓÉÒÈ Â ÌÈÍÓÑ)
void Character::RemoveGold(int amount)
{
	gold -= amount;
}

// ÄÎÁÀÂËÅÍÎ: ÌÅÒÎÄ ÄËß ÏÎÊÓÏÊÈ ÏÐÅÄÌÅÒÎÂ
bool Character::BuyItem(int cost)
{
	if (gold >= cost)
	{
		gold -= cost;
		cout << name << " ïîêóïàåò ïðåäìåò çà " << cost << " çîëîòà!" << endl;
		return true;
	}
	else
	{
		cout << "Íåäîñòàòî÷íî çîëîòà! Íóæíî: " << cost << ", åñòü: " << gold << endl;
		return false;
	}
}

void Character::BasicAttack(Character& other)
{
	cout << endl << name << " ïûòàåòñÿ àòàêîâàòü " << other.name << "..." << endl;

	Results result = CheckSuccess(this, characteristics.strength, other.characteristics.armorClass);

	int damageRoll;
	switch (result)
	{
	case 1:
		damageRoll = RollDice(damageFace);
		other.DecreaseHealth(damageRoll);
		cout << name << " íàíîñèò " << damageRoll << " óðîíà!" << endl;
		break;
	case 2:
		cout << name << " ïðîìàõèâàåòñÿ O_O" << endl;
		break;
	case 3:
		damageRoll = RollDice(damageFace * 2);
		other.DecreaseHealth(damageRoll);
		cout << name << " ÑÒÈÐÀÅÒ Ñ ËÈÖÀ ÇÅÌËÈ ÍÀ " << damageRoll << " ÓÐÎÍÀ!" << endl;
		break;
	case 4:
		damageRoll = RollDice(damageFace);
		DecreaseHealth(damageRoll);
		cout << name << " ïîäñêîëüçíóëñÿ íà áàíàíîâîé êîæóðå è ñëîìàë ïîçâîíî÷íèê íà " << damageRoll << " óðîíà :U" << endl;
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
			cout << "Â èíâåíòàðå íåò ïðåäìåòîâ!" << endl;
			return;
		}

		for (int i = 1; i <= inventory.size(); i++)
		{
			cout << i << ". " << inventory[i - 1].name << "." << endl;
		}

		cout << endl << "Ââåäèòå íîìåð ïðåäìåòà äëÿ åãî îñìîòðà (èëè '0' äëÿ âûõîäà): " << endl;
		cin >> userInput;

		if (userInput == 0) continue;
		while (true)
		{
			cout << SEPARATOR_LINE << endl;
			inventory[userInput - 1].ShowInfo();
			Item chosenItem = inventory[userInput - 1];
			cout << endl << "Ââåäèòå 1 äëÿ ïðèìåíåíèÿ ïðåäìåòà (èëè '0' äëÿ âûõîäà): " << endl;
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
		cout << "Ó âàñ íå îñòàëîñü çåëèé ëå÷åíèÿ!" << endl;
		return;
	}

	cout << name << " ïûòàåòñÿ èñöåëèòüñÿ..." << endl;

	Results result = CheckSuccess(this, characteristics.wisdom, difficulty);

	int healAmount;
	switch (result)
	{
	case 1:
		healthFlasks--;
		healAmount = maxHealth / 3;
		IncreaseHealth(healAmount);
		cout << name << " âîññòàíàâëèâàåò " << healAmount << " HP!" << endl;
		break;
	case 2:
		healthFlasks--;
		cout << name << " ïðîëèâàåò öåëåáíóþ æèäêîñòü ìèìî ðòà." << endl;
		break;
	case 3:
		healthFlasks--;
		healAmount = maxHealth / 2;
		IncreaseHealth(healAmount);
		cout << name << " âîññòàíàâëèâàåò " << healAmount << " HP!" << endl;
		break;
	case 4:
		healthFlasks--;
		healAmount = maxHealth / 3;
		DecreaseHealth(healAmount);
		cout << "Âî âðåìÿ òîãî, êàê " << name << " ñóäîðîæíî ïèë ñêëÿíêó, îí ïîïåðõíóëñÿ è ïîòåðÿë" << healAmount << " HP :o" << endl;
		break;
	default:
		cout << name << " ïðîïóñêàåò ñâîé õîä!" << endl;
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
		cout << name << " ñáåæàë, ïîæàâ õâîñò!" << endl;
		return true;
	case 2:
		cout << "Ó " << name << " ñáåæàëè ãëàçà, à îí îñòàëñÿ..." << endl;
		return false;
	case 3:
		cout << name << " íå òîëüêî óäàëîñü ñáåæàòü, íî è âîñïðÿòü äóõàìè!" << endl;
		healthFlasks++;
		Heal(8);
		return true;
	case 4:
		cout << name << " çàñìîòðåëñÿ íà ïðîòèâíèêà è ïîäñêîëüçíóëñÿ íà ñâîèõ ãëàçàõ." << name << "çàâîðàæèâàåò åãî âèä..." << endl;
		DecreaseHealth(RollDice(4));
		return false;
	default:
		cout << "×òî-òî ïîøëî íå òàê â FleeCheckSuccess!" << endl;
		return false;
	}
}
