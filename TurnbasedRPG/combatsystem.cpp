#include "combatsystem.h"
#include "entity.h"
#include "fightercomponent.h"
#include "InputComponent.h"
#include "component.h"
#include <iostream>

CombatSystem::CombatSystem()
    : _player(nullptr)
{
    
}

CombatSystem::~CombatSystem()
{
}

void CombatSystem::Init()
{
    std::unique_ptr<Entity> player = std::make_unique<Entity>();
    player->AddComponent<FighterComponent>();
    InputComponent* input = player->AddComponent<PlayerInputComponent>();
    input->SetCombatSystem(this);
    _entities.push_back(std::move(player));
    _player = player.get();
};

void CombatSystem::Update()
{
    //Create enemies
    int numEnemies = 2;
    for (int i = 0; i < numEnemies; ++i)
    {
        
        std::unique_ptr<Entity> enemy = std::make_unique<Entity>();
        enemy->AddComponent<FighterComponent>();
        InputComponent* input = enemy->AddComponent<AIInputComponent>();
        input->SetCombatSystem(this);

        enemy->entityType = entityType::enemy;
        enemy->entitySubType = i + 2; // HIER IST EIN KOMMIT FÜR KEANUUUUUUUUU

        _entities.push_back(std::move(enemy));
    }

    for (int i = 0; i < _entities.size(); i++)
    {
        Entity* currentEntity = _entities[i].get()->GetComponent<InputComponent>()->GetTarget();
        std::cout << static_cast<int>(_entities[i].get()->entityType);
        std::cout << " entity is targeting: ";
        std::cout << static_cast<int>(currentEntity->entityType);
        std::cout << std::endl;
    }

    std::cout << "amount of loaded Entities: " + std::to_string(_entities.size()) << std::endl;

    //Sort by initiative
    //Query input component and ask for target using GetComponent<InputComponent>()
    //Perform combat
    //Update IsGameOver
}
