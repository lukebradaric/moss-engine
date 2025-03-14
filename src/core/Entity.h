#ifndef ENTITY_H
#define ENTITY_H

class World;

class Entity
{
protected:
	// The Id of this Entity
	size_t _id;

	// The world that this Entity belongs too
	// Used for component lookups
	World& _world;
public:
	// Constructor
	// id(id) initializes the value of the variable to the id parameter
	Entity(size_t id, World& world) : _id(id), _world(world) {}
	size_t getId() const { return _id; }

	template<typename T>
	T* addComponent(const T& component)
	{
		_world.addComponent<T>(_id, component);
		return const_cast<T*>(&component);
	}

	template<typename T>
	T* getComponent() const
	{
		return _world.getComponent<T>(_id);
	}

	template<typename T>
	bool hasComponent() const
	{
		return _world.hasComponent<T>(_id);
	}
};

#endif