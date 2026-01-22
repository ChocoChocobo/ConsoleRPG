#pragma once // Идентично
#ifndef DICE_H // Этой записи
#define DICE_H

struct Character;

int RollDice(int face);

enum Results
{
    Success = 1,
    Fail = 2,
    CriticalSuccess = 3,
    CriticalFail = 4
};

Results CheckSuccess(Character* character, int characteristicValue, int difficulty);
#endif