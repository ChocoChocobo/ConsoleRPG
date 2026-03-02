#pragma once
#ifndef CHARACTER_CREATOR
#define CHARACTER_CREATOR
#include "character.h"

/// <summary>
/// Функция распределения характеристик персонажа. 
/// Возвращает структуру Characteristics с установленными значениями характеристик игрока [1, 2, 3, 4, 7, 8, 9].
/// </summary>
/// <returns>
/// Объект Characteristics с заполненными полями характеристик.
/// </returns>
Characteristics DistributeCharacteristics();

/// <summary>
/// Функция создания персонажа. 
/// Заполняет переданный объект Character начальными данными игрока [1, 2, 3, 4, 7, 8, 9].
/// </summary>
/// <param name="player">
/// Ссылка на объект Character, который инициализируется данными персонажа.
/// </param>
void CreateCharacter(Character& player);

#endif // !CHARACTER_CREATOR