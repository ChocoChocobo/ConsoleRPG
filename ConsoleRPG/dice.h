#pragma once // Идентично
#ifndef DICE_H // Этой записи
#define DICE_H

struct Character;

/// <summary>
/// Функция отвечает за случайное значение от одного до значения face включительно.
/// </summary>
/// <param name="face">Верхняя мягкая граница случайного числа</param>
/// <returns>Случаное число от одного до face включительно</returns>
int RollDice(int face);

/// <summary>
/// Перепись отвечает за удобство возврата результата проверки
/// </summary>
enum Results
{
    Success = 1,
    Fail = 2,
    CriticalSuccess = 3,
    CriticalFail = 4
};

/// <summary>
/// Функция отвечает за результат проверки при атаке и не только.
/// </summary>
/// <param name="character">Персонаж, который совершает проверку</param>
/// <param name="characteristicValue">Бонус к проверке</param>
/// <param name="difficulty">Сложность проверки</param>
/// <returns>Если результат "D20" с модификаторами больше или равен сложности проверке возвращает Success, иначе Fail. Если на "D20" выпало число 20 возвращает CriticalSuccess. Если на "D20" выпало число 1 возвращает CriticalFail</returns>
Results CheckSuccess(Character* character, int characteristicValue, int difficulty);
#endif