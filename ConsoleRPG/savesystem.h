#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <iostream>
#include "character.h"

/// <summary>
/// Функция отвечает за загрузку игры из файла.
/// </summary>
/// <param name="player">Объект, отвечающий за персонажа игрока</param>
/// <param name="enemy">Объект, отвечающий за персонажа врага</param>
/// <param name="filename">Путь к файлу с сохранением</param>
/// <returns>Если загрузка удачна возвращает true, иначе false</returns>
bool LoadGame(Character& player, Character& enemy, const string& filename = "saves\\save.txt");

/// <summary>
/// Сохраняет поля игрока, его врага и магазина в файл
/// </summary>
/// <param name="player">Объект, отвечающий за персонажа игрока</param>
/// <param name="enemy">Объект, отвечающий за персонажа врага</param>
/// <param name="filename">Путь к файлу с сохранением</param>
/// <returns>Если сохранение удачно возвращает true, иначе false</returns>
bool SaveGame(const Character& player, const Character& enemy, const string& filename = "saves\\save.txt");

/// <summary>
/// Проверяет наличие сохранения в папке
/// </summary>
/// <param name="filename">Путь к файлу с сохранением</param>
/// <returns>Возвращает true если файл сохранения есть, иначе false</returns>
bool SaveExists(const string& filename = "saves\\save.txt");

#endif 