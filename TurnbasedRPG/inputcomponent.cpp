#include "InputComponent.h"
#include <iostream>
#include "uiDriver.h"
#include "fighterComponent.h"

InputComponent::InputComponent()
    : _combatSystem(nullptr)
{

}

InputComponent::~InputComponent()
{

}

PlayerInputComponent::~PlayerInputComponent()
{

}

AIInputComponent::~AIInputComponent()
{

}

Entity* AIInputComponent::GetTarget() const
{
    std::vector<std::unique_ptr<Entity>>& allEntities = const_cast<CombatSystem*>(_combatSystem)->GetEntities();

    for (int i = 0; i < allEntities.size(); ++i)
    {
        if (allEntities[i]->entityType == entityType::player)
        {
            return allEntities[i].get();
        }
    }

    return nullptr;
}

Entity* PlayerInputComponent::GetTarget() const
{
    std::vector<std::unique_ptr<Entity>>& allEntities = const_cast<CombatSystem*>(_combatSystem)->GetEntities();

    std::map<std::string, int> playerFighterStats = this->GetOwner().GetComponent<FighterComponent>()->fighterStats;
    uiDriver uiDriver;

    int lineAmount = 0;
    std::string* lines = uiDriver.generatePlayerStatsLines(playerFighterStats, lineAmount);

    int lastMenuIndex = 0;
    int lasteMenuIndexOffset = 0;


    std::map<std::string, Entity*> nameEntityMap;

    for (int i = 0; i < allEntities.size(); i++)
    {
        if (allEntities[i]->entityType == entityType::enemy)
        {
            nameEntityMap[uiDriver.getNameFromEnemy(allEntities[i]->entitySubType)] = allEntities[i].get();
        }
    }

    std::string* menuItems = new std::string[nameEntityMap.size()];

    int index = 0;
    for (auto it = nameEntityMap.begin(); it != nameEntityMap.end(); ++it) 
    {
        const std::string& key = it->first;
        const Entity* entityPtr = it->second;

        menuItems[index] = key;
        ++index;
    }

    std::string pickedMenuItem = uiDriver.drawMenu(lines, lineAmount, "Choose a Target :", menuItems, nameEntityMap.size(), lastMenuIndex, lasteMenuIndexOffset);

    return nameEntityMap.at(pickedMenuItem);
}
