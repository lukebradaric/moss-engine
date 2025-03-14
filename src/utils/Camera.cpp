#include "Camera.h"

sf::Vector2f Camera::worldToScreenPosition(const sf::Vector2f& worldPos, const sf::Vector2u& windowSize) const
{
	float scale = getScale();

	float screenX = (worldPos.x - position.x) * scale + windowSize.x / 2.0f;
	float screenY = (worldPos.y + position.y) * scale + windowSize.y / 2.0f;
	return sf::Vector2f(screenX, screenY);
}