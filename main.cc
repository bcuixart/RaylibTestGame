#include <iostream>
#include <cmath>
#include "raylib.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define DEG_TO_RAD  M_PI / 180

Vector2 playerPosition = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
float playerRotation = 0;
const float ROTATE_SPEED = 150;

Vector2 playerVelocity = { 0, 0 };

const float MAX_PLAYER_SPEED = 200.f;
const float ACCELERATION = 200.f;
const float DECELERATION = 100.f;
const float DECELERATION_STOP_TOLERANCE = 0.01f;

float deltaTime;

int main() 
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dorga");

	Texture playerTexture = LoadTexture("Assets/Player_Arrow.png");

	while (!WindowShouldClose()) 
	{
		deltaTime = GetFrameTime();

		ClearBackground({ 0, 82, 172, 255 });
		BeginDrawing();

		float rotationSin = std::sin(playerRotation * DEG_TO_RAD);
		float rotationCos = std::cos(playerRotation * DEG_TO_RAD);

		if (IsKeyDown(KEY_SPACE)) 
		{
			playerVelocity.x += ACCELERATION * rotationCos * deltaTime;
			playerVelocity.y += ACCELERATION * rotationSin * deltaTime;
		}
		else 
		{
			playerRotation = std::fmod(float(playerRotation + ROTATE_SPEED * deltaTime), float(360.f));
		}
		
		if (std::abs(playerVelocity.x) > DECELERATION_STOP_TOLERANCE) {
			if (playerVelocity.x > 0) playerVelocity.x -= DECELERATION * rotationCos * deltaTime;
			else playerVelocity.x += DECELERATION * rotationCos * deltaTime;
		}
		if (std::abs(playerVelocity.y) > DECELERATION_STOP_TOLERANCE) {
			if (playerVelocity.y > 0) playerVelocity.y -= DECELERATION * rotationSin * deltaTime;
			else playerVelocity.y += DECELERATION * rotationSin * deltaTime;
		}

		if (playerVelocity.x > MAX_PLAYER_SPEED) playerVelocity.x = MAX_PLAYER_SPEED;
		if (playerVelocity.x < -MAX_PLAYER_SPEED) playerVelocity.x = -MAX_PLAYER_SPEED;
		if (playerVelocity.y > MAX_PLAYER_SPEED) playerVelocity.y = MAX_PLAYER_SPEED;
		if (playerVelocity.y < -MAX_PLAYER_SPEED) playerVelocity.y = -MAX_PLAYER_SPEED;

		playerPosition.x += playerVelocity.x * deltaTime;
		playerPosition.y -= playerVelocity.y * deltaTime;

		if (playerPosition.x < 0) playerPosition.x = 500;
		if (playerPosition.x > 500) playerPosition.x = 0;
		if (playerPosition.y > 500) playerPosition.y = -23;
		if (playerPosition.y < -23) playerPosition.y = 500;

		//std::cout << playerRotation << std::endl;
		//std::cout << playerVelocity.x << ' ' << playerVelocity.y << std::endl;
		std::cout << playerPosition.x << ' ' << playerPosition.y << std::endl;

		DrawTexturePro(playerTexture,
			(Rectangle) { 0.0f, 0.0f, (float)playerTexture.width, (float)playerTexture.height },
			(Rectangle) { playerPosition.x, playerPosition.y, (float)playerTexture.width, (float)playerTexture.height },
			(Vector2) { (float)playerTexture.width* 1 / 2, (float)playerTexture.height* 1 / 2 },
			-playerRotation + 90,
			WHITE);

		EndDrawing();
	}

	CloseWindow();
}