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
    FighterComponent* playerFighterComponent = player->AddComponent<FighterComponent>();
    InputComponent* input = player->AddComponent<PlayerInputComponent>();
    input->SetCombatSystem(this);

    player->entityType = entityType::player;

    playerFighterComponent->fighterStats = playerFighterComponent->defaultPlayerFighterStats;
    playerFighterComponent->currentweapon = playerFighterComponent->presetWeapons[2];

    _entities.push_back(std::move(player));
    _player = player.get();
};

void CombatSystem::Update()
{
    uiDriver uiDriver;
    //Create enemies
    int numEnemies = 2;
    for (int i = 0; i < numEnemies; ++i)
    {
        
        std::unique_ptr<Entity> enemy = std::make_unique<Entity>();
        FighterComponent *enemyFighterComponent = enemy->AddComponent<FighterComponent>();
        InputComponent* input = enemy->AddComponent<AIInputComponent>();
        input->SetCombatSystem(this);

        enemy->entityType = entityType::enemy;
        enemy->entitySubType = i + 5; // HIER IST EIN KOMMIT FÜR KEANUUUUUUUUU

        enemyFighterComponent->fighterStats = enemyFighterComponent->defaultMonsterFighterStats[i + 4];
        enemyFighterComponent->currentweapon = enemyFighterComponent->presetWeapons[0];

        _entities.push_back(std::move(enemy));
    }

    sortEntitiesByStat(_entities, "5_show_Initiative");

    uiDriver.drawTopLine();
    //uiDriver.displayMonster( ,numEnemies);

    //std::map<std::string, int> fcs[] = {  }
    //uiDriver.displayMonsterStats();
    for (int i = 0; i < _entities.size(); i++)
    {
        Entity* currentEntity = _entities[i].get();//->GetComponent<InputComponent>()->GetTarget();
        //combatManeuvers combatManeuver = _entities[i].get()->GetComponent<InputComponent>()->GetCombatManeuver();

        calculateAndApplyDamage(currentEntity);
        
        /*std::cout << static_cast<int>(combatManeuver) << std::endl;
        if (_entities[i].get()->entityType == entityType::player)
        {
            std::cout << uiDriver.getNameFromEnemy(currentEntity->entitySubType) << std::endl;

            //HIER STEHT EIN KOMMENTAR!!!!!!!!!!!!!!!!!!!!!!!!!!! <3
            //hier auch <3 -kc
            // hier steht ein weiterer Kommentar <3 RK
        }*/
    }

    for (int i = 0; i < _entities.size(); i++)
    {
        Entity* currentEntity = _entities[i].get();

        if (_entities[i].get()->entityType == entityType::player)
        {
            std::cout << "der player pos: " + std::to_string(i) << std::endl;
        
            std::cout << "der player lebt so: " + std::to_string(currentEntity->GetComponent<FighterComponent>()->fighterStats.at("1_show_Hitpoints")) << std::endl;
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
    // combat menuver picken
    // Würfeln!
    // Rechnen
    // Combat Spieler + combat WaffeSpieler + 20Seitiges Würfelergebnis
    // Combat Gegnger + combat WaffeGegner + 20Seitiges Würfelergebnis
    // 
    // if ( Angreifer int - 8 powerstrike shit > Verteidger int)
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

void CombatSystem::calculateAndApplyDamage(Entity* entityAttacker, Entity* forcedTargetEnity, bool forceTargetEnemy, bool doDoubleDamage)
{
    InputComponent *inputComponentAttacker = entityAttacker->GetComponent<InputComponent>();

    Entity* entityDefender;

    if (!forcedTargetEnity)
    {
        entityDefender = inputComponentAttacker->GetTarget();
    }
    else
    {
        entityDefender = forcedTargetEnity;
    }

    FighterComponent *attackerFighterComponent = entityAttacker->GetComponent<FighterComponent>();
    FighterComponent *defenderFighterComponent = entityDefender->GetComponent<FighterComponent>();

    int weaponDiceRoll = 0;
        
    for (int i = 0; i < attackerFighterComponent->currentweapon.d6Amount; i++)
    {
         weaponDiceRoll += (rand() % 5) + 1;
    }

    int attackerStrenght = attackerFighterComponent->fighterStats.at("3_show_Strength");
    int weaponDamage = attackerFighterComponent->currentweapon.damage;
    int defenderDexterity = defenderFighterComponent->fighterStats.at("4_show_Dexterity");

    int potentialDamage = weaponDiceRoll + attackerStrenght + weaponDamage;
    int totalDamage = potentialDamage - defenderDexterity;
    
    if (totalDamage <= 0)
    {
        totalDamage = 0;
    }


    if (doDoubleDamage)
    {
        totalDamage = totalDamage * 2;
    }

    std::cout << "                                                                              damage done:" + std::to_string(totalDamage) << std::endl;
    std::cout << "                                                                              before attack life:" + std::to_string(defenderFighterComponent->fighterStats.at("1_show_Hitpoints")) << std::endl;

    defenderFighterComponent->fighterStats.at("1_show_Hitpoints") = defenderFighterComponent->fighterStats.at("1_show_Hitpoints") - totalDamage;

    std::cout << "                                                                              after attack life:" + std::to_string(defenderFighterComponent->fighterStats.at("1_show_Hitpoints")) << std::endl;
};
