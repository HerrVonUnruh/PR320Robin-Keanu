#include <iostream>
#include <vector>
#include "combatsystem.h"
#include "entity.h"
#include "fightercomponent.h"

int main()
{
    Entity combatSystemEntity;
    CombatSystem* combatSystem = combatSystemEntity.AddComponent<CombatSystem>();

    while (!combatSystem->IsGameOver())
    {
        combatSystem->Update();
    }

    return 0;
}