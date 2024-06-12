#pragma once
#include "component.h"

class FighterComponent : public Component
{
public:
    virtual ~FighterComponent();
	virtual ComponentID GetID() const override { return ComponentID::Fighter; }
};