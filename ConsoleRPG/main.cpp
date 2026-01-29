#include <iostream>
#include <Windows.h>
#include <vector>
#include <conio.h>

#include "character.h"
#include "battle.h"
#include "user_interface.h"
#include "savesystem.h"
#include "shop.h"
#include "character_creator.h"
#include "casino.h"

using namespace std;

void main()
{
    setlocale(LC_ALL, "Ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(0));

    Character player("Безымянный", 12, 8, 0, 10);
    Character enemy("Блоха", 10, 4, 0, 10);

    vector<Item> shopItems;
    shopItems.push_back(Item("Зубы деда", "Наследство", 2, 32));
    shopItems.push_back(Item("Рок единорога", "Качественный звук", 5, 1));
    shopItems.push_back(Item("Батарейки", "Для пульта", 100, 4));

    Shop shop(player, shopItems);

    cout << "\t\t-----CPlusPlus Console RPG!-----" << endl;

    if (SaveExists())
    {
        cout << "Найдено сохранение. Загрузить? (1/0): ";
        int choice;
        cin >> choice;
        if (choice == 1)
            LoadGame(player, enemy);
    }

    bool gameRunning = true;

    while (gameRunning)
    {
        shop.ShowItems();
        // ф
        cout << TOP_BORDER << endl;
        cout << enemy.name << " появляется!" << endl;
        cout << TOP_BORDER << endl;

        int result = PlayerTurn(player, enemy, shop);

        if (result == 0)
            break;

        EnemyTurn(enemy, player);

        if (player.health <= 0)
        {
            cout << "Вы погибли!" << endl;
            break;
        }

        if (enemy.health <= 0)
        {
            cout << "Победа!" << endl;
            break;
        }
    }
}
