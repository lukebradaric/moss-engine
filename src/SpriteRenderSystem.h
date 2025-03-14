#ifndef SPRITERENDERSYSTEM_H
#define SPRITERENDERSYSTEM_H

#include "Component.h"
#include "System.h"
#include <SFML/Graphics.hpp>
#include "World.h"

class SpriteRenderSystem : public System
{
protected:
	sf::RenderWindow& _window;

public:
	SpriteRenderSystem(sf::RenderWindow& window) : _window(window) {}

	void update(float deltaTime, World& world) override
	{
		for (const auto& entity : world.getEntities())
		{
			auto* position = entity.getComponent<PositionComponent>();
			auto* render = entity.getComponent<SpriteRenderComponent>();

			if (position == nullptr || render == nullptr)
			{
				continue;
			}

			render->sprite.setPosition(sf::Vector2f(position->x, position->y));
			render->sprite.setScale(sf::Vector2f(5.0f, 5.0f));
			_window.draw(render->sprite);
		}
	}
};

#endif