#pragma once
#include "component.h"
#include <string>
#include <map>
#include <vector>


enum combatManeuvers
{
    standartAttack,
    sweepingStrike,
    powerStrike
};

struct weapon
{
    std::string name = "uhshu";
    int d6Amount = -32;
    int damage = -5345;
    int combat = -677;
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

    weapon currentweapon =
    {
        "nicht richtig gesetzt",
        -3423,
        -3546,
        -78946
    };

    weapon presetWeapons[3] =
    {
        {
            "AK47",
            2,
            3,
            3
        },
        {
            "Dildospear",
            1,
            6,
            6
        },
        {
            "Dubstepmoves",
            3,
            1,
            2
        }
    };

    std::map<std::string, int> defaultPlayerFighterStats =
    {
        {"1_show_Hitpoints", 20},
        {"2_hide_MaxHitpoints", 20},
        {"3_show_Strength", 15},
        {"4_show_Dexterity", 0},
        {"5_show_Initiative", 25},
        {"6_hide_Constitution", 0},
        {"7_hide_Combat", 0}
    };

    std::map<std::string, int> defaultBossFighterStats[3] =
    {
        {//infant panda
            {"1_show_Hitpoints", 35},
            {"2_hide_MaxHitpoints", 35},
            {"3_show_Strength", 25},
            {"4_show_Dexterity", 20},
            {"5_show_Initiative", 15},
            {"6_hide_Constitution", 3},
            {"7_hide_Combat", 10}
        },
        {//skellington
            {"1_show_Hitpoints", 20},
            {"2_hide_MaxHitpoints", 20},
            {"3_show_Strength", 20},
            {"4_show_Dexterity", 20},
            {"5_show_Initiative", 20},
            {"6_hide_Constitution", 20},
            {"7_hide_Combat", 20}
        },
        {//kraken
            {"1_show_Hitpoints", 80},
            {"2_hide_MaxHitpoints", 80},
            {"3_show_Strength", 35},
            {"4_show_Dexterity", 10},
            {"5_show_Initiative", 20},
            {"6_hide_Constitution", 5},
            {"7_hide_Combat", 15}
        }
    };

    std::map<std::string, int> defaultMonsterFighterStats[10] =
    {
        {//monster 1
            {"1_show_Hitpoints", 5},
            {"2_hide_MaxHitpoints", 5},
            {"3_show_Strength", 15},
            {"4_show_Dexterity", 2},
            {"5_show_Initiative", 7},
            {"6_hide_Constitution", 1},
            {"7_hide_Combat", 5}
        },
        {//monster 2
            {"1_show_Hitpoints", 1},
            {"2_hide_MaxHitpoints", 1},
            {"3_show_Strength", 25},
            {"4_show_Dexterity", 0},
            {"5_show_Initiative", 20},
            {"6_hide_Constitution", 0},
            {"7_hide_Combat", 10}
        },
        {//monster 3
            {"1_show_Hitpoints", 25},
            {"2_hide_MaxHitpoints", 25},
            {"3_show_Strength", 15},
            {"4_show_Dexterity", 5},
            {"5_show_Initiative", 25},
            {"6_hide_Constitution", 2},
            {"7_hide_Combat", 10}
        },
        {//monster 4
            {"1_show_Hitpoints", 10},
            {"2_hide_MaxHitpoints", 10},
            {"3_show_Strength", 10},
            {"4_show_Dexterity", 10},
            {"5_show_Initiative", 10},
            {"6_hide_Constitution", 10},
            {"7_hide_Combat", 10}
        },
        {//monster 5
            {"1_show_Hitpoints", 25},
            {"2_hide_MaxHitpoints", 25},
            {"3_show_Strength", 25},
            {"4_show_Dexterity", 25},
            {"5_show_Initiative", 25},
            {"6_hide_Constitution", 25},
            {"7_hide_Combat", 25}
        },
        {//monster 6
            {"1_show_Hitpoints", 8},
            {"2_hide_MaxHitpoints", 8},
            {"3_show_Strength", 12},
            {"4_show_Dexterity", 3},
            {"5_show_Initiative", 5},
            {"6_hide_Constitution", 2},
            {"7_hide_Combat", 4}
        },
        {//monster 7
            {"1_show_Hitpoints", 12},
            {"2_hide_MaxHitpoints", 12},
            {"3_show_Strength", 17},
            {"4_show_Dexterity", 7},
            {"5_show_Initiative", 30},
            {"6_hide_Constitution", 6},
            {"7_hide_Combat", 3}
        },
        {//monster 8
            {"1_show_Hitpoints", 2},
            {"2_hide_MaxHitpoints", 2},
            {"3_show_Strength", 1},
            {"4_show_Dexterity", 16},
            {"5_show_Initiative", 3},
            {"6_hide_Constitution", 15},
            {"7_hide_Combat", 14}
        },
        {//monster 9
            {"1_show_Hitpoints", 1},
            {"2_hide_MaxHitpoints", 1},
            {"3_show_Strength", 1},
            {"4_show_Dexterity", 1},
            {"5_show_Initiative", 1},
            {"6_hide_Constitution", 1},
            {"7_hide_Combat", 1}
        },
        {//monster 10
            {"1_show_Hitpoints", 5},
            {"2_hide_MaxHitpoints", 5},
            {"3_show_Strength", 5},
            {"4_show_Dexterity", 5},
            {"5_show_Initiative", 5},
            {"6_hide_Constitution", 5},
            {"7_hide_Combat", 5}
        }
    };
};