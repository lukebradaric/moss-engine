#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include "core/Component.h"

struct RigidbodyComponent : Component
{
	float mass; // body mass
	float bounce; // 0 = none, 1 = full elastic

	RigidbodyComponent(float mass, float bounce) : mass(mass), bounce(bounce) {}
};

#endif