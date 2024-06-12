#include <iostream>
#include <vector>
#include "combatsystem.h"
#include "entity.h"
#include "fightercomponent.h"
#include "uiDriver.h"

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
        uiDriver.displayMonster();

        
        system("pause");
    }

    return 0;
}