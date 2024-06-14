#include "uiDriver.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iterator>

void uiDriver::displayMonster(int monsterIDs[], int monsterAmount)
{
    int maxMonsterAmount = (sizeof(monsterGrafix) / sizeof(monsterGrafix[0]));
    int maxLinesPerMonster = (sizeof(monsterGrafix[0]) / sizeof(monsterGrafix[0][0]));

    int firstMonster = 0;
    int secondMonster = 0;
    int thirdMonster = 0;
    int fourthMonster = 0;

    for (int i = 0; i < monsterAmount; i++)
    {
        switch (i)
        {
        case 0:
            firstMonster = monsterIDs[i];
            break;

        case 1:
            secondMonster = monsterIDs[i];
            break;

        case 2:
            thirdMonster = monsterIDs[i];
            break;

        case 3:
            fourthMonster = monsterIDs[i];
            break;

        default:
            std::cout << "wrong index in monster grafix assignment step" << std::endl;
            abort();
            break;
        }
    }

    std::string* lines = new std::string[maxLinesPerMonster];

    for (int i = 0; i < maxLinesPerMonster; i++)
    {
        lines[i] += monsterGrafix[firstMonster][i];
        lines[i] += monsterGrafix[secondMonster][i];
        lines[i] += monsterGrafix[thirdMonster][i];
        lines[i] += monsterGrafix[fourthMonster][i];

        lines[i] += "|";
    }

    for (int i = 0; i < maxLinesPerMonster; i++)
    {
        std::cout << lines[i] << std::endl;
    }
}

void uiDriver::displayMonsterStats(std::map<std::string, int> fighterStats[], int fighterStatsAmount)
{
    int maxLinesPerStats = (sizeof(fighterStats[0]) / sizeof(fighterStats[0][0]));

    std::string* lines = new std::string[maxLinesPerStats];

    for (int i = 0; i < fighterStatsAmount; i++)
    {
        for (int j = 0; j < maxLinesPerStats; j++)
        {
            auto currentElement = fighterStats[i].begin();
            std::advance(currentElement, j);

            lines[j] += "|" + currentElement->first + ": " + std::to_string(currentElement->second);

            lines[j].resize(26 * (i + 1), ' ');
        }
    }

    for (int i = 0; i < maxLinesPerStats; i++)
    {
        std::cout << lines[i] + "|" << std::endl;
    }
}

void uiDriver::displayBoss(int bossID)
{
    int maxBossAmount = (sizeof(bossGrafix) / sizeof(bossGrafix[0]));
    int maxLinesPerBoss = (sizeof(bossGrafix[0]) / sizeof(bossGrafix[0][0]));

    int boss = bossID;

    std::string* lines = new std::string[maxLinesPerBoss];

    for (int i = 0; i < maxLinesPerBoss; i++)
    {
        lines[i] += bossGrafix[boss][i];

        lines[i] += "|";
    }

    for (int i = 0; i < maxLinesPerBoss; i++)
    {
        std::cout << lines[i] << std::endl;
    }
}

void uiDriver::drawTopLine()
{
    std::cout << uiDriver::topLine << std::endl;
}

void uiDriver::drawBottomLine()
{
    std::cout << uiDriver::bottomLine << std::endl;
}