#include <iostream>
#include <cmath>
#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "Player.hh"
#include "Camera.hh"
#include "Coin.hh"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

float generateRandomFromSeed(const Vector2& pos, unsigned int seed) {
	unsigned int hash = seed;

	hash ^= static_cast<unsigned int>(pos.x * 1000);
	hash ^= static_cast<unsigned int>(pos.y * 1000);

	hash = (hash ^ (hash >> 16)) * 0x45d9f3b;
	hash = (hash ^ (hash >> 16)) * 0x45d9f3b;
	hash = hash ^ (hash >> 16);

	return (static_cast<float>(hash) / std::numeric_limits<unsigned int>::max());
}

int main() 
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dorga");

	Player player = Player();
	CameraManager camera = CameraManager();

	/*
	vector<Coin> coins;
	for (int i = -1000; i < 1000; i += 100) {
		for (int j = -1000; j < 1000; j += 100) {
			Vector2 pos = { float(i), float(j) };
			if (generateRandomFromSeed(pos, 0) < 0.1f) coins.push_back(Coin(pos));
		}
	}
	*/

	while (!WindowShouldClose()) 
	{
		float deltaTime = GetFrameTime();

		player.Update(deltaTime);
		//for (int i = 0; i < coins.size(); ++i) coins[i].Update();

		ClearBackground({ 0, 82, 172, 255 });
		BeginDrawing();

		camera.Update(player.getPlayerPosition(), GetScreenWidth(), GetScreenHeight(), deltaTime);
		camera.MBeginMode2D();

		player.Render();
		//for (int i = 0; i < coins.size(); ++i) coins[i].Render();

		EndDrawing();
		EndMode2D();

		DrawFPS(0, 0);
	}

	CloseWindow();
}