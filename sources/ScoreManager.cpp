#include "ScoreManager.h"

void ScoreManager::init(SDL_Renderer* _renderer, int _x, int _y)
{
	score = 0;
	renderer = _renderer;
	font = ResourceManager::getInstance().getFont("Abbieshire");
	if (!font)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "ScoreManager::ScoreManager -> font loading from resource manager is not successful", nullptr);
		return;
	}

	textRect.x = _x;
	textRect.y = _y;
	textRect.w = 100;
	textRect.h = 30;
}

ScoreManager::ScoreManager()
{

}

ScoreManager::~ScoreManager()
{
	TTF_Quit();
}

ScoreManager& ScoreManager::getInstance()
{
	static ScoreManager instance;
	return instance;
}

void ScoreManager::addScore(int points)
{
	score += points;
}

void ScoreManager::drawScore()
{
	std::string scoreText = "Score: " + std::to_string(score);

	SDL_assert(font != nullptr);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
	if (!textSurface)
	{
		char buffer[256];
		const char* error = TTF_GetError();
		sprintf_s(buffer, "ScoreManager::drawScore -> error while creating SDL_Surface : TTF_GetError : %s", error);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr);
		return;
	}

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!textTexture)
	{
		char buffer[256];
		const char* error = SDL_GetError();
		sprintf_s(buffer, "ScoreManager::drawScore -> error while creating text texture from sdl surface : SDL_GetError : %s", error);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr);
		return;
	}

	SDL_DestroySurface(textSurface);
	SDL_RenderTexture(renderer, textTexture, nullptr, &textRect);
	SDL_DestroyTexture(textTexture);
}
