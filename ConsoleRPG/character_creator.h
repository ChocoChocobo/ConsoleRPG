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

/// <summary>
/// Функция проверяет имя персонажа и если оно соответствует секретному имени, то игроку добавляются бонусы.
/// </summary>
/// <param name="player">Объект класса Character, который отвечает за персонажа игрока.</param>
void CheckSecretName(Character& player);

#endif // !CHARACTER_CREATOR