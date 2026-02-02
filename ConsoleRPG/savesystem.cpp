#include "savesystem.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

using namespace std;

bool WriteKeyValue(ofstream& file, const string& key, const string& value)
{
	if (file.is_open())
	{
		file << key << "=" << value << endl;
		return true;
	}
	else return false;
}

bool SaveGame(const Character& player, const Character& enemy, const string& filename)
{
	filesystem::create_directory("saves");
	ofstream file;
	file.open(filename);// создание объекта и открытие файла
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

		file.close();
		cout << "Игра успешно сохранена! \\(@^0^@)/" << endl;
		return true;
	}
}

bool LoadGame(Character& player, Character& enemy, Shop& shop, const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Файл сохранения не найден! <(_ _)>" << endl;
        return false;
    }

    shop.availableItems.clear();
    player.inventory.clear();

    string line;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        size_t sep = line.find('=');
        if (sep == string::npos) continue;

        string key = line.substr(0, sep);
        string value = line.substr(sep + 1);

        // ===== ИГРОК =====
        if (key == "player.name") player.name = value;
        else if (key == "player.health") player.health = stoi(value);
        else if (key == "player.maxHealth") player.maxHealth = stoi(value);
        else if (key == "player.healthFlasks") player.healthFlasks = stoi(value);
        else if (key == "player.damageFace") player.damageFace = stoi(value);
        else if (key == "player.specialCooldown") player.specialCooldown = stoi(value);
        else if (key == "player.gold") player.gold = stoi(value);
        else if (key == "player.stats.armorClass") player.characteristics.armorClass = stoi(value);

        // ===== МАГАЗИН =====
        else if (key == "shop.name")
        {
            shop.name = value;
        }
        else if (key == "shop.items.count")
        {
            int count = stoi(value);
            shop.availableItems.resize(count);
        }
        else if (key.find("shop.items.") == 0)
        {
            // shop.items.X.field
            size_t firstDot = key.find('.', 11);
            size_t secondDot = key.find('.', firstDot + 1);

            int index = stoi(key.substr(11, firstDot - 11));
            string field = key.substr(secondDot + 1);

            if (index >= 0 && index < shop.availableItems.size())
            {
                Item& item = shop.availableItems[index];

                if (field == "name") item.name = value;
                else if (field == "description") item.description = value;
                else if (field == "price") item.price = stoi(value);
                else if (field == "quantity") item.quantity = stoi(value);
            }
        }

        // ===== ВРАГ =====
        else if (key == "enemy.name") enemy.name = value;
        else if (key == "enemy.health") enemy.health = stoi(value);
        else if (key == "enemy.maxHealth") enemy.maxHealth = stoi(value);
        else if (key == "enemy.healthFlasks") enemy.healthFlasks = stoi(value);
        else if (key == "enemy.damageFace") enemy.damageFace = stoi(value);
        else if (key == "enemy.specialCooldown") enemy.specialCooldown = stoi(value);
        else if (key == "enemy.gold") enemy.gold = stoi(value);
        else if (key == "enemy.stats.armorClass") enemy.characteristics.armorClass = stoi(value);
    }

    cout << "Сохранение успешно загружено! \\(@^0^@)/" << endl;
    file.close();
    return true;
}

bool SaveExists(const string& filename)
{
	ifstream file(filename);
	bool saveExists = bool(file);
	file.close();
	return saveExists;
}