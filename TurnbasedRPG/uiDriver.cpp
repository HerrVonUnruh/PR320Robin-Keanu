#include "uiDriver.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iterator>
#include <conio.h>
#include <iostream>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

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
    int maxLinesPerStats = fighterStats[0].size();

    std::string* lines = new std::string[maxLinesPerStats];

    for (int i = 0; i < fighterStatsAmount; i++)
    {
        for (int j = 0; j < maxLinesPerStats; j++)
        {
            auto currentElement = fighterStats[i].begin();
            std::advance(currentElement, j);

            if (currentElement->first.substr(2, 4) == "show")
            {
                std::string stringToDisplay = currentElement->first.substr(7, currentElement->first.size());

                lines[j] += "|" + stringToDisplay + ": " + std::to_string(currentElement->second);
            }
            else
            {
                lines[j] += "|";
            }

            lines[j].resize(charactersPerStatField * (i + 1), ' ');
        }
    }

    for (int i = 0; i < maxLinesPerStats; i++)
    {
        while (lines[i].size() < charactersPerStatField * 4)
        {
            lines[i] += "|" + std::string(charactersPerStatField - 1, ' ');
        }

        std::cout << lines[i] + "|" << std::endl;
    }
}


std::string* uiDriver::generatePlayerStatsLines(std::map<std::string, int> fighterStats, int& arraySize)
{
    int maxLinesPerStats = fighterStats.size();

    std::string* lines = new std::string[maxLinesPerStats];

    for (int j = 0; j < maxLinesPerStats; j++)
    {
        auto currentElement = fighterStats.begin();
        std::advance(currentElement, j);

        if (currentElement->first.substr(2, 4) == "show")
        {
            std::string stringToDisplay = currentElement->first.substr(7, currentElement->first.size());

            lines[j] += "|" + stringToDisplay + ": " + std::to_string(currentElement->second);
        }
        else
        {
            lines[j] += "|";
        }

        lines[j].resize(characterAmountForPlayerStats, ' ');

        lines[j].replace(characterAmountForPlayerStats - playerGrafix[0].size(), playerGrafix[0].size(), playerGrafix[j]);

        arraySize++;
    }

    return lines;
}

std::string uiDriver::drawMenu(std::string* playerStatLines, int lineAmount, std::string tagLine, std::string menuItems[], int menuItemCount)
{
    int inputKeycode = 0;

    playerStatLines[0] += "|" + tagLine;

    for (int i = 0; i < lineAmount; i++)
    {
        if (i != 0)
        {
            playerStatLines[i] += "|";
        }

        playerStatLines[i].resize(characterAmountForPlayerStats * 2, ' ');

        std::cout << playerStatLines[i] + "|" << std::endl;
    }

    drawBottomLine();

    bool hasPressedUpKey = false;
    while (!hasPressedUpKey) {
        switch ((inputKeycode = _getch()))
        {
            case KEY_UP:
                hasPressedUpKey = true;
               break;

            case KEY_DOWN:
               break;

            case KEY_ENTER:
                break;
        }
    }

    return "fick dich";
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

void uiDriver::drawCenterLine()
{
    std::cout << uiDriver::centerLine << std::endl;
}

void uiDriver::drawBottomLine()
{
    std::cout << uiDriver::bottomLine << std::endl;
}