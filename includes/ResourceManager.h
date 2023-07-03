#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>

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
	TTF_Font* getFont(const std::string& name) const;
	std::vector<std::string> getLoadedTextureNames();
	std::vector<std::string> getLoadedFontNames();
	void init(SDL_Renderer* _renderer);

private:
	ResourceManager();
	~ResourceManager();

	SDL_Renderer* renderer = nullptr;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	void loadTexture(const std::string& name, const std::string& filePath);
	void loadFont(const std::string& name, const std::string& filePath);
	bool isTextureLoaded(const std::string& name) const;
	bool isFontLoaded(const std::string& name) const;

	std::unordered_map<std::string, SDL_Texture*> m_textureMap;
	std::vector<std::string> textureNames;
	std::unordered_map<std::string, TTF_Font*> m_fontMap;
	std::vector<std::string> fontNames;
};

#endif