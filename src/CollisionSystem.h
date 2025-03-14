#pragma once

#include "System.h"
#include "World.h"

class CollisionSystem : public System
{
private:
	sf::RenderWindow& _window;
	static constexpr float GRAVITY = 980.0f;

public:
	CollisionSystem(sf::RenderWindow& window) : _window(window) {}
	void update(float deltaTime, World& world) override;
};