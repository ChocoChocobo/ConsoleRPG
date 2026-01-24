#ifndef BATTLE_H
#define BATTLE_H

#include "character.h"
#include "shop.h"

// Ход игрока
int PlayerTurn(Character& player, Character& enemy, Shop& shop);

// Ход врага
int EnemyTurn(Character& enemy, Character& player);

void CheckWinLoseConditionPlayer(Character player);
void CheckWinLoseConditionEnemy(Character enemy);

#endif
