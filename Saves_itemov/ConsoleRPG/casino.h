#pragma once
#ifndef CASINO_H
#define CASINO_H
#include "character.h"

void GameMoreLess(Character& player, bool GameReady);

void RoundGame(Character& player, bool GameReady);

void SpecialEvent(Character& player);
 
#endif