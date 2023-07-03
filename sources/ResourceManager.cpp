#include "ResourceManager.h"
#include <Windows.h>

ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;
	return instance;
}

void ResourceManager::loadTexture(const std::string& name, const std::string& filePath)
{
	SDL_Texture* texture = nullptr;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filePath.c_str());
	SDL_assert(renderer != nullptr && !name.empty() && !filePath.empty());
	texture = IMG_LoadTexture(renderer, filePath.c_str());
	if (texture == nullptr)
	{
		const char* error = IMG_GetError();
		char buffer[256];
		sprintf_s(buffer, "ResourceManager::loadTexture -> There is an error while loading texture %s from %s : IMG_GetError - %s", name.c_str(), filePath.c_str(), error);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr);
	}
	else
	{
		m_textureMap.insert(std::make_pair(name, texture));
		textureNames.push_back(name);
	}
}

void ResourceManager::loadFont(const std::string& name, const std::string& filePath)
{
	TTF_Font* font = nullptr;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filePath.c_str());
	SDL_assert(renderer != nullptr && !name.empty() && !filePath.empty());
	font = TTF_OpenFont(filePath.c_str(), 24);
	if (font == nullptr)
	{
		const char* error = SDL_GetError();
		char buffer[256];
		sprintf_s(buffer, "ResourceManager::loadTexture -> There is an error while loading font %s from %s : SDL_GetError - %s", name.c_str(), filePath.c_str(), error);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr);
	}
	else
	{
		m_fontMap.insert(std::make_pair(name, font));
		fontNames.push_back(name);
	}
}

bool ResourceManager::isTextureLoaded(const std::string& name) const
{
	return m_textureMap.find(name) != m_textureMap.end();
}

bool ResourceManager::isFontLoaded(const std::string& name) const
{
	return m_fontMap.find(name) != m_fontMap.end();
}

SDL_Texture* ResourceManager::getTexture(const std::string& name) const
{
	if (isTextureLoaded(name))
	{
		return m_textureMap.find(name)->second;
	}
	else
	{
		char buffer[256];
		sprintf_s(buffer, "ResourceManager::getTexture -> There is no such texture loaded as %s", name.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr);
	}
}

vec2f ResourceManager::getTextureSize(const std::string& name)
{
	if (isTextureLoaded(name))
	{
		SDL_Texture* texture = m_textureMap[name];
		int width, height;
		SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
		return vec2f(width, height);
	}
	else
	{
		char buffer[256];
		sprintf_s(buffer, "ResourceManager::getTextureSize -> There is no such texture loaded as %s", name.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr);
	}
}

TTF_Font* ResourceManager::getFont(const std::string& name) const
{
	if (isFontLoaded(name))
	{
		return m_fontMap.find(name)->second;
	}
	else
	{
		char buffer[256];
		sprintf_s(buffer, "ResourceManager::getFont -> There is no such font loaded as %s", name.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr);
	}
}

std::vector<std::string> ResourceManager::getLoadedTextureNames()
{
	return textureNames;
}

std::vector<std::string> ResourceManager::getLoadedFontNames()
{
	return fontNames;
}


ResourceManager::ResourceManager()
{	
}

ResourceManager::~ResourceManager()
{
	for (auto& texturePair : m_textureMap)
	{
		SDL_DestroyTexture(texturePair.second);
	}
	m_textureMap.clear();
}

void ResourceManager::init(SDL_Renderer* _renderer)
{
	renderer = _renderer;
	if (IsDebuggerPresent())
	{
		loadTexture("BlueBrick", "../assets/01.png");
		loadTexture("BlueBrickDamaged", "../assets/02.png");
		loadTexture("LightGreenBrick", "../assets/03.png");
		loadTexture("LightGreenBrickDamaged", "../assets/04.png");
		loadTexture("PurpleBrick", "../assets/05.png");
		loadTexture("PurpleBrickDamaged", "../assets/06.png");
		loadTexture("RedBrick", "../assets/07.png");
		loadTexture("RedBrickDamaged", "../assets/08.png");
		loadTexture("OrangeBrick", "../assets/09.png");
		loadTexture("OrangeBrickDamaged", "../assets/10.png");
		loadTexture("BlueBrick", "../assets/11.png");
		loadTexture("BlueBrickDamaged", "../assets/12.png");
		loadTexture("YellowBrick", "../assets/13.png");
		loadTexture("YellowBrickDamaged", "../assets/14.png");
		loadTexture("GreenBrick", "../assets/15.png");
		loadTexture("GreenBrickDamaged", "../assets/16.png");
		loadTexture("GrayBrick", "../assets/17.png");
		loadTexture("GrayBrickDamaged", "../assets/18.png");
		loadTexture("BrownBrick", "../assets/19.png");
		loadTexture("BrownBrickDamaged", "../assets/20.png");
		loadTexture("Player", "../assets/50.png");
		loadTexture("Player1", "../assets/51.png");
		loadTexture("Player2", "../assets/52.png");
		loadTexture("Ball", "../assets/64.png");
		loadTexture("BonusScore1", "../assets/32.png");
		loadTexture("BonusScore2", "../assets/33.png");
		loadTexture("BonusScore3", "../assets/34.png");
		loadTexture("BonusScore4", "../assets/35.png");
		loadTexture("BonusScore5", "../assets/36.png");
		loadTexture("BonusScore6", "../assets/37.png");
		loadFont("Abbieshire", "../assets/Abbieshire.ttf");
	}
	else
	{
		loadTexture("BlueBrick", "assets/01.png");
		loadTexture("BlueBrickDamaged", "assets/02.png");
		loadTexture("LightGreenBrick", "assets/03.png");
		loadTexture("LightGreenBrickDamaged", "assets/04.png");
		loadTexture("PurpleBrick", "assets/05.png");
		loadTexture("PurpleBrickDamaged", "assets/06.png");
		loadTexture("RedBrick", "assets/07.png");
		loadTexture("RedBrickDamaged", "assets/08.png");
		loadTexture("OrangeBrick", "assets/09.png");
		loadTexture("OrangeBrickDamaged", "assets/10.png");
		loadTexture("BlueBrick", "assets/11.png");
		loadTexture("BlueBrickDamaged", "assets/12.png");
		loadTexture("YellowBrick", "assets/13.png");
		loadTexture("YellowBrickDamaged", "assets/14.png");
		loadTexture("GreenBrick", "assets/15.png");
		loadTexture("GreenBrickDamaged", "assets/16.png");
		loadTexture("GrayBrick", "assets/17.png");
		loadTexture("GrayBrickDamaged", "assets/18.png");
		loadTexture("BrownBrick", "assets/19.png");
		loadTexture("BrownBrickDamaged", "assets/20.png");
		loadTexture("Player", "assets/50.png");
		loadTexture("Player1", "assets/51.png");
		loadTexture("Player2", "assets/52.png");
		loadTexture("Ball", "assets/64.png");
		loadTexture("BonusScore1", "assets/32.png");
		loadTexture("BonusScore2", "assets/33.png");
		loadTexture("BonusScore3", "assets/34.png");
		loadTexture("BonusScore4", "assets/35.png");
		loadTexture("BonusScore5", "assets/36.png");
		loadTexture("BonusScore6", "assets/37.png");
		loadFont("Abbieshire", "assets/Abbieshire.ttf");
	}
}
