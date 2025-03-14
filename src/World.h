#ifndef ECS_H
#define ECS_H

#include <unordered_map>
#include <typeindex>
#include "Entity.h"
#include "System.h"
#include "ComponentPool.h"
#include <vector>
#include <memory>

class World
{
protected:
	// Collection of all entities
	std::vector<Entity> _entities;

	// Key = ComponentType, Value = ComponentPool
	// type_index is how we define id's for each ComponentType
	// type_index == Type (C#)
	// std::type_index(typeid(PositionComponent)) would return the identifier for PositionComponent
	/// <summary>
	/// Map of each Component type to their corresponding ComponentPool.
	/// </summary>
	std::unordered_map<std::type_index, std::unique_ptr<ComponentPoolBase>> _typeToPool;

	/// <summary>
	/// The next available Enity Id
	/// </summary>
	size_t _nextId = 0;

	// Collection of systems that operator on our Components!
	std::vector<std::unique_ptr<System>> _systems;

	// Returns a ComponentPool of component type
	template<typename T>
	ComponentPool<T>* getPool()
	{
		std::type_index type = typeid(T);
		auto iterator = _typeToPool.find(type);
		if (iterator == _typeToPool.end())
		{
			//return nullptr;
			_typeToPool[type] = std::make_unique<ComponentPool<T>>();
		}

		return static_cast<ComponentPool<T>*>(_typeToPool[type].get());
	}

public:
	World()
	{
		// Reserve number of buckets for data
		// Minimum capacity
		// I assume this is similar to "Prewarming" a pool, without actually creating data
		_typeToPool.reserve(10);
	}

	Entity createEntity();

	template<typename T>
	void addComponent(size_t entityId, const T& component)
	{
		// Get the pool associated with component type, add component with entity id to pool
		const_cast<World*>(this)->getPool<T>()->add(entityId, component);
	}

	template<typename T>
	T* getComponent(size_t entityId) const
	{
		return const_cast<World*>(this)->getPool<T>()->get(entityId);
	}

	template<typename T>
	bool hasComponent(size_t entityId) const
	{
		return const_cast<World*>(this)->getPool<T>->has(entityId);
	}

	// Adds a system to run on the world
	void addSystem(std::unique_ptr<System> system);

	// Updates all systems assigned to world
	void update(float deltaTime);

	// Returns a reference to entities
	// Entities cannot be modified
	inline const std::vector<Entity>& getEntities() const { return _entities; }
};

#endif