#include "battle.h"
#include "savesystem.h"
#include "user_interface.h"
#include <iostream>

using namespace std;

// в зависимости от исхода у игрока возвращается int значение
int PlayerTurn(Character& player, Character& enemy, Shop& shop)
{
    cout << endl;
    cout << TOP_BORDER << endl;
    cout << "Вы можете сделать: " << endl;
    cout << "1. Обычная атака" << endl;
    cout << "2. Особая атака" << endl;
    cout << "3. Лечение" << endl;
    cout << "4. Побег" << endl;
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
        return 1;

    case 2:
        system("cls");
        return 2;

    case 3:
        system("cls");
        player.Heal(8);
        return 3;

    case 4:
        system("cls");
        if (player.Flee(enemy))
            return 4;
        return 5;

    case 8:
        system("cls");
        player.ShowInventory();
        return 8;

    case 9:
        system("cls");
        SaveGame(player, enemy, shop);
        return 9;

    case 0:
        system("cls");
        cout << "До новых встреч!" << endl;
        return 0;

    default:
        system("cls");
        cout << "Некорректный ввод пользователя" << endl;
        return -1;
    }
}

int EnemyTurn(Character& enemy, Character& player)
{
    int enemyAction = rand() % 3;

    if (enemyAction == 0)
    {
        enemy.BasicAttack(player);
        return 1;
    }
    else if (enemy.healthFlasks > 0)
    {
        enemy.Heal(8);
        return 3;
    }

    return 0;
}

void CheckWinLoseConditionPlayer(Character player) {}
void CheckWinLoseConditionEnemy(Character enemy) {}
