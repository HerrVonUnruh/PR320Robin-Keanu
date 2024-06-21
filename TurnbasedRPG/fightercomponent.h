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
        {"3_show_Strength", 0},
        {"4_show_Dexterity", 0},
        {"5_show_Initiative", 0},
        {"6_hide_Constitution", 0},
        {"7_hide_Combat", 0}
    };

    std::map<std::string, int> defaultBossFighterStats[3] =
    {
        {//infant panda
            {"1_show_Hitpoints", 20},
            {"2_hide_MaxHitpoints", 20},
            {"3_show_Strength", 4},
            {"4_show_Dexterity", 4},
            {"5_show_Initiative", 4},
            {"6_hide_Constitution", 4},
            {"7_hide_Combat", 4}
        },
        {//skellington
            {"1_show_Hitpoints", 15},
            {"2_hide_MaxHitpoints", 15},
            {"3_show_Strength", 5},
            {"4_show_Dexterity", 5},
            {"5_show_Initiative", 5},
            {"6_hide_Constitution", 5},
            {"7_hide_Combat", 5}
        },
        {//kraken
            {"1_show_Hitpoints", 25},
            {"2_hide_MaxHitpoints", 25},
            {"3_show_Strength", 4},
            {"4_show_Dexterity", 4},
            {"5_show_Initiative", 3},
            {"6_hide_Constitution", 2},
            {"7_hide_Combat", 2}
        }
    };

    std::map<std::string, int> defaultMonsterFighterStats[10] =
    {
        {//monster 1
            {"1_show_Hitpoints", 5},
            {"2_hide_MaxHitpoints", 5},
            {"3_show_Strength", 5},
            {"4_show_Dexterity", 1},
            {"5_show_Initiative", 1},
            {"6_hide_Constitution", 1},
            {"7_hide_Combat", 1}
        },
        {//monster 2
            {"1_show_Hitpoints", 1},
            {"2_hide_MaxHitpoints", 1},
            {"3_show_Strength", 5},
            {"4_show_Dexterity", 5},
            {"5_show_Initiative", 1},
            {"6_hide_Constitution", 1},
            {"7_hide_Combat", 2}
        },
        {//monster 3
            {"1_show_Hitpoints", 2},
            {"2_hide_MaxHitpoints", 2},
            {"3_show_Strength", 1},
            {"4_show_Dexterity", 5},
            {"5_show_Initiative", 2},
            {"6_hide_Constitution", 2},
            {"7_hide_Combat", 3}
        },
        {//monster 4
            {"1_show_Hitpoints", 1},
            {"2_hide_MaxHitpoints", 1},
            {"3_show_Strength", 10},
            {"4_show_Dexterity", 1},
            {"5_show_Initiative", 1},
            {"6_hide_Constitution", 1},
            {"7_hide_Combat", 1}
        },
        {//monster 5
            {"1_show_Hitpoints", 500},
            {"2_hide_MaxHitpoints", 5},
            {"3_show_Strength", 0},
            {"4_show_Dexterity", 1},
            {"5_show_Initiative", 1},
            {"6_hide_Constitution", 1},
            {"7_hide_Combat", 0}
        },
        {//monster 6
            {"1_show_Hitpoints", 0},
            {"2_hide_MaxHitpoints", 6},
            {"3_show_Strength", 0},
            {"4_show_Dexterity", 3},
            {"5_show_Initiative", 1},
            {"6_hide_Constitution", 2},
            {"7_hide_Combat", 0}
        },
        {//monster 7
            {"1_show_Hitpoints", 4},
            {"2_hide_MaxHitpoints", 4},
            {"3_show_Strength", 4},
            {"4_show_Dexterity", 4},
            {"5_show_Initiative", 1},
            {"6_hide_Constitution", 1},
            {"7_hide_Combat", 1}
        },
        {//monster 8
            {"1_show_Hitpoints", 2},
            {"2_hide_MaxHitpoints", 2},
            {"3_show_Strength", 1},
            {"4_show_Dexterity", 4},
            {"5_show_Initiative", 3},
            {"6_hide_Constitution", 5},
            {"7_hide_Combat", 0}
        },
        {//monster 9
            {"1_show_Hitpoints", 6},
            {"2_hide_MaxHitpoints", 6},
            {"3_show_Strength", 1},
            {"4_show_Dexterity", 1},
            {"5_show_Initiative", 1},
            {"6_hide_Constitution", 1},
            {"7_hide_Combat", 5}
        },
        {//monster 10
            {"1_show_Hitpoints", 5},
            {"2_hide_MaxHitpoints", 5},
            {"3_show_Strength", 5},
            {"4_show_Dexterity", 5},
            {"5_show_Initiative", 0},
            {"6_hide_Constitution", 0},
            {"7_hide_Combat", 0}
        }
    };
};