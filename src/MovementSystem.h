#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "System.h"
#include "Component.h"
#include "World.h"

class MovementSystem : public System
{
public:
	void update(float deltaTime, World& world)
	{
		for (const auto& entity : world.getEntities())
		{
			auto* position = entity.getComponent<PositionComponent>();
			auto* velocity = entity.getComponent<VelocityComponent>();

			if (position == nullptr || velocity == nullptr)
			{
				continue;
			}

			position->x += velocity->dx * deltaTime;
			position->y += velocity->dy * deltaTime;
		}
	}
};

#endif