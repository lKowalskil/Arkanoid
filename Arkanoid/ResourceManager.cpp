#include "ResourceManager.h"

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
		char buffer[100];
		sprintf_s(buffer, "ResourceManager::loadTexture -> There is an error while loading texture %s from %s : IMG_GetError - %s", name.c_str(), filePath.c_str(), error);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr);
	}
	else
	{
		m_textureMap.insert(std::make_pair(name, texture));
		textureNames.push_back(name);
	}
}

bool ResourceManager::isTextureLoaded(const std::string& name) const
{
	return m_textureMap.find(name) != m_textureMap.end();
}

SDL_Texture* ResourceManager::getTexture(const std::string& name) const
{
	if (isTextureLoaded(name))
	{
		return m_textureMap.find(name)->second;
	}
	else
	{
		char buffer[100];
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
		char buffer[100];
		sprintf_s(buffer, "ResourceManager::getTextureSize -> There is no such texture loaded as %s", name.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr);
	}
}

std::vector<std::string> ResourceManager::getLoadedTextureNames()
{
	return textureNames;
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
}
