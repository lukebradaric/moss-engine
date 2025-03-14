#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "core/System.h"
#include "core/Component.h"
#include "core/World.h"
#include "components/PositionComponent.h"
#include "components/VelocityComponent.h"

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