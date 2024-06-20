#pragma once

#include <map>
#include "component.h"

enum class entityType
{
	player,
	enemy,
	boss
};

class Entity
{
public:
	Entity();
	~Entity();

	void Update();

	void AddComponent(Component* component);

	//Nice to have for developer convenience...
	template <class T>
	T* AddComponent()
	{
		T* component = new T();
		AddComponent(component);
		return component;
	}

	Component* GetComponent(ComponentID id) const;

	//Nice to have for developer convenience...
	// In entity.h

	template <class T>
	T* GetComponent() const
	{
		for (const auto& pair : _components)
		{
			if (T* component = dynamic_cast<T*>(pair.second))
			{
				return component;
			}
		}
		return nullptr;
	}

	void SendMessage(int id);

	entityType entityType;
	int entitySubType;

private:
    Entity(Entity& other) = delete;
	Entity(Entity&& other) = delete;
	Entity& operator=(Entity& other) = delete;
	Entity& operator=(Entity&& other) = delete;

	//map is a sorted container, iteration will be in component id order
	std::map<ComponentID, Component*> _components;
};