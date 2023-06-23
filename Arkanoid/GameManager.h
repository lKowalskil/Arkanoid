#pragma once

#include <App.h>
#include <ScoreManager.h>
#include <Brick.h>

class GameManager
{
private:
	App* app;
	ScoreManager* scoreManager;
	ResourceManager* resourceManager;
	std::vector<Brick> bricks;
	Player* player;
	Ball* ball;
	bool gameover = false;

public:
	GameManager(App* _app, ScoreManager* _scoreManager, ResourceManager* _resourceManager);
	void initialize();
	void handleInput();
	void update(float deltaTime);
	void draw();
	void run();
	~GameManager();
};