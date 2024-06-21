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

    int level = 1;
    while (!combatSystem->IsGameOver())
    {
        system("cls");
        
        combatSystem->Update(level);
        level++;
        //system("pause");
    }

    while (false)
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


        int lastMenuIndex = 0;
        int lasteMenuIndexOffset = 0;
        std::string menuItems[] = { "menu item", "item menu", "dildi", "hans", "jeff", "huckleberry fin", "pipikaka" };
        std::string pickedMenuItem = uiDriver.drawMenu(lines, lineAmount, "cool menu", menuItems, 7, lastMenuIndex, lasteMenuIndexOffset);


        int x = 0;
        int y = 0;
        uiDriver.getCursorPosition(x, y);
        uiDriver.setCursorPosition(x, y + 8);
        std::cout << "picked menu item: " + pickedMenuItem << std::endl;
        system("pause");
    }

    return 0;
}