#include "GameManager.h"
#include <chrono>

void doKeyDown(SDL_KeyboardEvent* event, App* app)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app->up = true;
		}
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app->down = true;
		}
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app->left = true;
		}
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app->right = true;
		}
	}
}
void doKeyUp(SDL_KeyboardEvent* event, App* app)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app->up = false;
		}
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app->down = false;
		}
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app->left = false;
		}
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app->right = false;
		}
	}
}
void prepareScene(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
	SDL_RenderClear(renderer);
}
void presentScene(SDL_Renderer* renderer)
{
	SDL_RenderPresent(renderer);
}

GameManager::GameManager(App* _app, ScoreManager* _scoreManager, ResourceManager* _resourceManager)
 : app(_app), scoreManager(_scoreManager), resourceManager(_resourceManager), ball(nullptr), player(nullptr){}

void GameManager::initialize()
{
	player = new Player(app->screenSize.x / 2, app->screenSize.y - app->screenSize.y / 5, app->renderer);
	player->setSpeed(150);

	ball = new Ball(app->screenSize.x / 2, app->screenSize.y - app->screenSize.y / 4, app->renderer);
	ball->setSpeed(100);

	vec2f brickSize = resourceManager->getTextureSize("GrayBrick");
	int numberOfBricksX = app->screenSize.x / brickSize.x - 1;
	int freeSpaceX = app->screenSize.x - brickSize.x * numberOfBricksX;

	int currentX = freeSpaceX / 2 + brickSize.x / 2;
	int currentY = brickSize.y;
	for (int j = 0; j < 15; ++j)
	{
		currentX = freeSpaceX / 2 + brickSize.x / 2;
		for (int i = 0; i < numberOfBricksX; ++i)
		{
			Brick brick(currentX, currentY, app->renderer);
			bricks.push_back(brick);
			currentX += brickSize.x;
		}
		currentY += brickSize.y;
	}
}

void GameManager::handleInput()
{
	SDL_Event event;
	SDL_GetMouseState(&app->mousePos.x, &app->mousePos.y);
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			exit(0);
			break;

		case SDL_EVENT_KEY_DOWN:
			doKeyDown(&event.key, app);
			break;

		case SDL_EVENT_KEY_UP:
			doKeyUp(&event.key, app);
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				ball->startMoving(app->mousePos);
			}
			break;

		default:
			break;
		}
	}
}

void GameManager::update(float deltaTime)
{
	OutOfScreenDirection PlayerOutOfScreenDirection = player->checkIfOutOfTheScreen(app->screenSize.x, app->screenSize.y);
	switch (PlayerOutOfScreenDirection)
	{
	case Right:
		if (app->left)
		{
			player->moveLeft(deltaTime);
		}
		break;
	case Left:
		if (app->right)
		{
			player->moveRight(deltaTime);
		}
		break;
	case NotOut:
		if (app->left)
		{
			player->moveLeft(deltaTime);
		}
		if (app->right)
		{
			player->moveRight(deltaTime);
		}
		break;
	}

	OutOfScreenDirection BallOutOfScreenDirection = ball->checkIfOutOfTheScreen(app->screenSize.x, app->screenSize.y);
	switch (BallOutOfScreenDirection)
	{
	case Left:
		ball->setPos(ball->getPos().x - 5 * ball->dx * deltaTime, ball->getPos().y + ball->dy * deltaTime);
		ball->dx = -ball->dx;
		break;
	case Right:
		ball->setPos(ball->getPos().x - 5 * ball->dx * deltaTime, ball->getPos().y + ball->dy * deltaTime);
		ball->dx = -ball->dx;
		break;
	case Up:
		ball->setPos(ball->getPos().x + ball->dx * deltaTime, ball->getPos().y - 5 * ball->dy * deltaTime);
		ball->dy = -ball->dy;
		break;
	case Down:
		printf("gameover");
		gameover = true;
		break;
	}

	if (ball->aabb.isCollided(&player->aabb))
	{
		ball->dy = -ball->dy;
	}
	for (Brick& brick : bricks)
	{
		if (ball->aabb.isCollided(&brick.aabb) && !brick.isDestroyed())
		{
			ball->dy = -ball->dy;
			brick.Damaged();
		}
	}

	player->animate(deltaTime);
	ball->move(deltaTime);
}

void GameManager::draw()
{
	for (Brick& brick : bricks)
	{
		if (!brick.isDestroyed())
		{
			brick.draw();
		}
	}
	player->draw();
	ball->draw();
	scoreManager->drawScore();
}

void GameManager::run()
{
	float timeElapsed = 0.0f;
	float deltaTime = 0.001f;

	while (!gameover) {
		auto start = std::chrono::steady_clock::now();

		prepareScene(app->renderer);
		handleInput();
		update(deltaTime);
		draw();
		presentScene(app->renderer);

		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		deltaTime = duration.count() / 1000.0f;
		timeElapsed += deltaTime;
	}
}

GameManager::~GameManager()
{
	delete player;
	delete ball;
}
