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


        uiDriver.drawTopLine();

        uiDriver.displayMonster(monsterIDs, 4);
        //uiDriver.displayBoss(bossID);

        FighterComponent fc;
        FighterComponent fc2;
        FighterComponent fc3;
        FighterComponent fc4;
        std::map<std::string, int> fcs[] = { fc.fighterStats, fc2.fighterStats, fc3.fighterStats, fc4.fighterStats};
        uiDriver.displayMonsterStats(fcs, 4);

        uiDriver.drawCenterLine();


        int lineAmount = 0;
        std::string* lines = uiDriver.generatePlayerStatsLines(fc.fighterStats, lineAmount);

        std::string menuItems[] = { "menu item", "item menu" };
        uiDriver.drawMenu(lines, lineAmount, "cool menu", menuItems, 2);
    }

    return 0;
}