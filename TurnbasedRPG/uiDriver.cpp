#include "uiDriver.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

void uiDriver::displayMonster() 
{
    int maxMonsterAmount = (sizeof(monsterGrafix) / sizeof(monsterGrafix[0]));
    int maxLinesPerMonster = (sizeof(monsterGrafix[0]) / sizeof(monsterGrafix[0][0]));

    int firstMonster = rand() % maxMonsterAmount;
    int secondMonster = rand() % maxMonsterAmount;
    int thirdMonster = rand() % maxMonsterAmount;
    int fourthMonster = rand() % maxMonsterAmount;

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