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
    std::string menuItems[4] = {};

    int lineAmount = 0;
    std::string* lines = uiDriver.generatePlayerStatsLines(playerFighterStats, lineAmount);

    int lastMenuIndex = 0;
    int lasteMenuIndexOffset = 0;

    std::string* menuItems = new std::string[allEntities.size()];

    for (int i = 0; i < allEntities.size(); i++)
    {
        if (allEntities[i].get()->entityType == entityType::enemy)
        {
            menuItems[i] = uiDriver.getNameFromEnemy(allEntities[i].get()->entitySubType);
        }
    }

    std::string pickedMenuItem = uiDriver.drawMenu(lines, lineAmount, "Choose a Target :", menuItems, allEntities.size(), lastMenuIndex, lasteMenuIndexOffset);


    return allEntities[menuItems.in].get();
}


