#pragma once

#include "core/System.h"
#include "core/World.h"
#include "SFML/Graphics.hpp"

class CollisionSystem : public System
{
private:
	sf::Vector2f _worldSize;
	static constexpr float GRAVITY = -98.0f;

public:
	CollisionSystem(sf::Vector2f worldSize) : _worldSize(worldSize) {}
	void update(float deltaTime, World& world) override;
};