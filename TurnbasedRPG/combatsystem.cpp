#include "combatsystem.h"
#include "entity.h"
#include "fightercomponent.h"
#include "InputComponent.h"
#include "component.h"
#include "uiDriver.h"
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

    player->entityType = entityType::player;

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
        enemy->entitySubType = i + 4; // HIER IST EIN KOMMIT FÜR KEANUUUUUUUUU

        _entities.push_back(std::move(enemy));
    }

    for (int i = 0; i < _entities.size(); i++)
    {
        Entity* currentEntity = _entities[i].get()->GetComponent<InputComponent>()->GetTarget();
        if (_entities[i].get()->entityType == entityType::player)
        {
            uiDriver uiDriver;
            std::cout << uiDriver.getNameFromEnemy(currentEntity->entitySubType) << std::endl;
            //HIER STEHT EIN KOMMENTAR!!!!!!!!!!!!!!!!!!!!!!!!!!! <3
            //hier auch <3 -kc
        }
    }

    //Sort by initiative
    //Query input component and ask for target using GetComponent<InputComponent>()
    //Perform combat
    //Update IsGameOver
}
