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

struct CircleRenderComponent : Component
{
	float radius;
	sf::Color color;

	CircleRenderComponent(float radius, sf::Color color) : radius(radius), color(color) {}
};

struct SpriteRenderComponent : Component
{
	sf::Sprite sprite;
	sf::Texture texture;
	//bool isVisible = true;

	SpriteRenderComponent(const char* fileName)
	{
		if (!texture.loadFromFile(fileName))
		{
			std::cout << "Failed to load texture from: " << fileName << " in directory: " << std::filesystem::current_path() << std::endl;
		}
		else
		{
			std::cout << "Tex load success: " << fileName << " in directory: " << std::filesystem::current_path() << std::endl;
			sprite.setTexture(texture);
		}
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