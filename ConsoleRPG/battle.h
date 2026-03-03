#ifndef BATTLE_H
#define BATTLE_H
#include "character.h"
#include "user_interface.h"

void CheckWinLoseConditionPlayer(Character player);
void CheckWinLoseConditionEnemy(Character enemy);

enum BattleStates
{
    PlayerTurnEnum = 0,
    EnemyTurnEnum = 1
};

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
    virtual int HandleAction(Character& player, Character& enemy) = 0;
protected:
    BattleContext* context;
};

class BattleContext
{
public:
    BattleContext(BattleState* state)
    {
        battleState = PlayerTurnEnum;
        this->TransitionToState(state);
    }
    
    void TransitionToState(BattleState* state);
    void RequestChangeState()
    {
        this->state->HandleChangeState();
    }
    int RequestAction(Character& player, Character& enemy)
    {
        return this->state->HandleAction(player, enemy);
    }
    void SetBattleStateEnum(BattleStates state)
    {
        battleState = state;
    }
    BattleStates GetBattleState()
    {
        return battleState;
    }
    ~BattleContext()
    {
        delete state;
    }
private:
    BattleState* state;
    BattleStates battleState;
};

class PlayerTurnState : public BattleState
{
public:
    void HandleChangeState() override;
    int HandleAction(Character& player, Character& enemy) override;
};

class EnemyTurnState : public BattleState
{
public:
    void HandleChangeState() override;
    int HandleAction(Character& player, Character& enemy) override;
};
#endif