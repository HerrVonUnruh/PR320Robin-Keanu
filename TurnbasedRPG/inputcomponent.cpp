#include "InputComponent.h"

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


