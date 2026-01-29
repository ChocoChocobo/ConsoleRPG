#include "battle.h"
#include "savesystem.h"
#include "user_interface.h"
#include <iostream>

using namespace std;

// â çàâèñèìîñòè îò èñõîäà ó èãðîêà âîçâðàùàåòñÿ int çíà÷åíèå
int PlayerTurn(Character& player, Character& enemy, Shop& shop)
{
    cout << endl;
    cout << TOP_BORDER << endl;
    cout << "Âû ìîæåòå ñäåëàòü: " << endl;
    cout << "1. Îáû÷íàÿ àòàêà" << endl;
    cout << "2. Îñîáàÿ àòàêà" << endl;
    cout << "3. Ëå÷åíèå" << endl;
    cout << "4. Ïîáåã" << endl;
    cout << "8. Èíâåíòàðü" << endl;
    cout << "9. Ñîõðàíèòü èãðó" << endl;
    cout << "0. Âûéòè èç èãðû" << endl;
    cout << "Âàøè äåéñòâèÿ: ";

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
        cout << "Äî íîâûõ âñòðå÷!" << endl;
        return 0;

    default:
        system("cls");
        cout << "Íåêîððåêòíûé ââîä ïîëüçîâàòåëÿ" << endl;
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
