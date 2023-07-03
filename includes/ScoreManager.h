#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include <string>
#include <ResourceManager.h>

class ScoreManager {
private:
	int score;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color textColor;
	SDL_FRect textRect;

public:
	static ScoreManager& getInstance();
	void init(SDL_Renderer* _renderer, int _x, int _y);
	void addScore(int points);
	void drawScore();

private:
	ScoreManager();
	~ScoreManager();
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;
};