#include "uiDriver.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iterator>
#include <conio.h>
#include <iostream>
#include <windows.h>

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

std::string uiDriver::drawMenu(std::string* playerStatLines, int lineAmount, std::string tagLine, std::string menuItems[], int menuItemCount, int& lastMenuIndexOffset, int& lastMenuIndex, bool setMenuIndexAndOffset)
{
    int inputKeycode = 0;
    int menuIndex = 0;
    int menuIndexOffset = 0;

    std::string selectedMenuItem = "none";

    if (setMenuIndexAndOffset)
    {
        menuIndex = lastMenuIndex;
        menuIndexOffset = lastMenuIndexOffset;
    }

    bool pressedKey = false;
    while (!pressedKey) {
        playerStatLines[0] += "|" + tagLine;

        for (int i = 1; i < lineAmount; i++) {
            playerStatLines[i] = playerStatLines[i].substr(0, characterAmountForPlayerStats) + " ";
        }

        for (int i = 0; i < 4; i++)
        {
            if (i + menuIndexOffset < menuItemCount) {
                playerStatLines[i + 2] += "     " + menuItems[i + menuIndexOffset];
            }
            else {
                playerStatLines[i + 2] += "     ";
            }
        }

        playerStatLines[menuIndex + 2].replace(characterAmountForPlayerStats + 3, 2, "->");

        if (menuIndexOffset > 0)
        {
            playerStatLines[1].replace(characterAmountForPlayerStats, 2, "           ^");
        }

        if (menuIndexOffset + 4 < menuItemCount)
        {
            playerStatLines[6].replace(characterAmountForPlayerStats, 2, "           v");
        }

        for (int i = 0; i < lineAmount; i++)
        {
            playerStatLines[i].replace(characterAmountForPlayerStats, 1, "|");
            playerStatLines[i].resize(characterAmountForPlayerStats * 2, ' ');

            std::cout << playerStatLines[i] + "|" << std::endl;
        }

        drawBottomLine();

        switch ((inputKeycode = _getch()))
        {
        case KEY_UP:
            if (menuIndex == 0 && menuIndexOffset == 0)
            {
                break;
            }

            menuIndex--;

            if (menuIndex < 0)
            {
                if (menuIndexOffset > 0)
                {
                    menuIndex = 0;
                    menuIndexOffset--;
                }
                else
                {
                    menuIndex = menuItemCount - 1;
                    if (menuItemCount > 4)
                    {
                        menuIndexOffset = menuItemCount - 4;
                    }
                }
            }
            break;

        case KEY_DOWN:
            if (menuIndex == 4 && menuIndexOffset == menuItemCount - 4)
            {
                break;
            }

            menuIndex++;

            if (menuIndex == 4 && menuItemCount > 4)
            {
                menuIndexOffset++;
                menuIndex--;

                if (menuIndexOffset >= menuItemCount - 4)
                {
                    menuIndexOffset = menuItemCount - 4;
                }
            }
            else if (menuIndex >= menuItemCount)
            {
                menuIndex = menuItemCount - 1;
            }
            break;

        case KEY_ENTER:
            pressedKey = true;
            selectedMenuItem = menuItems[menuIndex + menuIndexOffset];
            break;

        default:
            break;
        }

        int x = 0;
        int y = 0;
        getCursorPosition(x, y);
        setCursorPosition(x, y - 8);

        
        for (int i = 0; i < 4; i++)
        {
            playerStatLines[i + 2].replace(characterAmountForPlayerStats + 3, 2, "  ");
        }
    }

    lastMenuIndex = menuIndex;
    lastMenuIndexOffset = menuIndexOffset;

    return selectedMenuItem;
}


void uiDriver::setCursorPosition(int x, int y) {
    // Get the console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error getting console handle." << std::endl;
        return;
    }

    // Set the cursor position
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(hConsole, position);
}

void uiDriver::getCursorPosition(int& x, int& y) {
    // Get the console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error getting console handle." << std::endl;
        return;
    }

    // Get console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "Error getting console screen buffer info." << std::endl;
        return;
    }

    // Extract cursor position
    x = csbi.dwCursorPosition.X;
    y = csbi.dwCursorPosition.Y;
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