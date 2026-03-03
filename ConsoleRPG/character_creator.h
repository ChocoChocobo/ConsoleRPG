#pragma once
#ifndef CHARACTER_CREATOR
#define CHARACTER_CREATOR
#include "character.h"

/// <summary>
/// Функция отвечает за распределение характеристик у персонажа.
/// </summary>
/// <returns>Возвращает набор характеристик</returns>
Characteristics DistributeCharacteristics();

/// <summary>
/// Функция отвечает за создание внешнего вида персонажа.
/// </summary>
/// <param name="player">Объект, который отвечает за персонажа игрока</param>
void CreateCharacter(Character& player);

#endif // !CHARACTER_CREATOR