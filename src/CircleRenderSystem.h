#pragma once

#include "Component.h"
#include "System.h"
#include <SFML/Graphics.hpp>
#include "World.h"

class CircleRenderSystem : public System
{
protected:
	sf::RenderWindow& _window;

public:
	CircleRenderSystem(sf::RenderWindow& window) : _window(window) {}

	void update(float deltaTime, World& world) override
	{
		for (const auto& entity : world.getEntities())
		{
			auto* position = entity.getComponent<PositionComponent>();
			auto* render = entity.getComponent<CircleRenderComponent>();

			if (position == nullptr || render == nullptr)
			{
				continue;
			}

			sf::CircleShape circle(render->radius);
			circle.setFillColor(render->color);
			circle.setPosition(position->x - render->radius, position->y - render->radius);

			_window.draw(circle);
		}
	}
};