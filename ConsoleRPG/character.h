#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>
#include "item.h"
#include "dice.h"
#include "user_interface.h"

using namespace std;

// ================= CHARACTERISTICS =================

struct Characteristics {
    int strength;
    int dexterity;
    int constitution;
    int wisdom;
    int intelligence;
    int charisma;
    int armorClass;

    Characteristics();
    Characteristics(int _strength, int _dexterity, int _constitution,
        int _wisdom, int _intelligence,
        int _charisma, int _armorClass);

    int CountModificator(int characteristic);
    void PrintCharacteristics();
};

// ================= VISUAL =================

struct VisualsASCII {
    void ShowSprite() {}
};

struct Appearance {
    string skinColor;
    string hairColor;
};

// ================= FORWARD DECLARATIONS =================

class CharacterContext;
class CharacterState;

// ================= CHARACTER =================

struct Character {

    string name;
    Appearance appearance;

    int health;
    int maxHealth;
    int healthFlasks;
    int damageFace;
    int specialCooldown;
    int gold;

    vector<Item> inventory;
    Characteristics characteristics;

    int uniqueAbilityDifficulty;
    bool minionSpawned = false;
    Character* minion = nullptr;

    VisualsASCII visualsASCII;

    // --- State context ---
    CharacterContext* stateContext;

    Character();
    Character(string _name, int _health, int _damageFace,
        int _specialCooldown, int _startGold,
        Character& _minion, int _uniqueAbilityDifficulty);
    Character(string _name, int _health, int _damageFace,
        int _specialCooldown, int _startGold);

    ~Character();

    // --- Service ---
    void PrintStatus();
    void RemoveGold(int amount);
    void AddGold(int amount);
    bool BuyItem(int cost);
    void IncreaseHealth(int amount);
    void DecreaseHealth(int amount);
    bool CheckFleeSuccess(int difficulty);

    // --- State-based actions ---
    void BasicAttack(Character& other);
    void SpecialAttack();
    void ShowInventory();
    void Heal(int difficulty);
    bool Flee(Character& other);
};

// ================= STATE PATTERN =================

class CharacterState {
public:
    virtual ~CharacterState() {}
    void SetContext(CharacterContext* context) {
        this->context = context;
    }

    virtual void HandleChangeState() {}
    virtual void HandleAction(Character* target = nullptr) = 0;

protected:
    CharacterContext* context;
};

class CharacterContext {
public:
    CharacterContext(Character* owner, CharacterState* state);
    ~CharacterContext();

    void TransitionToState(CharacterState* state);

    void RequestAction(Character* target = nullptr) {
        state->HandleAction(target);
    }

    Character* GetOwner() {
        return owner;
    }

private:
    CharacterState* state;
    Character* owner;
};

// ================= CONCRETE STATES =================

class BasicAttackState : public CharacterState {
public:
    void HandleAction(Character* target) override;
};

class SpecialAttackState : public CharacterState {
public:
    void HandleAction(Character* target) override;
};

class HealState : public CharacterState {
public:
    void HandleAction(Character* target) override;
};

class InventoryState : public CharacterState {
public:
    void HandleAction(Character* target) override;
};

class FleeState : public CharacterState {
public:
    void HandleAction(Character* target) override;
};

#endif