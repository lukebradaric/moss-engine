#ifndef SPRITERENDERCOMPONENT_H
#define SPRITERENDERCOMPONENT_H

#include "core/Component.h"
#include "SFML/Graphics.hpp"

struct SpriteRenderComponent : Component
{
	sf::Sprite sprite;
	sf::Vector2f origin;

	SpriteRenderComponent(sf::Texture& textureRef)
	{
		sprite.setTexture(textureRef);
		sf::Vector2u textureSize = textureRef.getSize();
		origin = sf::Vector2f(textureSize.x / 2.0f, textureSize.y / 2.0f);
	}
};

#endif