#pragma once
#include "component.h"
#include <string>
#include <map>

class FighterComponent : public Component
{
public:
    virtual ~FighterComponent();
	virtual ComponentID GetID() const override { return ComponentID::Fighter; }

    std::map<std::string, int> fighterStats =
    {
        {"Strength", -1},
        {"Dexterity", -1},
        {"Constitution", -1},
        {"MaxHitpoints", -1},
        {"Hitpoints", -1},
        {"Combat", -1},
        {"Initiative", -1}
    };
};