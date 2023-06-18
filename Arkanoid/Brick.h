#include <Entity.h>
#include <ResourceManager.h>

class Brick : public Entity
{
public:
	Brick(float posX, float posY, SDL_Renderer* _renderer);
	void Damaged();
	bool isDestroyed();
	bool isDamaged();

private:
	std::string textureNormalName;
	std::string textureDamagedName;
	bool damaged = false;
	bool destroyed = false;
	SDL_Renderer* renderer;
};