#pragma once
#include "component.h"
#include <vector>
#include <memory>

class CombatSystem : public Component
{
public:
    CombatSystem();
    virtual ~CombatSystem();
	virtual ComponentID GetID() const override { return ComponentID::CombatSystem; }
    virtual void Init() override;
    virtual void Update() override;
    bool IsGameOver() const { return false; }
    std::vector<std::unique_ptr<Entity>>& GetEntities() { return _entities; }
private:
    Entity* _player;
    std::vector<std::unique_ptr<Entity>> _entities;
};

