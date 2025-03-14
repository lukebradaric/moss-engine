#include "TextureManager.h"

bool TextureManager::loadTexture(const std::string& textureKey, const std::string& fileName)
{
	std::string fullPath = _basePath + fileName;
	sf::Texture texture;

	if (!texture.loadFromFile(fullPath))
	{
		// Error loading texture
		_logger.logError("Failed to load texture: " + fileName);
		return false;
	}

	_logger.logInfo("Successfully loaded texture: " + fileName);

	_textureMap[textureKey] = texture;
	return true;
}

sf::Texture& TextureManager::getTexture(const std::string& textureKey)
{
	auto iterator = _textureMap.find(textureKey);
	if (iterator == _textureMap.end())
	{
		// Error finding texture
		_logger.logError("Failed to find texture with key: " + textureKey);
		return sf::Texture();
	}

	// Return sf::Texture
	return iterator->second;
}
