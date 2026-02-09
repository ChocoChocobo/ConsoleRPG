#include "character_creator.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Функция для создания внешности персонажа
Appearance DefineAppearance()
{
    Appearance definedAppearance;
    int choice;
    
    cout << "\n=== СОЗДАНИЕ ВНЕШНОСТИ ПЕРСОНАЖА ===\n";
    
    // 1. Цвет кожи
    cout << "\n1. Выберите цвет кожи:" << endl;
    cout << "1. Бледная" << endl;
    cout << "2. Светлая" << endl;
    cout << "3. Смуглая" << endl;
    cout << "4. Темная" << endl;
    cout << "5. Оливковая" << endl;
    cout << "6. Загорелая" << endl;
    cout << "Ваш выбор (1-6): ";
    cin >> choice;
    
    switch(choice) {
        case 1: definedAppearance.skinColor = "Бледная"; break;
        case 2: definedAppearance.skinColor = "Светлая"; break;
        case 3: definedAppearance.skinColor = "Смуглая"; break;
        case 4: definedAppearance.skinColor = "Темная"; break;
        case 5: definedAppearance.skinColor = "Оливковая"; break;
        case 6: definedAppearance.skinColor = "Загорелая"; break;
        default: definedAppearance.skinColor = "Светлая"; break;
    }
    
    // 2. Цвет волос
    cout << "\n2. Выберите цвет волос:" << endl;
    cout << "1. Черные" << endl;
    cout << "2. Коричневые" << endl;
    cout << "3. Русые" << endl;
    cout << "4. Светлые" << endl;
    cout << "5. Рыжие" << endl;
    cout << "6. Седые" << endl;
    cout << "7. Фиолетовые" << endl;
    cout << "Ваш выбор (1-7): ";
    cin >> choice;
    
    switch(choice) {
        case 1: definedAppearance.hairColor = "Черные"; break;
        case 2: definedAppearance.hairColor = "Коричневые"; break;
        case 3: definedAppearance.hairColor = "Русые"; break;
        case 4: definedAppearance.hairColor = "Светлые"; break;
        case 5: definedAppearance.hairColor = "Рыжие"; break;
        case 6: definedAppearance.hairColor = "Седые"; break;
        case 7: definedAppearance.hairColor = "Фиолетовые"; break;
        default: definedAppearance.hairColor = "Коричневые"; break;
    }
    
    // 3. Стиль волос
    cout << "\n3. Выберите стиль волос:" << endl;
    cout << "1. Короткие" << endl;
    cout << "2. Длинные" << endl;
    cout << "3. Лысый/лысая" << endl;
    cout << "4. Ирокез" << endl;
    cout << "5. Хвост" << endl;
    cout << "6. Растрепанные" << endl;
    cout << "7. Косы" << endl;
    cout << "Ваш выбор (1-7): ";
    cin >> choice;
    
    switch(choice) {
        case 1: definedAppearance.hairStyle = "Короткие"; break;
        case 2: definedAppearance.hairStyle = "Длинные"; break;
        case 3: definedAppearance.hairStyle = "Лысый/лысая"; break;
        case 4: definedAppearance.hairStyle = "Ирокез"; break;
        case 5: definedAppearance.hairStyle = "Хвост"; break;
        case 6: definedAppearance.hairStyle = "Растрепанные"; break;
        case 7: definedAppearance.hairStyle = "Косы"; break;
        default: definedAppearance.hairStyle = "Короткие"; break;
    }
    
    // 4. Цвет глаз
    cout << "\n4. Выберите цвет глаз:" << endl;
    cout << "1. Карие" << endl;
    cout << "2. Голубые" << endl;
    cout << "3. Зеленые" << endl;
    cout << "4. Серые" << endl;
    cout << "5. Янтарные" << endl;
    cout << "6. Разные" << endl;
    cout << "Ваш выбор (1-6): ";
    cin >> choice;
    
    switch(choice) {
        case 1: definedAppearance.eyeColor = "Карие"; break;
        case 2: definedAppearance.eyeColor = "Голубые"; break;
        case 3: definedAppearance.eyeColor = "Зеленые"; break;
        case 4: definedAppearance.eyeColor = "Серые"; break;
        case 5: definedAppearance.eyeColor = "Янтарные"; break;
        case 6: definedAppearance.eyeColor = "Разные"; break;
        default: definedAppearance.eyeColor = "Карие"; break;
    }
    
    // 5. Растительность на лице (для мужских персонажей)
    cout << "\n5. Выберите растительность на лице:" << endl;
    cout << "1. Нет" << endl;
    cout << "2. Легкая щетина" << endl;
    cout << "3. Усы" << endl;
    cout << "4. Борода" << endl;
    cout << "5. Длинная борода" << endl;
    cout << "Ваш выбор (1-5): ";
    cin >> choice;
    
    switch(choice) {
        case 1: definedAppearance.facialHair = "Нет"; break;
        case 2: definedAppearance.facialHair = "Легкая щетина"; break;
        case 3: definedAppearance.facialHair = "Усы"; break;
        case 4: definedAppearance.facialHair = "Борода"; break;
        case 5: definedAppearance.facialHair = "Длинная борода"; break;
        default: definedAppearance.facialHair = "Нет"; break;
    }
    
    // 6. Шрамы
    cout << "\n6. Выберите шрамы:" << endl;
    cout << "1. Нет" << endl;
    cout << "2. Шрам на щеке" << endl;
    cout << "3. Шрам на лбу" << endl;
    cout << "4. Порезы на руках" << endl;
    cout << "5. Старый шрам на груди" << endl;
    cout << "Ваш выбор (1-5): ";
    cin >> choice;
    
    switch(choice) {
        case 1: definedAppearance.scars = "Нет"; break;
        case 2: definedAppearance.scars = "Шрам на щеке"; break;
        case 3: definedAppearance.scars = "Шрам на лбу"; break;
        case 4: definedAppearance.scars = "Порезы на руках"; break;
        case 5: definedAppearance.scars = "Старый шрам на груди"; break;
        default: definedAppearance.scars = "Нет"; break;
    }
    
    // 7. Татуировки
    cout << "\n7. Выберите татуировки:" << endl;
    cout << "1. Нет" << endl;
    cout << "2. Племенные узоры" << endl;
    cout << "3. Рунические символы" << endl;
    cout << "4. Портрет дракона" << endl;
    cout << "5. Магические знаки" << endl;
    cout << "Ваш выбор (1-5): ";
    cin >> choice;
    
    switch(choice) {
        case 1: definedAppearance.tattoos = "Нет"; break;
        case 2: definedAppearance.tattoos = "Племенные узоры"; break;
        case 3: definedAppearance.tattoos = "Рунические символы"; break;
        case 4: definedAppearance.tattoos = "Портрет дракона"; break;
        case 5: definedAppearance.tattoos = "Магические знаки"; break;
        default: definedAppearance.tattoos = "Нет"; break;
    }
    
    // 8. Стиль одежды
    cout << "\n8. Выберите стиль одежды:" << endl;
    cout << "1. Кожаная броня" << endl;
    cout << "2. Кольчуга" << endl;
    cout << "3. Магические робы" << endl;
    cout << "4. Путниковая одежда" << endl;
    cout << "5. Благородные одежды" << endl;
    cout << "6. Разбойничья форма" << endl;
    cout << "Ваш выбор (1-6): ";
    cin >> choice;
    
    switch(choice) {
        case 1: definedAppearance.clothingStyle = "Кожаная броня"; break;
        case 2: definedAppearance.clothingStyle = "Кольчуга"; break;
        case 3: definedAppearance.clothingStyle = "Магические робы"; break;
        case 4: definedAppearance.clothingStyle = "Путниковая одежда"; break;
        case 5: definedAppearance.clothingStyle = "Благородные одежды"; break;
        case 6: definedAppearance.clothingStyle = "Разбойничья форма"; break;
        default: definedAppearance.clothingStyle = "Путниковая одежда"; break;
    }
    
    // 9. Аксессуары
    cout << "\n9. Выберите аксессуары:" << endl;
    cout << "1. Нет" << endl;
    cout << "2. Серьга" << endl;
    cout << "3. Ожерелье" << endl;
    cout << "4. Несколько колец" << endl;
    cout << "5. Шляпа" << endl;
    cout << "6. Повязка на глаз" << endl;
    cout << "Ваш выбор (1-6): ";
    cin >> choice;
    
    switch(choice) {
        case 1: definedAppearance.accessories = "Нет"; break;
        case 2: definedAppearance.accessories = "Серьга"; break;
        case 3: definedAppearance.accessories = "Ожерелье"; break;
        case 4: definedAppearance.accessories = "Несколько колец"; break;
        case 5: definedAppearance.accessories = "Шляпа"; break;
        case 6: definedAppearance.accessories = "Повязка на глаз"; break;
        default: definedAppearance.accessories = "Нет"; break;
    }
    
    cout << "\n✓ Внешность персонажа создана!\n";
    
    return definedAppearance;
}

// Обновленная функция CreateCharacter
void CreateCharacter(Character& player)
{
    cout << "СОЗДАНИЕ ПЕРСОНАЖА\n";
    cout << "===================\n";

    // Имя персонажа
    cout << "\nВведите имя персонажа: ";
    cin.ignore(1000, '\n');
    getline(cin, player.name);

    // Выбор типа создания внешности
    cout << "\n=== НАСТРОЙКА ВНЕШНОСТИ ===" << endl;
    cout << "Выберите способ создания внешности:" << endl;
    cout << "1. Создать вручную" << endl;
    cout << "2. Случайная внешность" << endl;
    cout << "3. Пропустить (стандартная внешность)" << endl;
    cout << "Ваш выбор (1-3): ";
    
    int appearanceChoice;
    cin >> appearanceChoice;
    
    Appearance playerAppearance;
    
    switch(appearanceChoice) {
        case 1:
            playerAppearance = DefineAppearance();
            break;
        case 2:
            playerAppearance.Randomize();
            cout << "\n✓ Случайная внешность создана!\n";
            playerAppearance.Display();
            break;
        case 3:
            // Используется конструктор по умолчанию
            cout << "\nИспользуется стандартная внешность.\n";
            break;
        default:
            cout << "\nНеверный выбор. Используется стандартная внешность.\n";
            break;
    }
    
    // Устанавливаем внешность персонажу
    player.SetAppearance(playerAppearance);
    
    system("cls");
}

// Существующая функция распределения характеристик (оставляем как есть)
Characteristics DistributeCharacteristics()
{
    Characteristics distributedCharacteristics;
    distributedCharacteristics.PrintCharacteristics();
    
    cout << "Введите 1 для изменения характеристик (или '0' для отмены): ";	
    int userInput;
    cin >> userInput;
    
    // ... остальной код функции остается без изменений ...
    
    return distributedCharacteristics;
}
