#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <unordered_map>
#include "Logger.h"

class TextureManager
{
private:
	std::unordered_map<std::string, sf::Texture> _textureMap;
	std::string _basePath = "assets/textures/";
	Logger _logger;

public:
	TextureManager()
	{
		_logger = Logger("TextureManager");
	}

	bool loadTexture(const std::string& textureKey, const std::string& fileName);
	sf::Texture& getTexture(const std::string& textureKey);
};

#endif