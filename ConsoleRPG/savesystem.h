#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <iostream>
#include "character.h"
#include "shop.h"

bool LoadGame(Character& player, Character& enemy, const string& filename = "saves\\save.txt");

bool SaveGame(const Character& player, const Character& enemy, const Shop& shop, const string& filename = "saves\\save.txt");

bool SaveExists(const string& filename = "saves\\save.txt");

#endif 