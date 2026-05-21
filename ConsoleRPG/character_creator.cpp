#include "character_creator.h"
#include <iostream>
#include <limits>
using namespace std;

void CreateCharacter(Character& player)
{
	cout << "Создание персонажа\n";

	cout << "Введите имя персонажа: ";
	cin.ignore(1000, '\n');
	getline(cin, player.name);

	// Выбор внешности
	player.appearance = DefineAppearance();
	
	// Распределение характеристик
	player.characteristics = DistributeCharacteristics();

	system("cls");
	cout << "Персонаж успешно создан!" << endl;
	player.PrintFullInfo();
}

Appearance DefineAppearance()
{
	Appearance newAppearance;
	int choice;

	cout << "\n=== Настройка внешности персонажа ===\n";

	// Выбор цвета кожи
	cout << "\nВыберите цвет кожи:\n";
	cout << "1. Светлая\n";
	cout << "2. Смуглая\n";
	cout << "3. Темная\n";
	cout << "4. Оливковая\n";
	cout << "5. Бледная\n";
	cout << "6. Загорелая\n";
	cout << "> ";
	cin >> choice;

	switch (choice)
	{
	case 1: newAppearance.skinColor = "светлая"; break;
	case 2: newAppearance.skinColor = "смуглая"; break;
	case 3: newAppearance.skinColor = "темная"; break;
	case 4: newAppearance.skinColor = "оливковая"; break;
	case 5: newAppearance.skinColor = "бледная"; break;
	case 6: newAppearance.skinColor = "загорелая"; break;
	default: newAppearance.skinColor = "светлая"; cout << "Выбран вариант по умолчанию.\n"; break;
	}

	// Выбор цвета волос
	cout << "\nВыберите цвет волос:\n";
	cout << "1. Русые\n";
	cout << "2. Шатены\n";
	cout << "3. Блондинистые\n";
	cout << "4. Рыжие\n";
	cout << "5. Черные\n";
	cout << "6. Седые\n";
	cout << "7. Каштановые\n";
	cout << "> ";
	cin >> choice;

	switch (choice)
	{
	case 1: newAppearance.hairColor = "русые"; break;
	case 2: newAppearance.hairColor = "шатены"; break;
	case 3: newAppearance.hairColor = "блондинистые"; break;
	case 4: newAppearance.hairColor = "рыжие"; break;
	case 5: newAppearance.hairColor = "черные"; break;
	case 6: newAppearance.hairColor = "седые"; break;
	case 7: newAppearance.hairColor = "каштановые"; break;
	default: newAppearance.hairColor = "русые"; cout << "Выбран вариант по умолчанию.\n"; break;
	}

	// Выбор цвета глаз
	cout << "\nВыберите цвет глаз:\n";
	cout << "1. Голубые\n";
	cout << "2. Зеленые\n";
	cout << "3. Карие\n";
	cout << "4. Серые\n";
	cout << "5. Янтарные\n";
	cout << "6. Фиолетовые\n";
	cout << "7. Синие\n";
	cout << "> ";
	cin >> choice;

	switch (choice)
	{
	case 1: newAppearance.eyeColor = "голубые"; break;
	case 2: newAppearance.eyeColor = "зеленые"; break;
	case 3: newAppearance.eyeColor = "карие"; break;
	case 4: newAppearance.eyeColor = "серые"; break;
	case 5: newAppearance.eyeColor = "янтарные"; break;
	case 6: newAppearance.eyeColor = "фиолетовые"; break;
	case 7: newAppearance.eyeColor = "синие"; break;
	default: newAppearance.eyeColor = "голубые"; cout << "Выбран вариант по умолчанию.\n"; break;
	}

	// Выбор роста
	cout << "\nВыберите рост:\n";
	cout << "1. Низкий (140-160 см)\n";
	cout << "2. Средний (160-175 см)\n";
	cout << "3. Высокий (175-190 см)\n";
	cout << "4. Очень высокий (190-210 см)\n";
	cout << "5. Гигантский (210+ см)\n";
	cout << "> ";
	cin >> choice;

	switch (choice)
	{
	case 1: newAppearance.height = "низкий"; break;
	case 2: newAppearance.height = "средний"; break;
	case 3: newAppearance.height = "высокий"; break;
	case 4: newAppearance.height = "очень высокий"; break;
	case 5: newAppearance.height = "гигантский"; break;
	default: newAppearance.height = "средний"; cout << "Выбран вариант по умолчанию.\n"; break;
	}

	// Выбор телосложения
	cout << "\nВыберите телосложение:\n";
	cout << "1. Худое\n";
	cout << "2. Атлетичное\n";
	cout << "3. Мускулистое\n";
	cout << "4. Коренастое\n";
	cout << "5. Полное\n";
	cout << "6. Сутулое\n";
	cout << "> ";
	cin >> choice;

	switch (choice)
	{
	case 1: newAppearance.bodyType = "худое"; break;
	case 2: newAppearance.bodyType = "атлетичное"; break;
	case 3: newAppearance.bodyType = "мускулистое"; break;
	case 4: newAppearance.bodyType = "коренастое"; break;
	case 5: newAppearance.bodyType = "полное"; break;
	case 6: newAppearance.bodyType = "сутулое"; break;
	default: newAppearance.bodyType = "атлетичное"; cout << "Выбран вариант по умолчанию.\n"; break;
	}

	cout << "\n=== Внешность настроена! ===\n";
	newAppearance.PrintAppearance();
	
	return newAppearance;
}

Characteristics DistributeCharacteristics()
{
	Characteristics distributedCharacteristics;
	
	cout << "\n=== Распределение характеристик ===\n";
	cout << "У вас есть следующие значения характеристик: 15, 14, 13, 12, 10, 8\n";
	cout << "Распределите их по шести параметрам.\n\n";
	
	distributedCharacteristics.PrintCharacteristics();
	
	cout << "\nНажмите 1 для распределения характеристик (или '0' для пропуска): ";	
	int userInput;
	cin >> userInput;
	
	if (userInput == 0)
	{
		cout << "Характеристики остались стандартными.\n";
		return distributedCharacteristics;
	}
	
	// Обнуляем характеристики для распределения
	distributedCharacteristics.strength = 0;
	distributedCharacteristics.dexterity = 0;
	distributedCharacteristics.constitution = 0;
	distributedCharacteristics.intelligence = 0;
	distributedCharacteristics.wisdom = 0;
	distributedCharacteristics.charisma = 0;

	vector<int> characteristicsArray = { 15, 14, 13, 12, 10, 8 };

	do // Распределение характеристик
	{		
		cout << "\nОсталось распределить значений: " << characteristicsArray.size() << endl;
		cout << "Доступные значения: ";
		for (int i = 0; i < characteristicsArray.size(); i++)
		{
			cout << characteristicsArray[i];
			if (i < characteristicsArray.size() - 1) cout << ", ";
		}
		cout << endl;
		
		cout << "\nНажмите 1 для распределения характеристики (или '0' для выхода):" << endl;
		cin >> userInput;
		
		if (userInput == 1)
		{
			system("cls");
					
			cout << "\n=== Текущие характеристики ===\n";
			cout << "Сила: " << (distributedCharacteristics.strength ? to_string(distributedCharacteristics.strength) : "не распределено") << endl;
			cout << "Ловкость: " << (distributedCharacteristics.dexterity ? to_string(distributedCharacteristics.dexterity) : "не распределено") << endl;
			cout << "Телосложение: " << (distributedCharacteristics.constitution ? to_string(distributedCharacteristics.constitution) : "не распределено") << endl;
			cout << "Интеллект: " << (distributedCharacteristics.intelligence ? to_string(distributedCharacteristics.intelligence) : "не распределено") << endl;
			cout << "Мудрость: " << (distributedCharacteristics.wisdom ? to_string(distributedCharacteristics.wisdom) : "не распределено") << endl;
			cout << "Харизма: " << (distributedCharacteristics.charisma ? to_string(distributedCharacteristics.charisma) : "не распределено") << endl;
			cout << "Класс брони: " << distributedCharacteristics.armorClass << endl;

			cout << "\nВыберите значение для распределения: " << endl;
			for (int i = 1; i <= characteristicsArray.size(); i++)
			{
				cout << i << ". " << characteristicsArray[i-1] << endl;
			}
			cout << "> ";
			
			int nestedUserInput;
			cin >> nestedUserInput;
			nestedUserInput--;
			
			if (nestedUserInput < 0 || nestedUserInput >= characteristicsArray.size()) 
			{
				cout << "Неверный выбор!" << endl;
				continue;
			}

			cout << "\nВыберите характеристику для назначения: " << endl;
			cout << "1) Сила\n";
			cout << "2) Ловкость\n";
			cout << "3) Телосложение\n";
			cout << "4) Интеллект\n";
			cout << "5) Мудрость\n";
			cout << "6) Харизма\n";
			cout << "> ";

			int doubleNestedUserInput;
			cin >> doubleNestedUserInput;
			doubleNestedUserInput--;

			if (doubleNestedUserInput < 0 || doubleNestedUserInput > 5)
			{
				cout << "Неверный выбор!" << endl;
				continue;
			}

			int selectedValue = characteristicsArray[nestedUserInput];
			
			switch (doubleNestedUserInput)
			{
			case 0: // Сила
				if (distributedCharacteristics.strength != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.strength);
					distributedCharacteristics.strength = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else
				{
					distributedCharacteristics.strength = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				cout << "Сила установлена на " << selectedValue << endl;
				break;
				
			case 1: // Ловкость
				if (distributedCharacteristics.dexterity != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.dexterity);
					distributedCharacteristics.dexterity = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else
				{
					distributedCharacteristics.dexterity = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				// Пересчет класса брони на основе ловкости
				distributedCharacteristics.armorClass = 10 + int((distributedCharacteristics.dexterity - 10) / 2);
				cout << "Ловкость установлена на " << selectedValue << endl;
				cout << "Класс брони пересчитан: " << distributedCharacteristics.armorClass << endl;
				break;
				
			case 2: // Телосложение
				if (distributedCharacteristics.constitution != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.constitution);
					distributedCharacteristics.constitution = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else
				{
					distributedCharacteristics.constitution = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				cout << "Телосложение установлено на " << selectedValue << endl;
				break;
				
			case 3: // Интеллект
				if (distributedCharacteristics.intelligence != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.intelligence);
					distributedCharacteristics.intelligence = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else
				{
					distributedCharacteristics.intelligence = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				cout << "Интеллект установлен на " << selectedValue << endl;
				break;
				
			case 4: // Мудрость
				if (distributedCharacteristics.wisdom != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.wisdom);
					distributedCharacteristics.wisdom = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else 
				{
					distributedCharacteristics.wisdom = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				cout << "Мудрость установлена на " << selectedValue << endl;
				break;
				
			case 5: // Харизма
				if (distributedCharacteristics.charisma != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.charisma);
					distributedCharacteristics.charisma = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else
				{
					distributedCharacteristics.charisma = selectedValue;
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				cout << "Харизма установлена на " << selectedValue << endl;
				break;
				
			default:
				cout << "Неверный выбор!" << endl;
				break;
			}
			
			cout << "\nНажмите Enter для продолжения...";
			cin.ignore();
			cin.get();
			system("cls");

			if (characteristicsArray.empty()) 
			{
				cout << "\n=== Все характеристики распределены! ===\n";
				break;
			}
		}
		else if (userInput == 0) 
		{
			cout << "Распределение характеристик завершено.\n";
			break;
		}
		else 
		{
			cout << "Введите корректное значение!" << endl;
		}
	} while (userInput != 0);

	cout << "\n=== Итоговые характеристики ===\n";
	distributedCharacteristics.PrintCharacteristics();
	
	return distributedCharacteristics;
}
