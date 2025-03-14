#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include "core/Component.h"

struct VelocityComponent : Component
{
	float dx;
	float dy;

	VelocityComponent(float dx = 0.0f, float dy = 0.0f) : dx(dx), dy(dy) {}
};

#endif