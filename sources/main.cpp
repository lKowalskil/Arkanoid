#include <GameManager.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main()
{
	App app(SCREEN_WIDTH, SCREEN_HEIGHT);
	ResourceManager& resourceManager = ResourceManager::getInstance();
	resourceManager.init(app.renderer);
	ScoreManager& scoreManager = ScoreManager::getInstance();
	scoreManager.init(app.renderer, 10, app.screenSize.y - 50);

	GameManager gameManager(&app, &scoreManager, &resourceManager);
	gameManager.initialize();
	gameManager.run();
	return 0;
}