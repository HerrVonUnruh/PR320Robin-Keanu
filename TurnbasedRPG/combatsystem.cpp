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
        combatManeuvers combatManeuver = _entities[i].get()->GetComponent<InputComponent>()->GetCombatManeuver();
        std::cout << static_cast<int>(combatManeuver) << std::endl;
        if (_entities[i].get()->entityType == entityType::player)
        {
            uiDriver uiDriver;
            std::cout << uiDriver.getNameFromEnemy(currentEntity->entitySubType) << std::endl;

            //HIER STEHT EIN KOMMENTAR!!!!!!!!!!!!!!!!!!!!!!!!!!! <3
            //hier auch <3 -kc
            // hier steht ein weiterer Kommentar <3 RK
        }
    }


    //FightingLocig(entitunique ptr);
    // {
    //  create new List Sort by initiative 
    // if (initiative 1 == initivative 2)
    // {
    //      pick random wer zuerst dran ist.
    // }
    // 
    // loop über die sortierte Liste und mache jedes mal das jeweilige combatshitding
    // 
    // fightercomponent getTarget 
    // fightercomponent getcombatManeuver
    // 
    // 
    // Würfeln!
    // Rechnen
    // Combat Spieler + combat WaffeSpieler + 20Seitiges Würfelergebnis
    // Combat Gegnger + combat WaffeGegner + 20Seitiges Würfelergebnis
    // 
    // if ( Angreifer int > Verteidger int)
    // {
    //  Berechne DMG
    //  Würfeln!
    // Würfel mit Würfel von Waffe
    // Ergebnis + Strength + weapon damage = potenzieller DMG
    // potenzieller DMG - Gegner Dexterity = wahrer DMG
    // Hitpoints Gegner - wahrer DMG.
    // 
    // if ( hitpoint == 0 )
    // {
    //  TOT()!
    // }
    // }
    //
    // Else
    // {
    //      block = 0DMG = Nischt!
    // }
    //
    // 
    // update();
    // 
    // 
    // 
    // }
   
    //Query input component and ask for target using GetComponent<InputComponent>()
    //Perform combat
    //Update IsGameOver
}
