#include <iostream>
#include <vector>
#include "combatsystem.h"
#include "entity.h"
#include "fightercomponent.h"
#include "uiDriver.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <map>

int main()
{
    Entity combatSystemEntity;
    CombatSystem* combatSystem = combatSystemEntity.AddComponent<CombatSystem>();

    while (false&&!combatSystem->IsGameOver())
    {
        combatSystem->Update();
    }

    while (true)
    {
        system("cls");
        uiDriver uiDriver;

        int monsterIDs[] = { rand() % 11, rand() % 11, rand() % 11 , rand() % 11 };
        int bossID = rand() % 3;

        //display shit
        uiDriver.drawTopLine();

        uiDriver.displayMonster(monsterIDs, 4);
        uiDriver.displayBoss(bossID);

        FighterComponent fc;
        FighterComponent fc2;
        FighterComponent fc3;
        FighterComponent fc4;

        //fc3.fighterStats.find("Constitution")->second = 482938479;

        std::map<std::string, int> fcs[] = { fc.fighterStats, fc2.fighterStats, fc3.fighterStats, fc4.fighterStats};

        uiDriver.displayMonsterStats(fcs, 3);

        uiDriver.drawBottomLine();
        
        system("pause");
    }

    return 0;
}