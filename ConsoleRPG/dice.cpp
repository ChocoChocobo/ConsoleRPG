#include <iostream>
#include <cstdlib>
#include "dice.h"
#include "character.h"
#include "log.h"

using namespace std;

int RollDice(int face)
{
	return rand() % face + 1;
}

Results CheckSuccess(Character* character, int characteristicValue, int difficulty)
{
    int d20Roll = RollDice(20);
    cout << "¡ÓÒÓÍ ÍÛ·ËÍ‡: " << d20Roll;
    int modificator = character->characteristics.CountModificator(characteristicValue);
    PrintConsoleMessage("ÃŒƒ»‘» ¿“Œ–: ", modificator);
    if (d20Roll == 20)
    {
        cout << " --  –»»»»»»»“»◊≈— »… ”—œ≈’ :D" << endl;
        return CriticalSuccess;
    }
    else if (d20Roll == 1)
    {
        cout << " -- ÍËËË...ÚË˜ÂÒÍËÈ ÔÓ‚‡Î... D:" << endl;
        return CriticalFail;
    }
    else if (d20Roll + modificator > difficulty)
    {
        cout << " -- ÛÒÔÂı!" << endl;
        return Success;
    }
    else
    {
        cout << " -- ÔÓ‚‡Î T_T" << endl;
        return Fail;
    }
}