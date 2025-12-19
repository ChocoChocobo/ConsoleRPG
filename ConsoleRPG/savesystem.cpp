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
		WriteKeyValue(file, "player.stats.armorClass", to_string(player.stats.armorClass));

		// Враг
		WriteKeyValue(file, "enemy.name", enemy.name);
		WriteKeyValue(file, "enemy.health", to_string(enemy.health));
		WriteKeyValue(file, "enemy.maxHealth", to_string(enemy.maxHealth));
		WriteKeyValue(file, "enemy.healthFlasks", to_string(enemy.healthFlasks));
		WriteKeyValue(file, "enemy.damageFace", to_string(enemy.damageFace));
		WriteKeyValue(file, "enemy.specialCooldown", to_string(enemy.specialCooldown));
		WriteKeyValue(file, "enemy.gold", to_string(enemy.gold));
		WriteKeyValue(file, "enemy.stats.armorClass", to_string(enemy.stats.armorClass));

		file.close();
		cout << "Игра успешно сохранена! \\(@^0^@)/" << endl;
		return true;
	}
}

bool LoadGame(Character& player, Character& enemy, const string& filename)
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

		if (key == "player.name") player.name = value;
		else if (key == "player.health") player.health = stoi(value);
		else if (key == "player.maxHealth") player.maxHealth = stoi(value);
		else if (key == "player.healthFlasks") player.healthFlasks = stoi(value);
		else if (key == "player.damageFace") player.damageFace = stoi(value);
		else if (key == "player.specialCooldown") player.specialCooldown = stoi(value);
		else if (key == "player.gold") player.gold = stoi(value);
		else if (key == "player.stats.armorClass") player.stats.armorClass = stoi(value);
	}

	cout << "Сохранение успешно загружено!" << endl;
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