#include "character_creator.h"

Characteristics DistributeCharacteristics()
{
	Characteristics distributedCharacteristics;
	distributedCharacteristics.PrintCharacteristics();
	
	cout << "Введите 1 для изменения характеристик (или '0' для отмены): ";	
	int userInput;
	cin >> userInput;
	if (userInput == 1)
	{
		distributedCharacteristics.strength = 0;
		distributedCharacteristics.dexterity = 0;
		distributedCharacteristics.constitution = 0;
		distributedCharacteristics.intelligence = 0;
		distributedCharacteristics.wisdom = 0;
		distributedCharacteristics.charisma = 0;
		distributedCharacteristics.armorClass = 0;
	}

	vector<int> characteristicsArray = { 15, 14, 13, 12, 10, 8 };

	do // распределение характеристик
	{		
		cout << "Введите 1 для изменения характеристик (или '0' для отмены):" << endl;
		cin >> userInput;
		if (userInput == 1)
		{
			system("cls");
					
			distributedCharacteristics.PrintCharacteristics();

			cout << "Выберите значение для распределения: " << endl;
			for (int i = 1; i <= characteristicsArray.size(); i++)
			{
				cout << i << ". " << characteristicsArray[i-1] << endl;
			}

			int nestedUserInput;
			cin >> nestedUserInput;
			nestedUserInput--;
			if (!(0 <= nestedUserInput <= 5)) cout << "Вы ввели фигню!" << endl;

			cout << "Выберите характеристику для присовения: " << endl;
			cout << "1) Сила\n2) Ловкость\n3) Телосложение\n4) Интеллект\n5) Мудрость\n6) Харизма" << endl;

			int doubleNestedUserInput;
			cin >> doubleNestedUserInput;
			doubleNestedUserInput--;

			switch (doubleNestedUserInput)
			{
			case 0:
				if (distributedCharacteristics.strength != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.strength);
					distributedCharacteristics.strength = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else
				{
					distributedCharacteristics.strength = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				break;
			case 1:
				if (distributedCharacteristics.dexterity != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.dexterity);
					distributedCharacteristics.dexterity = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else
				{
					distributedCharacteristics.dexterity = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}

				distributedCharacteristics.armorClass = int((distributedCharacteristics.dexterity -10) / 2 + 10);
				break;
			case 2:
				if (distributedCharacteristics.constitution != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.constitution);
					distributedCharacteristics.constitution = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else
				{
					distributedCharacteristics.constitution = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}				
				break;
			case 3:
				if (distributedCharacteristics.intelligence != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.intelligence);
					distributedCharacteristics.intelligence = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else
				{
					distributedCharacteristics.intelligence = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				break;
			case 4:
				if (distributedCharacteristics.wisdom != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.wisdom);
					distributedCharacteristics.wisdom = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else 
				{
					distributedCharacteristics.wisdom = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				break;
			case 5:
				if (distributedCharacteristics.charisma != 0)
				{
					characteristicsArray.push_back(distributedCharacteristics.charisma);
					distributedCharacteristics.charisma = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}
				else
				{
					distributedCharacteristics.charisma = characteristicsArray[nestedUserInput];
					characteristicsArray.erase(characteristicsArray.begin() + nestedUserInput);
				}				
				break;
			default:
				cout << "Вы ввели фигню!" << endl;
				break;
			}

			if (characteristicsArray.empty()) break;
		}
		else if (userInput == 0) continue;
		else cout << "Введено неверное значение!" << endl;
	} while (userInput != 0);

	return distributedCharacteristics;
}

//Appearance DefineAppearance()
//{
//	Appearance definedAppearance();
//	return definedAppearance;
//}