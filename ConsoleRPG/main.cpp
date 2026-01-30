// Что добавить:
// 2. В начале распределение статов из 75 предложенных очков (любая другая система на ваш вкус) и создание перса из домашки
// 3. Сохранение в магазине и магазина
// 4. Меню паузы для Давида с настройками сложности
// 7. Вывод графики в ASCII
// 8. Переделать вывод информации для уникальных ситуаций
// 9. Стринговые массивы для описания разных действий
// 11. Клаустрофобия
// Пульт от кондиционера открывает секретную комнату

// ?. Сделать A* типа шахматного поля для Давида!
// ???. A* для ии врага

#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include "character.h"
#include "battle.h"
#include "user_interface.h"
#include "savesystem.h"
#include "shop.h"
#include "character_creator.h"
#include "casino.h"
#include <conio.h>

using namespace std;

#if !defined(__cplusplus)
#error C++ компилятор нужен ты олух!
#endif

void main()
{
	setlocale(LC_ALL, "Ru");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//cout << "Программа была скомпилирована в: " << __TIME__ << endl;

	srand(time(0));

	int userChoice;
	int enemyChoice;
	bool fled = false;

	// ДОБАВЛЕНО: ИГРОК НАЧИНАЕТ С 10 ЗОЛОТА
	Character player("Безымянный", 12, 8, 0, 10);
	
	Character enemy("Блоха", 10, 4, 0, 10);
	Character enemy1("Цербер", 25, 8, 0, 25);
	Character enemy2("Моль-беспилотник", 2, 10, 0, 10);

	Character condeiMinion("Кондей", 12, 4, 0, 0);
	Character enemy3("Пульт от кондиционера", 45, 8, 0, 1000, condeiMinion, 15);

	vector<Character> enemyWave = {enemy, enemy1, enemy2, enemy3};

	vector<Item> shopItems = {};

	Item item1("Зубы деда", "Все что вам могло осталось в наследство", 2, 32);
	Item item2("Рок единорога", "Самый качественный звук", 5, 1);
	Item item3("Батарейки", "Батарейки для пульта от кондиционера", 100, 4);

	shopItems.push_back(item2);
	shopItems.push_back(item1);
	shopItems.push_back(item3);

	Shop shop(player, shopItems);
	

	cout << "\t\t-----CPlusPlus Console RPG!-----" << endl;
	cout << "В данной текстовой ролевой игре вам необходимо победить врага в формате пошаговых боев. При совершении каждого действия происходит бросок кубика д20, который определяет исход результата. Удачи!" << endl;
	
	if (SaveExists())
	{
		cout << endl << "Обнаружено сохранение. Для его загрузки нажмите 1. Для начала новой игрой нажмите 0." << endl;
		cin >> userChoice;
		if (userChoice == 1) LoadGame(player, enemy);
		else
		{
			ShowProgressBar(3.2, 50, "Загрузка.", '#');
			system("cls");
			player.characteristics = DistributeCharacteristics();

			system("cls");
			cout << "Задайте имя вашему герою: ";
			cin.ignore(1000, '\n');
			getline(cin, player.name);
			cout << endl;

			if (player.name == "Платон Святозарный")
			{
				cout << "Вы вписали секретное имя!" << endl;
				cout << "+ 6 кд" << endl;
				cout << "+ 40 голды" << endl;
				player.characteristics.armorClass += 6;
				player.gold += 40;
			}
			else if (player.name == "ChocoChocobo")
			{
				cout << "Вы вписали секретное имя!" << endl;
				cout << "+ вы чувствуете себя сильнее" << endl;
				cout << "+ мораль" << endl;
				player.damageFace = 10;				
			}
			else if (player.name == "Bytik Menich")
			{
				cout << "Вы вписали секретное имя!" << endl;
				cout << "+ вы чувствуете..." << endl;
				Item item4("Батарейки", "Батарейки для пульта от кондиционера", 100, 2);
				Item item5("Шпингалет", "Арбитр мироздания в твоей ванной", 1, 1);
				player.inventory.push_back(item4);
				player.inventory.push_back(item5);
			}
			else if (player.name == "Levi_333")
			{
				cout << "Вы вписали секретное имя!" << endl;
				cout << "+ вы чувствуете свободу в вашем разуме" << endl;
				cout << "+ вы перестали думать" << endl;
				cout << "- мысли" << endl;
				player.health += 12;
				player.maxHealth += 12;
				player.healthFlasks += 2;
			}
			else if (player.name == "Ольга Петровна")
			{
				cout << "Вы вписали секретное имя!" << endl;
				cout << "+ вы чувствуете страх в глазах ваших врагов" << endl;
				cout << "+ Вы" << endl;
				cout << "- Родин" << endl;
				player.characteristics.armorClass = 18;
				player.health = 1;
				player.maxHealth = 1;
				player.gold = 250;
			}
			else if (player.name == "Кусов")
			{
				cout << "Вы вписали секретное имя!" << endl;
				cout << "+ теперь вы что-то между Абаем Кунанбаевом и Аполлоном" << endl;
				cout << "+++++++++++++++++++++" << endl;
				cout << "- нет" << endl;
				player.damageFace = 1;
				player.healthFlasks = 64;
				player.characteristics.armorClass = 128;
				player.health = 256;
				player.maxHealth = 512;
				player.gold = 1024;
			}
			else if (player.name == "Леша 10 метров от вас")
			{
				cout << "Вы вписали секретное имя!" << endl;
				cout << "+ определенно дотянется" << endl;
				cout << "+ вы вступили на тропу войны с С++" << endl;
				cout << "+ С++" << endl;
				cout << "- С--" << endl;
				cout << "- проиграл все торговцу" << endl;
				player.gold = -1024;
				player.characteristics.charisma = 17;
				player.characteristics.wisdom = 17;
			}
			else if (player.name == "Гном Плюсокрад")
			{
				cout << "Вы вписали секретное имя!" << endl;
				cout << "+ теперь гном" << endl;
				cout << "+ есть честь" << endl;
				cout << "+ печеньки с молоком" << endl;
				cout << "- тестировщик" << endl;
				player.gold = 1024;
				player.characteristics.wisdom = 20;
				player.characteristics.strength = 20;
				player.characteristics.constitution = 20;
				player.characteristics.dexterity = 20;
				player.characteristics.charisma = 20;
				player.characteristics.intelligence = 20;
				player.damageFace = 60;
				player.health = 256;
				player.maxHealth = 512;
				player.characteristics.armorClass = 30;
			}

			cout << "Нажмите любую клавишу, чтобы продолжить...";
			_getch(); // Ждет нажатия одной клавиши
			system("cls");			

			/*int index = 1;
			while (true)
			{
				cout << "Задайте класс доспехов (12): ";
				cin >> player.stats.armorClass;
				cout << endl;

				if (player.stats.armorClass != 12 && index == 1)
				{
					cout << "Вы уверены?" << endl;
					index++;
				}
				else if (player.stats.armorClass != 12 && index == 2)
				{
					cout << "Вы точно хотите это сделать..?" << endl;
					index++;
				}
				else if (player.stats.armorClass != 12 && index == 3)
				{
					cout << "Вы встали на тропу войны /(`o`)✓" << endl;
					cout << "Противники чувствуют себя сильнее..." << endl;
					enemy.health *= 100;
					enemy.maxHealth *= 100;
					enemy.damageFace *= 100;
					enemy.healthFlasks *= 100;
					enemy.stats.armorClass *= 100;
					break;
				}
				else
				{
					cout << "Мой хороший \\(>o<*)o" << endl;
					break;
				}
			}*/
		}
	}	

	for (int enemyCount = 0; enemyCount < enemyWave.size(); enemyCount++)
	{
		PAUSE_1_SECONDS;
		// МАГАЗИН
		shop.ShowItems();

		// Казино Алексея - случайное событие
		// Код казино
		SpecialEvent(player);
		

		// БИТВА
		//system("cls");
		ShowLoadingDots(chrono::milliseconds(200), RollDice(4));

		cout << TOP_BORDER << endl;
		cout << enemyWave[enemyCount].name << " выступает следующим!" << endl;
		cout << TOP_BORDER << endl;
		do
		{
			player.PrintStatus();
			PAUSE_1_SECONDS;
			
			if (enemyWave[enemyCount].minion != nullptr && enemyWave[enemyCount].minionSpawned)
			{
				enemyWave[enemyCount].minion->PrintStatus();
				PAUSE_1_SECONDS;
				userChoice = PlayerTurn(player, *enemyWave[enemyCount].minion);
			}
			else
			{
				enemyWave[enemyCount].PrintStatus();
				PAUSE_1_SECONDS;
				userChoice = PlayerTurn(player, enemyWave[enemyCount]);
			}

			if (fled)
			{
				cout << TOP_BORDER << endl;
				fled = false;
				break;
			}

			if (enemyWave[enemyCount].minion != nullptr && enemyWave[enemyCount].minion->health <= 0)
			{
				cout << "Ты выйграл битву, но не войну!" << endl;
				enemyWave[enemyCount].AddGold(enemyWave[enemyCount].minion->gold);
				enemyWave[enemyCount].minionSpawned = false;
			}

			if (enemyWave[enemyCount].health <= 0)
			{
				cout << "Победа, но какой ценой (o_o;)" << endl;

				player.AddGold(enemyWave[enemyCount].gold);

				break;
			}

			if (player.health <= 0)
			{
				cout << player.name << " пал!" << endl;
				break;
			}

			if (userChoice == 1 || userChoice == 2 || userChoice == 3 || userChoice == 4)
			{
				PAUSE_1_SECONDS;
				enemyChoice = EnemyTurn(enemyWave[enemyCount], player);
			}

			if (enemyWave[enemyCount].health <= 0)
			{
				cout << "Победа, но какой ценой (o_o;)" << endl;

				player.AddGold(enemyWave[enemyCount].gold);

				break;
			}

			if (userChoice == 0) enemyCount = 999; // РАБОТАЕТ - НЕ ТРОГАЙ!

		} while (userChoice != 0);
	}
}