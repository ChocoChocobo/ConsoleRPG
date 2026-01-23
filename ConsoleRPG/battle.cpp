#include "battle.h"
#include "savesystem.h"
#include "user_interface.h"

// в зависимости от исхода у игрока возвращается int значение
int PlayerTurn(Character& player, Character& enemy)
{
	cout << endl;
	cout << TOP_BORDER << endl;
	cout << "Вы можете сделать: " << endl;
	cout << "1. Обычная атака" << endl;
	cout << "2. Особая атака" << endl;
	cout << "3. Лечение" << endl;
	cout << "4. Побег" << endl; // чем больше хп врага, тем меньше шанс сбежать
	// 5. Открыть инвентарь. Прим.: боевка на паузе
	cout << "8. Инвентарь" << endl;
	cout << "9. Сохранить игру" << endl;
	cout << "0. Выйти из игры" << endl;
	cout << "Ваши действия: ";
	int userInput;
	cin >> userInput;
	cout << TOP_BORDER << endl;

	switch (userInput)
	{
	case 1:
		system("cls");
		player.BasicAttack(enemy);
		cout << TOP_BORDER << endl;
		return 1;
	case 2:
		// SpecialAttack()
		system("cls");
		cout << TOP_BORDER << endl;
		return 2;
	case 3:
		system("cls");
		player.Heal(8);
		cout << TOP_BORDER << endl;
		return 3;
	case 4:
		system("cls");
		cout << TOP_BORDER << endl;
		if (player.Flee(enemy))
		{			
			return 4;
		}		
		return 5;
	case 8:
		system("cls");
		cout << TOP_BORDER << endl;
		player.ShowInventory();
		return 8;
	case 9:
		system("cls");
		SaveGame(player, enemy);
		return 9;
	case 0:
		system("cls");
		cout << "До новых встреч!" << endl;
		return 0;
	default:
		system("cls");
		cout << "Некорректный ввод пользоватля, строка: " << __LINE__ << " в файле: " << __FILE__ << endl;
		break;
	}
}

int EnemyTurn(Character& enemy, Character& player)
{
	int enemyAction = rand() % 3;

	if (enemyAction == 0 && (double(enemy.health) / double(enemy.maxHealth)) * 100 >= 40)
	{
		enemy.BasicAttack(player);
		cout << endl;
		return 1;
	}
	else if (enemy.healthFlasks != 0 && (double(enemy.health) / double(enemy.maxHealth)) * 100 <= 40)
	{
		enemy.Heal(8);
		cout << endl;
		return 3;
	}

	int diceRoll = RollDice(20);
	if (diceRoll > enemy.uniqueAbilityDifficulty)
	{
		cout << "Польт от кондиционера включает кондей!" << endl;

		enemy.minionSpawned = true;
	}
	/*else
	{
		if (enemy.Flee(player))
		{
			cout << enemy.name << " сбегает в закат, оставляя ваши трусы с дурным послевкусием..." << endl;
			return 4;
		}
		else return 5;
	}*/
}

void CheckWinLoseConditionPlayer(Character player)
{

}

void CheckWinLoseConditionEnemy(Character enemy)
{

}