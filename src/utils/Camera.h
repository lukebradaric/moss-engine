#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera
{
public:
	sf::Vector2f position;

	float orthoSize;
	float pixelsPerUnit;

	Camera(float orthoSize = 7.0f, float pixelsPerUnit = 16.0f) : position(0.0f, 0.0f), orthoSize(orthoSize), pixelsPerUnit(pixelsPerUnit) {}

	// Get scale (PixelsPerUnit adjusted based on orthoSize)
	inline float getScale() const { return pixelsPerUnit * (orthoSize / 7.0f); }

	sf::Vector2f worldToScreenPosition(const sf::Vector2f& worldPos, const sf::Vector2u& windowSize) const;
};

#endif