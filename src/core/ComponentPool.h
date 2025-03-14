#ifndef COMPONENTPOOL_H
#define COMPONENTPOOL_H

#include "ComponentPoolBase.h"
#include "Component.h"
#include <unordered_map>
#include <vector>

template<typename T>
class ComponentPool : public ComponentPoolBase
{
	// Ensure generic type is a component
	static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

protected:

	// Vector to store components contiuously in memory
	// Like List<T> in C#, but no dynamic resizing
	std::vector<T> _components;

	// Mapping of each entity Id to component index
	// Like Dictionary<T,T> in C#
	// size_t = unsigned int, size_t is defined in standard library
	// using size_t instead of unsigned int because the max value can differ between platforms
	std::unordered_map<size_t, size_t> _entityToIndex;

public:

	// Adds component to ComponentPool and returns index
	size_t add(size_t entityId, const T& component)
	{
		size_t index = _components.size();
		_components.push_back(component);
		_entityToIndex[entityId] = index;
		return index;
	}

	// Returns pointer to component with associated entityId
	// Returns nullptr if the component is not found
	T* get(size_t entityId)
	{
		// Find pair element with matching entityId
		// Note: Find is a single hash lookup (does not work like Linq)
		auto iterator = _entityToIndex.find(entityId);

		// If iterator is not the end of the map
		if (iterator != _entityToIndex.end())
		{
			// return pointer to component based on entityToIndex
			// iterator->second is returning the value from the key/value pair
			return &_components[iterator->second];
		}

		return nullptr;
	}


	// Returns if the ComponentPool has a component for the entityId
	// Const at the end of function declaration means the function will not modify the state of ComponentPool
	bool has(size_t entityId) const
	{
		// return if map contains entry for entityId
		return _entityToIndex.contains(entityId);
	}
};

#endif