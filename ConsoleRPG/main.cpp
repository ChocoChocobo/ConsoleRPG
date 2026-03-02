#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <thread>
#include <chrono>
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

// ДОБАВЛЕНО: Массивы строк для разных действий
vector<string> battleStartMessages = {
    " выходит на поле боя!",
    " готовится к атаке!",
    " появляется из темноты!",
    " жаждет твоей крови!",
    " преграждает путь!"
};

vector<string> victoryMessages = {
    "Победа! Враг повержен!",
    "Ты выиграл этот бой!",
    "Противник пал в битве!",
    "Слава победителю!",
    "Еще один враг побежден!"
};

vector<string> defeatMessages = {
    " пал в бою...",
    " проиграл эту битву...",
    " не выдержал натиска...",
    " погиб смертью храбрых...",
    " отправился к предкам..."
};

// ДОБАВЛЕНО: Структура для настроек сложности
struct DifficultySettings {
    string name;
    float enemyHpMultiplier;
    float enemyDamageMultiplier;
    float playerHealMultiplier;
    int goldMultiplier;
};

// ДОБАВЛЕНО: Функция для распределения 75 очков характеристик
Characteristics Distribute75Points() {
    Characteristics stats;
    int pointsLeft = 75;
    int choice;
    
    stats.strength = 8;
    stats.dexterity = 8;
    stats.constitution = 8;
    stats.intelligence = 8;
    stats.wisdom = 8;
    stats.charisma = 8;
    
    system("cls");
    cout << "=========================================" << endl;
    cout << "     РАСПРЕДЕЛЕНИЕ ХАРАКТЕРИСТИК" << endl;
    cout << "=========================================" << endl;
    cout << "У вас 75 очков для распределения" << endl;
    cout << "База: 8 в каждой характеристике" << endl << endl;
    
    do {
        cout << "Осталось очков: " << pointsLeft << endl;
        cout << "1. Сила: " << stats.strength << " (влияет на урон)" << endl;
        cout << "2. Ловкость: " << stats.dexterity << " (влияет на класс брони)" << endl;
        cout << "3. Телосложение: " << stats.constitution << " (влияет на здоровье)" << endl;
        cout << "4. Интеллект: " << stats.intelligence << endl;
        cout << "5. Мудрость: " << stats.wisdom << endl;
        cout << "6. Харизма: " << stats.charisma << " (влияет на цены в магазине)" << endl;
        cout << "0. Завершить распределение" << endl;
        cout << "Выберите характеристику: ";
        cin >> choice;
        
        if (choice >= 1 && choice <= 6 && pointsLeft > 0) {
            int points;
            cout << "Сколько очков добавить (1-" << pointsLeft << "): ";
            cin >> points;
            
            if (points > 0 && points <= pointsLeft) {
                switch(choice) {
                    case 1: stats.strength += points; break;
                    case 2: stats.dexterity += points; break;
                    case 3: stats.constitution += points; break;
                    case 4: stats.intelligence += points; break;
                    case 5: stats.wisdom += points; break;
                    case 6: stats.charisma += points; break;
                }
                pointsLeft -= points;
            }
        }
    } while (choice != 0 && pointsLeft > 0);
    
    // Расчет производных характеристик
    stats.armorClass = 10 + (stats.dexterity - 8) / 2;
    
    return stats;
}

// Функция для имитации прогрузки
void simulate_loading(const string& action, int min_sec = 2, int max_sec = 5) {
    int delay = min_sec + rand() % (max_sec - min_sec + 1);
    cout << "Прогрузка... " << action << " (ожидайте " << delay << " секунд)" << endl;
    // Задержка для имитации прогрузки
    this_thread::sleep_for(chrono::seconds(delay));
    cout << action << " завершено!" << endl;
}

// ДОБАВЛЕНО: Меню паузы с настройками сложности
void ShowPauseMenu(Character& player, DifficultySettings& currentDifficulty) {
    int pauseChoice;
    
    do {
        system("cls");
        cout << "=========================================" << endl;
        cout << "              МЕНЮ ПАУЗЫ" << endl;
        cout << "=========================================" << endl;
        cout << "1. Продолжить игру" << endl;
        cout << "2. Настройки сложности" << endl;
        cout << "3. Сохранить игру" << endl;
        cout << "4. Загрузить игру" << endl;
        cout << "5. Выход в главное меню" << endl;
        cout << "0. Отмена" << endl;
        cout << "Ваш выбор: ";
        cin >> pauseChoice;
        
        switch(pauseChoice) {
            case 2: {
                system("cls");
                cout << "=========================================" << endl;
                cout << "         НАСТРОЙКИ СЛОЖНОСТИ" << endl;
                cout << "=========================================" << endl;
                cout << "1. Легкая - враги слабее, золота больше" << endl;
                cout << "2. Обычная - стандартные параметры" << endl;
                cout << "3. Сложная - враги сильнее" << endl;
                cout << "4. Хардкор - враги очень сильные" << endl;
                cout << "Выберите сложность: ";
                
                int diffChoice;
                cin >> diffChoice;
                
                switch(diffChoice) {
                    case 1:
                        currentDifficulty.name = "Легкая";
                        currentDifficulty.enemyHpMultiplier = 0.7f;
                        currentDifficulty.enemyDamageMultiplier = 0.6f;
                        currentDifficulty.playerHealMultiplier = 1.5f;
                        currentDifficulty.goldMultiplier = 2;
                        break;
                    case 2:
                        currentDifficulty.name = "Обычная";
                        currentDifficulty.enemyHpMultiplier = 1.0f;
                        currentDifficulty.enemyDamageMultiplier = 1.0f;
                        currentDifficulty.playerHealMultiplier = 1.0f;
                        currentDifficulty.goldMultiplier = 1;
                        break;
                    case 3:
                        currentDifficulty.name = "Сложная";
                        currentDifficulty.enemyHpMultiplier = 1.5f;
                        currentDifficulty.enemyDamageMultiplier = 1.3f;
                        currentDifficulty.playerHealMultiplier = 0.8f;
                        currentDifficulty.goldMultiplier = 1;
                        break;
                    case 4:
                        currentDifficulty.name = "Хардкор";
                        currentDifficulty.enemyHpMultiplier = 2.0f;
                        currentDifficulty.enemyDamageMultiplier = 1.8f;
                        currentDifficulty.playerHealMultiplier = 0.5f;
                        currentDifficulty.goldMultiplier = 3;
                        break;
                }
                cout << "Сложность изменена на: " << currentDifficulty.name << endl;
                Sleep(1500);
                break;
            }
            case 3:
                cout << "Игра сохранена!" << endl;
                SaveGame(player, player);
                Sleep(1000);
                break;
            case 4:
                cout << "Игра загружена!" << endl;
                LoadGame(player, player);
                Sleep(1000);
                break;
        }
    } while (pauseChoice != 1 && pauseChoice != 0);
}

// ДОБАВЛЕНО: Эффект клаустрофобии
void ApplyClaustrophobia(Character& player) {
    cout << "\n*** Стены начинают сжиматься... ***" << endl;
    cout << "*** Вам становится душно и тесно! ***" << endl;
    
    int fearRoll = rand() % 20 + 1;
    
    if (fearRoll <= 5) {
        cout << "Паника охватывает вас! Вы теряете концентрацию!" << endl;
        player.characteristics.armorClass -= 2;
        cout << "Класс брони уменьшен на 2!" << endl;
    }
    else if (fearRoll >= 16) {
        cout << "Страх превращается в ярость! Вы бьете сильнее!" << endl;
        player.damageFace += 2;
        cout << "Урон увеличен на 2!" << endl;
    }
    else {
        cout << "Вы справляетесь с клаустрофобией." << endl;
    }
    
    _getch();
}

// ДОБАВЛЕНО: Секретная комната (БЕЗ ASCII АРТА)
void EnterSecretRoom(Character& player) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "         СЕКРЕТНАЯ КОМНАТА" << endl;
    cout << "=========================================" << endl;
    cout << "Вы нашли тайную комнату за пультом!" << endl;
    cout << "Здесь хранятся древние сокровища..." << endl << endl;
    
    int lootRoll = rand() % 100 + 1;
    
    if (lootRoll >= 95) {
        cout << "ЛЕГЕНДАРНЫЙ АРТЕФАКТ: Амулет бессмертия!" << endl;
        player.maxHealth += 50;
        player.health += 50;
        player.characteristics.armorClass += 5;
    }
    else if (lootRoll >= 80) {
        cout << "ЭПИЧЕСКИЙ МЕЧ: Клинок тысячи истин!" << endl;
        player.damageFace += 10;
    }
    else if (lootRoll >= 60) {
        cout << "МАГИЧЕСКОЕ КОЛЬЦО: Кольцо защиты!" << endl;
        player.characteristics.armorClass += 3;
    }
    else if (lootRoll >= 30) {
        cout << "ЗОЛОТОЙ СУНДУК: Много золота!" << endl;
        player.gold += 200;
    }
    else {
        cout << "ОБЫЧНЫЙ СУНДУК: Немного золота и зелья" << endl;
        player.gold += 50;
        player.healthFlasks += 2;
    }
    
    cout << "\nНажмите любую клавишу чтобы продолжить...";
    _getch();
}

void main()
{
    setlocale(LC_ALL, "Ru");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(0));

    int userChoice;
    int enemyChoice;
    bool fled = false;
    
    // ДОБАВЛЕНО: Настройки сложности по умолчанию
    DifficultySettings currentDifficulty;
    currentDifficulty.name = "Обычная";
    currentDifficulty.enemyHpMultiplier = 1.0f;
    currentDifficulty.enemyDamageMultiplier = 1.0f;
    currentDifficulty.playerHealMultiplier = 1.0f;
    currentDifficulty.goldMultiplier = 1;

    Character player("Безымянный", 12, 8, 0, 10);
    
    Character enemy("Блоха", 10, 4, 0, 10);
    Character enemy1("Цербер", 25, 8, 0, 25);
    Character enemy2("Моль-беспилотник", 2, 10, 0, 10);

    Character condeiMinion("Кондей", 12, 4, 0, 0);
    Character enemy3("Пульт от кондиционера", 45, 8, 0, 1000, condeiMinion, 15);

    vector<Character> enemyWave = {enemy, enemy1, enemy2, enemy3};

    vector<Item> shopItems = {};

    // ИЗМЕНЕНО: Добавил больше предметов в магазин
    Item item1("Зубы деда", "Все что вам могло осталось в наследство", 2, 32);
    Item item2("Рок единорога", "Самый качественный звук", 5, 1);
    Item item3("Батарейки", "Батарейки для пульта от кондиционера", 100, 4);
    Item item4("Меч-кладенец", "Легендарный меч", 50, 15);
    Item item5("Зелье здоровья", "Восстанавливает 20 HP", 30, 10);
    Item item6("Кольцо защиты", "Повышает класс брони", 40, 8);

    shopItems.push_back(item2);
    shopItems.push_back(item1);
    shopItems.push_back(item3);
    shopItems.push_back(item4);
    shopItems.push_back(item5);
    shopItems.push_back(item6);

    Shop shop(player, shopItems);
    
    cout << "\t\t-----CPlusPlus Console RPG!-----" << endl;
    cout << "В данной текстовой ролевой игре вам необходимо победить врага в формате пошаговых боев. При совершении каждого действия происходит бросок кубика д20, который определяет исход результата. Удачи!" << endl;
    
    // ДОБАВЛЕНО: Проверка на нажатие клавиши паузы (P)
    cout << "(Нажмите P для открытия меню паузы во время игры)" << endl;
    
    if (SaveExists())
    {
        cout << endl << "Обнаружено сохранение. Для его загрузки нажмите 1. Для начала новой игрой нажмите 0." << endl;
        cin >> userChoice;
        if (userChoice == 1) LoadGame(player, enemy);
        else
        {
            ShowProgressBar(3.2, 50, "Загрузка.", '#');
            system("cls");
            
            // ИЗМЕНЕНО: Используем новую функцию распределения 75 очков
            player.characteristics = Distribute75Points();

            system("cls");
            cout << "Задайте имя вашему герою: ";
            cin.ignore(1000, '\n');
            getline(cin, player.name);
            cout << endl;

            // Секретные имена (оставил как есть)
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
                player.damageFace = 10;                
            }
            else if (player.name == "Bytik Menich")
            {
                cout << "Вы вписали секретное имя!" << endl;
                Item item4("Батарейки", "Батарейки для пульта от кондиционера", 100, 2);
                Item item5("Шпингалет", "Арбитр мироздания в твоей ванной", 1, 1);
                player.inventory.push_back(item4);
                player.inventory.push_back(item5);
            }
            else if (player.name == "Гном Плюсокрад")
            // ДОБАВЛЕНО: Секретное имя для геймера
else if (player.name == "Gamer" || player.name == "gamer" || 
         player.name == "Игрок" || player.name == "игрок" ||
         player.name == "Noob" || player.name == "noob" ||
         player.name == "Pro" || player.name == "pro")
{
    cout << "====================" << endl;
    cout << "ГЕЙМЕР ДЕТЕКТЕД!" << endl;
    cout << "====================" << endl;
    cout << "Ты провел тысячи часов в играх," << endl;
    cout << "теперь пришло время применить навыки!" << endl;
    cout << endl;
    cout << "Бонусы за геймерский опыт:" << endl;
    cout << "+8 к урону (натренированная реакция)" << endl;
    cout << "+4 к классу брони (скилловый мув)" << endl;
    cout << "+50 золота (нашел в сундуке)" << endl;
    cout << "+2 флакона здоровья (аптечки с запасом)" << endl;
    cout << endl;
    cout << "Особый навык: 'Last hit' - добивание врага с 50% хп" << endl;
    
    player.damageFace += 8;
    player.characteristics.armorClass += 4;
    player.gold += 50;
    player.healthFlasks += 2;
}
            {
                cout << "Вы вписали секретное имя!" << endl;
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
            _getch();
            system("cls");
        }
    }
    else
    {
        // ИЗМЕНЕНО: Сразу распределяем характеристики для новой игры
        system("cls");
        player.characteristics = Distribute75Points();
        
        system("cls");
        cout << "Задайте имя вашему герою: ";
        cin.ignore(1000, '\n');
        getline(cin, player.name);
    }

    for (int enemyCount = 0; enemyCount < enemyWave.size(); enemyCount++)
    {
        // ДОБАВЛЕНО: Применяем множители сложности к врагу
        enemyWave[enemyCount].health = int(enemyWave[enemyCount].health * currentDifficulty.enemyHpMultiplier);
        enemyWave[enemyCount].maxHealth = enemyWave[enemyCount].health;
        enemyWave[enemyCount].damageFace = int(enemyWave[enemyCount].damageFace * currentDifficulty.enemyDamageMultiplier);
        
        simulate_loading("Прогрузка боя");

        // МАГАЗИН
        shop.ShowItems();

        // Казино Алексея
        SpecialEvent(player);
        
        // ДОБАВЛЕНО: Эффект клаустрофобии в определенных битвах
        if (enemyCount == 1 || enemyCount == 3) {
            ApplyClaustrophobia(player);
        }

        // БИТВА
        simulate_loading("Прогрузка действий врага и игрока");

        cout << TOP_BORDER << endl;
        
        // ИЗМЕНЕНО: Используем массив строк для сообщения
        int msgIndex = rand() % battleStartMessages.size();
        cout << enemyWave[enemyCount].name << battleStartMessages[msgIndex] << endl;
        
        cout << TOP_BORDER << endl;
        
        do
        {
            // ДОБАВЛЕНО: Проверка нажатия клавиши паузы
            if (_kbhit()) {
                char key = _getch();
                if (key == 'p' || key == 'P') {
                    ShowPauseMenu(player, currentDifficulty);
                }
            }
            
            player.PrintStatus();
            simulate_loading("Прогрузка состояния игрока", 1, 2);
            
            if (enemyWave[enemyCount].minion != nullptr && enemyWave[enemyCount].minionSpawned)
            {
                enemyWave[enemyCount].minion->PrintStatus();
                simulate_loading("Прогрузка состояния миньона", 1, 2);
                userChoice = PlayerTurn(player, *enemyWave[enemyCount].minion);
            }
            else
            {
                enemyWave[enemyCount].PrintStatus();
                simulate_loading("Прогрузка состояния врага", 1, 2);
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
                int winIndex = rand() % victoryMessages.size();
                cout << victoryMessages[winIndex] << endl;
                
                player.AddGold(enemyWave[enemyCount].gold * currentDifficulty.goldMultiplier);
                
                if (enemyWave[enemyCount].name == "Пульт от кондиционера") {
                    EnterSecretRoom(player);
                }
                
                break;
            }

            if (player.health <= 0)
            {
                int loseIndex = rand() % defeatMessages.size();
                cout << player.name << defeatMessages[loseIndex] << endl;
                break;
            }

            if (userChoice == 1 || userChoice == 2 || userChoice == 3 || userChoice == 4)
            {
                simulate_loading("Прогрузка хода врага", 2, 3);
                enemyChoice = EnemyTurn(enemyWave[enemyCount], player);
            }

        } while (userChoice != 0);
    }
    
    // ДОБАВЛЕНО: Финальное сообщение
    cout << "\n=========================================" << endl;
    cout << "         ИГРА ПРОЙДЕНА!" << endl;
    cout << "=========================================" << endl;
    cout << "Поздравляем с победой!" << endl;
    _getch();
}
