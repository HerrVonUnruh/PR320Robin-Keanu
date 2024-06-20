#pragma once
#include <memory>
#include <vector>

#include "entity.h"
#include "combatsystem.h"
#include "component.h"

class InputComponent : public Component
{
public:
    InputComponent();
    virtual ~InputComponent();
	virtual ComponentID GetID() const override { return ComponentID::Input;}
    void SetCombatSystem(const CombatSystem* combatSystem) { _combatSystem = combatSystem; }
    virtual Entity* GetTarget() const = 0;
protected:
    const CombatSystem* _combatSystem;
};

class PlayerInputComponent : public InputComponent
{
public:
    virtual ~PlayerInputComponent();
    Entity* GetTarget() const override;// { return nullptr; } //query entities from m_CombatSystem
};

class AIInputComponent : public InputComponent
{
public:
    virtual ~AIInputComponent();
    Entity* GetTarget() const override;// const override { return nullptr; } //query entities from m_CombatSystem
};

