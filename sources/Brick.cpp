#include <Brick.h>
#include <random>
#include <vector>
#include <ScoreManager.h>

Brick::Brick(float posX, float posY, SDL_Renderer* _renderer)
	: Entity(_renderer)
{
	Entity::setPos(posX, posY);
	ResourceManager& resourceManager = ResourceManager::getInstance();
	std::vector<std::string> textureNames = resourceManager.getLoadedTextureNames();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 19);
	int random_Number = dist(gen);

	while (random_Number % 2 != 0)
	{
		random_Number = dist(gen);
	}

	textureNormalName = textureNames[random_Number];
	textureDamagedName = textureNames[random_Number + 1];
	Entity::changeTexture(textureNormalName);
	renderer = _renderer;
}

void Brick::Damaged()
{
	if (damaged)
	{
		destroyed = true;
		ScoreManager::getInstance().addScore(10);
		return;
	}
	damaged = true;
	Entity::changeTexture(textureDamagedName);
}

bool Brick::isDamaged()
{
	return damaged;
}

bool Brick::isDestroyed()
{
	return destroyed;
}
