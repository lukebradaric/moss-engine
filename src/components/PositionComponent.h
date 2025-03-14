#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "core/Component.h"

struct PositionComponent : Component
{
	float x;
	float y;

	PositionComponent(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
};

#endif