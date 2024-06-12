#include "uiDriver.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

void uiDriver::displayMonster() 
{
    int firstMonster = rand() % 10;
    int secondMonster = rand() % 10;
    int thirdMonster = rand() % 10;
    int fourthMonster = rand() % 10;

    std::string lines[7];

    for (int i = 0; i < 7; i++)
    {
        lines[i] += monsterGrafix[firstMonster][i];
        lines[i] += monsterGrafix[secondMonster][i];
        lines[i] += monsterGrafix[thirdMonster][i];
        lines[i] += monsterGrafix[fourthMonster][i];

        lines[i] += "|";
    }

    for (int i = 0; i < 7; i++)
    {
        std::cout << lines[i] << std::endl;
    }
}