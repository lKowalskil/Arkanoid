#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL.h>

#include <Functions.h>
#include <unordered_map>
#include <string>
#include <vector>

class ResourceManager
{
public:
	static ResourceManager& getInstance();
	SDL_Texture* getTexture(const std::string& name) const;
	vec2f getTextureSize(const std::string& name);
	std::vector<std::string> getLoadedTextureNames();
	void init(SDL_Renderer* _renderer);

	SDL_Renderer* renderer = nullptr;

private:
	ResourceManager();
	~ResourceManager();


	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	void loadTexture(const std::string& name, const std::string& filePath);
	bool isTextureLoaded(const std::string& name) const;

	std::unordered_map<std::string, SDL_Texture*> m_textureMap;
	std::vector<std::string> textureNames;
};

#endif