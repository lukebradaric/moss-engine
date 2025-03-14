#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

struct Component
{
	virtual ~Component() = default;
	int z0 = 5;
};

struct PositionComponent : Component
{
	float x;
	float y;

	PositionComponent(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
};

struct VelocityComponent : Component
{
	float dx;
	float dy;

	VelocityComponent(float dx = 0.0f, float dy = 0.0f) : dx(dx), dy(dy) {}
};

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

struct RigidbodyComponent : Component
{
	float mass; // body mass
	float bounce; // 0 = none, 1 = full elastic

	RigidbodyComponent(float mass, float bounce) : mass(mass), bounce(bounce) {}
};

struct CollisionComponent : Component
{
	float radius; // radius of circle collision

	CollisionComponent(float radius) : radius(radius) {}
};

#endif