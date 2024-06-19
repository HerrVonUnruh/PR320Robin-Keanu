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

Entity* AIInputComponent::GetTarget()
{
    std::vector<std::unique_ptr<Entity>> allEntitys = AIInputComponent::_combatSystem->GetEntities();
    
    for (int i = 0; i < allEntitys.size(); i++)
    {
        Entity* currentEntity = allEntitys[i].get();

        if (currentEntity->entityType == entityType::player)
        {
            return currentEntity;
        }
    }

    return nullptr;
}
