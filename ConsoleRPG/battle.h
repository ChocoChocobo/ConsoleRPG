#ifndef BATTLE_H
#define BATTLE_H
#include "character.h"
#include "user_interface.h"

int PlayerTurn(Character& player, Character& enemy);

int EnemyTurn(Character& enemy, Character& player);

void CheckWinLoseConditionPlayer(Character player);

void CheckWinLoseConditionEnemy(Character enemy);

class BattleContext;
class BattleState
{
public:
    ~BattleState() {}
    // Публичный метод, позволяющий переключиться на конкретное состояние
    void SetContext(BattleContext* context)
    {
        this->context = context;
    }
    // Handle-функция ответственна за возможность справиться с вызовом другой функции
    virtual void HandleChangeState() = 0;
    virtual void HandleAction() = 0;
protected:
    BattleContext* context;
};

class BattleContext
{
public:
    BattleContext(BattleState* state)
    {
        this->TransitionToState(state);
    }
    // Контекст позволяет изменять состояние объекта с помощью этой функции
    void TransitionToState(BattleState* state);
    void RequestChangeState()
    {
        this->state->HandleChangeState();
    }
    void RequestAction()
    {
        this->state->HandleAction();
    }
    ~BattleContext()
    {
        delete state;
    }
private:
    BattleState* state;
};

class PlayerTurn : public BattleState
{
public:
    void HandleChangeState() override;

    void HandleAction() override
    {

    }
};

class EnemyTurn : public BattleState
{
public:
    void HandleChangeState() override
    {
        this->context->TransitionToState(new PlayerTurn);
    }

    void HandleAction() override
    {

    }
};
#endif