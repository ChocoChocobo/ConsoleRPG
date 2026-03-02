#include "savesystem.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include "shop.h" // Подключаем файл с определением структуры Shop

using namespace std;

// Функция записи пары ключ-значение в файл
bool WriteKeyValue(ofstream& file, const string& key, const string& value)
{
    if (file.is_open())
    {
        file << key << "=" << value << endl;
        return true;
    }
    else return false;
}

// Функция записи информации о предмете в файл
bool WriteItem(ofstream& file, const Item& item, const string& prefix)
{
    WriteKeyValue(file, prefix + ".name", item.name);
    WriteKeyValue(file, prefix + ".description", item.description);
    WriteKeyValue(file, prefix + ".weight", to_string(item.weight));
    WriteKeyValue(file, prefix + ".value", to_string(item.value));
    return true;
}

// Функция сохранения игры
bool SaveGame(const Character& player, const Character& enemy, const Shop& shop, const string& filename)
{
    filesystem::create_directory("saves");
    ofstream file;
    file.open(filename); // создание объекта и открытие файла
    if (!file.is_open())
    {
        cout << "Ошибка сохранения >:)" << endl;
        return false;
    }
    else
    {
        // Игрок
        WriteKeyValue(file, "player.name", player.name);
        WriteKeyValue(file, "player.health", to_string(player.health));
        WriteKeyValue(file, "player.maxHealth", to_string(player.maxHealth));
        WriteKeyValue(file, "player.healthFlasks", to_string(player.healthFlasks));
        WriteKeyValue(file, "player.damageFace", to_string(player.damageFace));
        WriteKeyValue(file, "player.specialCooldown", to_string(player.specialCooldown));
        WriteKeyValue(file, "player.gold", to_string(player.gold));
        WriteKeyValue(file, "player.stats.armorClass", to_string(player.characteristics.armorClass));

        // Враг
        WriteKeyValue(file, "enemy.name", enemy.name);
        WriteKeyValue(file, "enemy.health", to_string(enemy.health));
        WriteKeyValue(file, "enemy.maxHealth", to_string(enemy.maxHealth));
        WriteKeyValue(file, "enemy.healthFlasks", to_string(enemy.healthFlasks));
        WriteKeyValue(file, "enemy.damageFace", to_string(enemy.damageFace));
        WriteKeyValue(file, "enemy.specialCooldown", to_string(enemy.specialCooldown));
        WriteKeyValue(file, "enemy.gold", to_string(enemy.gold));
        WriteKeyValue(file, "enemy.stats.armorClass", to_string(enemy.characteristics.armorClass));

        // Сохранение информации о магазине
        WriteKeyValue(file, "shop.name", shop.name);
        for (size_t i = 0; i < shop.items.size(); ++i) {
            WriteItem(file, shop.items[i], "shop.item" + to_string(i+1));
        }

        // Сохранение инвентаря игрока
        for (size_t i = 0; i < player.inventory.size(); ++i) {
            WriteItem(file, player.inventory[i], "player.inventory.item" + to_string(i+1));
        }

        file.close();
        cout << "Игра успешно сохранена! \\(@^0^@)/" << endl;
        return true;
    }
}

// Функция загрузки игры
bool LoadGame(Character& player, Character& enemy, Shop& shop, const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Файл сохранения не найден! <(_　_)>" << endl;
        return false;
    }

    string line;
    if (getline(file, line)) if (line.empty()) return false;

    while (getline(file, line))
    {
        if (line.empty()) continue;
        size_t sep = line.find('=');
        string key = line.substr(0, sep);
        string value = line.substr(sep + 1);

        // Загрузка игрока
        if (key == "player.name") player.name = value;
        else if (key == "player.health") player.health = stoi(value);
        else if (key == "player.maxHealth") player.maxHealth = stoi(value);
        else if (key == "player.healthFlasks") player.healthFlasks = stoi(value);
        else if (key == "player.damageFace") player.damageFace = stoi(value);
        else if (key == "player.specialCooldown") player.specialCooldown = stoi(value);
        else if (key == "player.gold") player.gold = stoi(value);
        else if (key == "player.stats.armorClass") player.characteristics.armorClass = stoi(value);

        // Загрузка врага
        else if (key == "enemy.name") enemy.name = value;
        else if (key == "enemy.health") enemy.health = stoi(value);
        else if (key == "enemy.maxHealth") enemy.maxHealth = stoi(value);
        else if (key == "enemy.healthFlasks") enemy.healthFlasks = stoi(value);
        else if (key == "enemy.damageFace") enemy.damageFace = stoi(value);
        else if (key == "enemy.specialCooldown") enemy.specialCooldown = stoi(value);
        else if (key == "enemy.gold") enemy.gold = stoi(value);
        else if (key == "enemy.stats.armorClass") enemy.characteristics.armorClass = stoi(value);

        // Загрузка магазина
        else if (key == "shop.name") shop.name = value;
        else if (key.find("shop.item") == 0) {
            // Загружаем предметы магазина
            size_t itemIndex = stoi(key.substr(10)) - 1;
            Item item;
            item.name = value; // Пример: нужно парсить все данные предмета
            shop.items.push_back(item);
        }

        // Загрузка инвентаря игрока
        else if (key.find("player.inventory.item") == 0) {
            size_t itemIndex = stoi(key.substr(20)) - 1;
            Item item;
            item.name = value; // Пример: нужно парсить все данные предмета
            player.inventory.push_back(item);
        }
    }

    cout << "Сохранение успешно загружено!" << endl;
    file.close();
    return true;
}

// Проверка существования файла сохранения
bool SaveExists(const string& filename)
{
    ifstream file(filename);
    bool saveExists = bool(file);
    file.close();
    return saveExists;
}
