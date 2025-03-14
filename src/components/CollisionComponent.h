#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "core/Component.h"

struct CollisionComponent : Component
{
	float radius; // radius of circle collision

	CollisionComponent(float radius) : radius(radius) {}
};

#endif