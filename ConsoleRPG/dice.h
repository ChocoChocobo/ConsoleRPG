#pragma once
#ifndef DICE_H
#define DICE_H

struct Character;

/// <summary>
/// Функция генерации случайного значения броска кубика.
/// Возвращает число от 1 до значения грани кубика включительно [1, 2, 3, 4, 7, 8, 9].
/// </summary>
/// <param name="face">
/// Количество граней кубика.
/// </param>
/// <returns>
/// Целое число в диапазоне от 1 до face.
/// </returns>
int RollDice(int face);

/// <summary>
/// Перечисление возможных результатов проверки действия.
/// Определяет тип исхода броска кубика при проверке успеха [1, 2, 3, 7, 8, 9].
/// </summary>
enum Results
{
    Success = 1,
    Fail = 2,
    CriticalSuccess = 3,
    CriticalFail = 4
};

/// <summary>
/// Функция проверки успешности действия персонажа.
/// Выполняет анализ характеристики персонажа и сложности действия.
/// Возвращает результат типа Results [1, 2, 3, 4, 7, 8, 9].
/// </summary>
/// <param name="character">
/// Указатель на объект Character, выполняющий действие.
/// </param>
/// <param name="characteristicValue">
/// Значение характеристики, используемой при проверке.
/// </param>
/// <param name="difficulty">
/// Сложность действия.
/// </param>
/// <returns>
/// Значение перечисления Results, определяющее исход действия.
/// </returns>
Results CheckSuccess(Character* character, int characteristicValue, int difficulty);

#endif