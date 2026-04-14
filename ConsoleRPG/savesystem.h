#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <iostream>
#include "character.h"
#include "shop.h"

bool LoadGame(Character& player, Character& enemy, Shop& shop, const string& filename = "saves\\save.txt");

bool SaveGame(Character& player, Character& enemy, const string& filename = "saves\\save.txt");

bool SaveExists(const string& filename = "saves\\save.txt");

#endif 