#include "combatsystem.h"
#include "entity.h"
#include "fightercomponent.h"
#include "InputComponent.h"

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
        _entities.push_back(std::move(enemy));
    }
    //Sort by initiative
    //Query input component and ask for target using GetComponent<InputComponent>()
    //Perform combat
    //Update IsGameOver
}
