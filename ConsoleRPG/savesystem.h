#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <fstream>
#include <string>
#include <vector>
#include "character.h"
#include "shop.h"
#include "item.h"

// Служебная функция записи ключ=значение
bool WriteKeyValue(std::ofstream& file, const std::string& key, const std::string& value);

// Сохранение вектора предметов (инвентарь, магазин)
bool SaveItems(std::ofstream& file, const std::string& prefix, const std::vector<Item>& items);

// Сохранение / загрузка игры
bool SaveGame(
    const Character& player,
    const Character& enemy,
    const Shop& shop,
    const std::string& filename = "saves\\save.txt"
);

bool LoadGame(
    Character& player,
    Character& enemy,
    const std::string& filename = "saves\\save.txt"
);

bool SaveExists(const std::string& filename = "saves\\save.txt");

#endif
