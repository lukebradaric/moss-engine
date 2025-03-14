#include "World.h"

Entity World::createEntity()
{
	Entity entity(_nextId++, *this);
	_entities.push_back(entity);
	return entity;
}

void World::addSystem(std::unique_ptr<System> system)
{
	_systems.push_back(std::move(system));
}

void World::update(float deltaTime)
{
	for (auto& system : _systems)
	{
		system->update(deltaTime, *this);
	}
}