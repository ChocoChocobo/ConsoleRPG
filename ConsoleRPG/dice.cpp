#include <iostream>
#include <cstdlib>
#include "dice.h"
#include "character.h"

using namespace std;

int RollDice(int face)
{
	return rand() % face + 1;
}

Results CheckSuccess(Character* character, int characteristicValue, int difficulty)
{
    int d20Roll = RollDice(20);
    cout << "Áðîñîê êóáèêà: " << d20Roll;
    if (d20Roll == 20)
    {
        cout << " -- ÊÐÈÈÈÈÈÈÈÒÈ×ÅÑÊÈÉ ÓÑÏÅÕ :D" << endl;
        return CriticalSuccess;
    }
    else if (d20Roll == 1)
    {
        cout << " -- êðèèè...òè÷åñêèé ïðîâàë... D:" << endl;
        return CriticalFail;
    }
    else if (d20Roll + character->characteristics.CountModificator(characteristicValue) > difficulty)
    {
        cout << " -- óñïåõ!" << endl;
        return Success;
    }
    else
    {
        cout << " -- ïðîâàë T_T" << endl;
        return Fail;
    }
}