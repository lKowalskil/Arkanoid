#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <Entity.h>
#include <App.h>
#include <Math.h>
#include <Player.h>
#include <Ball.h>
#include <ResourceManager.h>
#include <Brick.h>
#include <SDL3/SDL_ttf.h>
#include <ScoreManager.h>
#include <chrono>
#include <numeric>
#include <BonusScore.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

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
void doInput(App* app)
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
					app->ball->startMoving(app->mousePos);
				}
				break;

			default:
				break;
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

int main()
{
	float timeElapsed = 0.0f;
	float deltaTime = 0.001f;
	App app(SCREEN_WIDTH, SCREEN_HEIGHT);
	ResourceManager& resourceManager = ResourceManager::getInstance();
	resourceManager.init(app.renderer);

	ScoreManager& scoreManager = ScoreManager::getInstance();
	scoreManager.init(app.renderer, 15, SCREEN_HEIGHT - 45);
	
	vec2f brickSize = resourceManager.getTextureSize("GrayBrick");
	int numberOfBricksX = SCREEN_WIDTH / brickSize.x - 1;
	int freeSpaceX = SCREEN_WIDTH - brickSize.x * numberOfBricksX;

	std::vector<Brick> bricks;
	int currentX = freeSpaceX / 2 + brickSize.x / 2;
	int currentY = brickSize.y;
	for (int j = 0; j < 15; ++j)
	{
		currentX = freeSpaceX / 2 + brickSize.x / 2;
		for (int i = 0; i < numberOfBricksX; ++i)
		{
			Brick brick(currentX, currentY, app.renderer);
			bricks.push_back(brick);

			currentX += brickSize.x;
		}
		currentY += brickSize.y;
	}

	Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 5, app.renderer);
	app.player = &player;
	Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4, app.renderer);
	app.ball = &ball;
	player.setSpeed(150);
	ball.setSpeed(100);

	while (1)
	{
		auto start = std::chrono::steady_clock::now();
		prepareScene(app.renderer);
		doInput(&app);
		if (player.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 2)
		{
			if (app.left)
			{
				player.moveLeft(deltaTime);
			}
		} 
		else if (player.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 1)
		{
			if (app.right)
			{
				player.moveRight(deltaTime);
			}
		}
		else
		{
			if (app.left)
			{
				player.moveLeft(deltaTime);
			}
			if (app.right)
			{
				player.moveRight(deltaTime);
			}
		}

		if (ball.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 1 || 
			ball.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 2)
		{
			ball.setPos(ball.getPos().x - 5 * ball.dx * deltaTime, ball.getPos().y + ball.dy * deltaTime);
			ball.dx = -ball.dx;
		}
		if (ball.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 3)
		{
			ball.setPos(ball.getPos().x + ball.dx * deltaTime, ball.getPos().y - 5 * ball.dy * deltaTime);
			ball.dy = -ball.dy;
		}
		if (ball.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 4)
		{
			printf("gameover");
			break;
		}

		if (ball.aabb.isCollided(&player.aabb))
		{
			ball.dy = -ball.dy;
		}
		


		for (Brick& brick : bricks)
		{
			if (ball.aabb.isCollided(&brick.aabb) && !brick.isDestroyed())
			{
				ball.dy = -ball.dy;
				brick.Damaged();
			}
		}

		ball.move(deltaTime);

		player.animate(deltaTime);

		ball.draw(app.renderer);
		player.draw(app.renderer);
		scoreManager.drawScore();

		presentScene(app.renderer);

		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		deltaTime = duration.count() / 1000.0f;
		timeElapsed += deltaTime;
	}
	return 0;
}