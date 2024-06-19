#pragma once
#include "component.h"
#include <string>
#include <map>
#include <vector>


enum combatManeuvers
{
    standartAttack,
    powerStrike,
    sweepingStrike
};

class weapon
{
public:
    std::string name;
    combatManeuvers combatManeuver;
    int d6Amount;
    int damage;
    int combat;
};

class FighterComponent : public Component
{
public:
    virtual ~FighterComponent();
	virtual ComponentID GetID() const override { return ComponentID::Fighter; }

    std::map<std::string, int> fighterStats =
    {
        {"1_show_Hitpoints", -1},
        {"2_hide_MaxHitpoints", -1},
        {"3_show_Strength", -1},
        {"4_show_Dexterity", -1},
        {"5_show_Initiative", -1},
        {"6_hide_Constitution", -1},
        {"7_hide_Combat", -1}
    };

    weapon weapon;

    std::vector<combatManeuvers> combatManeuvers;
};