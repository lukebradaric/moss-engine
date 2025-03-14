#ifndef SPRITERENDERSYSTEM_H
#define SPRITERENDERSYSTEM_H

#include "Component.h"
#include "System.h"
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Camera.h"

class SpriteRenderSystem : public System
{
protected:
	sf::RenderWindow& _window;
	const Camera& _camera;

public:
	SpriteRenderSystem(sf::RenderWindow& window, const Camera& camera) : _window(window), _camera(camera) {}

	void update(float deltaTime, World& world) override
	{
		sf::Vector2u windowSize = _window.getSize();
		for (const auto& entity : world.getEntities())
		{
			auto* position = entity.getComponent<PositionComponent>();
			auto* render = entity.getComponent<SpriteRenderComponent>();

			if (position == nullptr || render == nullptr)
			{
				continue;
			}

			// Convert entity world position to screen position
			sf::Vector2f screenPosition = _camera.worldToScreenPosition(sf::Vector2f(position->x, -position->y), windowSize);
			render->sprite.setOrigin(render->origin);
			render->sprite.setPosition(screenPosition);

			float scale = _camera.getScale();
			sf::Vector2u textureSize = render->sprite.getTexture()->getSize();
			float scaleX = scale / textureSize.x;
			float scaleY = scale / textureSize.y;
			render->sprite.setScale(scaleX, scaleY);

			_window.draw(render->sprite);
		}
	}
};

#endif