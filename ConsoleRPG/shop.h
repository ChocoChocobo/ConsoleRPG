#pragma once
#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <vector>
#include "item.h"
#include "character.h"

using namespace std;

/// <summary>
/// Структура магазина.
/// Отвечает за отображение товаров и взаимодействие игрока с ними [1, 2, 3, 4, 7, 8, 9].
/// </summary>
struct Shop
{
    /// <summary>
    /// Название магазина.
    /// </summary>
    string name;

    /// <summary>
    /// Список доступных предметов (по ссылке).
    /// </summary>
    vector<Item>& availableItems;

    /// <summary>
    /// Ссылка на игрока, совершающего покупки.
    /// </summary>
    Character& player;

    /// <summary>
    /// Конструктор магазина.
    /// </summary>
    /// <param name="_player">
    /// Игрок, взаимодействующий с магазином.
    /// </param>
    /// <param name="_availableItems">
    /// Список доступных предметов.
    /// </param>
    /// <param name="_name">
    /// Название магазина (по умолчанию "Дремучая Ива").
    /// </param>
    Shop(Character& _player, vector<Item>& _availableItems, string _name = "Дремучая Ива");

    /// <summary>
    /// Отображает список предметов и позволяет игроку выбрать товар.
    /// Возвращает результат взаимодействия [1, 2, 3, 4, 7, 8, 9].
    /// </summary>
    /// <returns>
    /// true — если покупка состоялась.
/// false — если игрок отменил действие или произошла ошибка.
/// </returns>
    bool ShowItems();

    // В дальнейшем можно добавить:
    // Item BuyItem(Item _chosenItem);
};

#endif // SHOP_H