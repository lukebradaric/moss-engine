#ifndef SYSTEM_H
#define SYSTEM_H

class World;

class System
{
public:
	virtual ~System() = default;
	virtual void update(float deltaTime, World& world) = 0;
};

#endif