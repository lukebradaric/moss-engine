#include "TextureManager.h"

bool TextureManager::loadTexture(const std::string& textureKey, const std::string& fileName)
{
	std::string fullPath = _basePath + fileName;
	sf::Texture texture;

	if (!texture.loadFromFile(fullPath))
	{
		// Error loading texture
		std::cerr << "Failed to load texture: " << fullPath << std::endl;
		return false;
	}

	_textureMap[textureKey] = texture;
	return true;
}

sf::Texture& TextureManager::getTexture(const std::string& textureKey)
{
	auto iterator = _textureMap.find(textureKey);
	if (iterator == _textureMap.end())
	{
		// Error finding texture
	}

	// Return sf::Texture
	return iterator->second;
}
