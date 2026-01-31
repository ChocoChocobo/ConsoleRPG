#ifndef BATTLE_H
#define BATTLE_H
#include "character.h"
#include "user_interface.h"

int PlayerTurn(Character& player, Character& enemy);

int EnemyTurn(Character& enemy, Character& player);

void CheckWinLoseConditionPlayer(Character player);

void CheckWinLoseConditionEnemy(Character enemy);

#endif