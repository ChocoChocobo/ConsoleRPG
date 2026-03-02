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

    void SetContext(BattleContext* context)
    {
        this->context = context;
    }

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

class PlayerTurnState : public BattleState
{
public:
    void HandleChangeState() override;

    void HandleAction() override
    {

    }
};

class EnemyTurnState : public BattleState
{
public:
    void HandleChangeState() override
    {
        this->context->TransitionToState(new PlayerTurnState);
    }

    void HandleAction() override
    {

    }
};
#endif