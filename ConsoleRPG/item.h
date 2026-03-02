#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>

using namespace std;

/// <summary>
/// Структура предмета.
/// Содержит данные о названии, описании, цене и количестве предмета [1, 2, 3, 4, 7, 8, 9].
/// </summary>
struct Item
{
    string name;
    string description;
    int price;
    int quantity;

    /// <summary>
    /// Конструктор предмета.
    /// Инициализирует поля структуры Item переданными значениями [1, 2, 3, 7, 9].
    /// </summary>
    /// <param name="_name">Название предмета.</param>
    /// <param name="_description">Описание предмета.</param>
    /// <param name="_price">Стоимость предмета.</param>
    /// <param name="_quantity">Количество предметов.</param>
    Item(string _name, string _description, int _price, int _quantity);

    /// <summary>
    /// Выводит информацию о предмете в консоль [1, 2, 3, 4, 7, 8, 9].
    /// </summary>
    void ShowInfo();

    /// <summary>
    /// Проверяет возможность покупки предмета.
    /// Сравнивает стоимость предмета с количеством золота игрока [1, 2, 3, 4, 7, 8, 9].
    /// </summary>
    /// <param name="playerGold">
    /// Количество золота у игрока.
    /// </param>
    /// <returns>
    /// true — если покупка возможна, false — если недостаточно золота.
    /// </returns>
    bool BuyItem(int playerGold);
};

#endif