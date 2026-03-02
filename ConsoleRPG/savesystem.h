#pragma once
#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <iostream>
#include <string>
#include "character.h"

/// <summary>
/// Загружает данные игры из файла сохранения.
/// Восстанавливает состояние игрока и противника [1, 2, 3, 4, 7, 8, 9].
/// </summary>
/// <param name="player">
/// Ссылка на объект игрока, в который будут загружены данные.
/// </param>
/// <param name="enemy">
/// Ссылка на объект противника, в который будут загружены данные.
/// </param>
/// <param name="filename">
/// Путь к файлу сохранения. По умолчанию "saves\\save.txt".
/// </param>
/// <returns>
/// true — если загрузка прошла успешно.
/// false — если произошла ошибка или файл не найден.
/// </returns>
bool LoadGame(Character& player, Character& enemy, const string& filename = "saves\\save.txt");


/// <summary>
/// Сохраняет текущее состояние игры в файл.
/// Записывает данные игрока и противника [1, 2, 3, 4, 7, 8, 9].
/// </summary>
/// <param name="player">
/// Константная ссылка на объект игрока.
/// </param>
/// <param name="enemy">
/// Константная ссылка на объект противника.
/// </param>
/// <param name="filename">
/// Путь к файлу сохранения. По умолчанию "saves\\save.txt".
/// </param>
/// <returns>
/// true — если сохранение прошло успешно.
/// false — если произошла ошибка записи.
/// </returns>
bool SaveGame(const Character& player, const Character& enemy, const string& filename = "saves\\save.txt");


/// <summary>
/// Проверяет существование файла сохранения.
/// Используется перед загрузкой игры [1, 2, 3, 4, 7, 8, 9].
/// </summary>
/// <param name="filename">
/// Путь к файлу сохранения. По умолчанию "saves\\save.txt".
/// </param>
/// <returns>
/// true — если файл существует.
/// false — если файл отсутствует.
/// </returns>
bool SaveExists(const string& filename = "saves\\save.txt");

#endif // SAVESYSTEM_H