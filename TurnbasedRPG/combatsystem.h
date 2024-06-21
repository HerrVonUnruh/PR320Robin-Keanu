#pragma once
#include "component.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include "entity.h"
#include "fighterComponent.h"

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

    void calculateAndApplyDamage(Entity *entity, Entity *forcedTargetEnity = NULL, bool forceTargetEnemy = false, bool doDoubleDamag = false);
    
    void sortEntitiesByStat(std::vector<std::unique_ptr<Entity>>& entities, const std::string& stat) {
        std::sort(entities.begin(), entities.end(), [&stat](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) {
            return a->GetComponent<FighterComponent>()->fighterStats.at(stat) >
                b->GetComponent<FighterComponent>()->fighterStats.at(stat);
            });
    }

private:
    Entity* _player;
    std::vector<std::unique_ptr<Entity>> _entities;


    
    // FightingLocig(entitunique ptr);
};

