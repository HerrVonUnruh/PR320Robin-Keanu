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
        enemy->entitySubType = i + 4; // HIER IST EIN KOMMIT F�R KEANUUUUUUUUU

        enemyFighterComponent->fighterStats = enemyFighterComponent->defaultMonsterFighterStats[i + 4];
        enemyFighterComponent->currentweapon = enemyFighterComponent->presetWeapons[0];

        _entities.push_back(std::move(enemy));
    }

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
    // loop �ber die sortierte Liste und mache jedes mal das jeweilige combatshitding
    // 
    // fightercomponent getTarget 
    // fightercomponent getcombatManeuver
    // 
    // 
    // W�rfeln!
    // Rechnen
    // Combat Spieler + combat WaffeSpieler + 20Seitiges W�rfelergebnis
    // Combat Gegnger + combat WaffeGegner + 20Seitiges W�rfelergebnis
    // 
    // if ( Angreifer int > Verteidger int)
    // {
    //  Berechne DMG
    //  W�rfeln!
    // W�rfel mit W�rfel von Waffe
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

void CombatSystem::calculateAndApplyDamage(Entity* entityAttacker)
{
    InputComponent *inputComponentAttacker = entityAttacker->GetComponent<InputComponent>();

    Entity *entityDefender = inputComponentAttacker->GetTarget();

    FighterComponent *attackerFighterComponent = entityAttacker->GetComponent<FighterComponent>();
    FighterComponent *defenderFighterComponent = entityDefender->GetComponent<FighterComponent>();

    int weaponDiceRoll = ((rand() % 5) + 1) * attackerFighterComponent->currentweapon.d6Amount;
    int attackerStrenght = attackerFighterComponent->fighterStats.at("3_show_Strength");
    int weaponDamage = attackerFighterComponent->currentweapon.damage;
    int defenderDexterity = defenderFighterComponent->fighterStats.at("4_show_Dexterity");

    int potentialDamage = weaponDiceRoll + attackerStrenght + weaponDamage;
    int totalDamage = potentialDamage - defenderDexterity;
    std::cout << "damage done:" + std::to_string(totalDamage) << std::endl;
    std::cout << "before attack life:" + std::to_string(defenderFighterComponent->fighterStats.at("1_show_Hitpoints")) << std::endl;

    defenderFighterComponent->fighterStats.at("1_show_Hitpoints") = defenderFighterComponent->fighterStats.at("1_show_Hitpoints") - totalDamage;

    std::cout << "after attack life:" + std::to_string(defenderFighterComponent->fighterStats.at("1_show_Hitpoints")) << std::endl;
};
