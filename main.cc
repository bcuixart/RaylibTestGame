#include <iostream>
#include <cmath>
#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "Player.hh"
#include "Camera.hh"
#include "World.hh"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

void StartGame(Player& player, World& world, CameraManager& camera) 
{
	world.ClearWorld();
	world.Start(0);
	player.Start();
	camera.Start();
}

int main() 
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dorga");

	Player player = Player();
	CameraManager camera = CameraManager();

	World world = World();

	StartGame(player, world, camera);

	float playerRadius = player.getPlayerRadius();

	while (!WindowShouldClose()) 
	{
		float deltaTime = GetFrameTime();

		int playerInfo = player.Update(deltaTime);
		if (playerInfo == 1) {
			StartGame(player, world, camera); // Restart if dead
		}

		int playerDied = world.Update(player.getPlayerPosition(), playerRadius);
		if (playerDied) player.KillPlayer();

		ClearBackground({ 133, 60, 217, 255 });
		BeginDrawing();

		camera.Update(player.getPlayerPosition(), GetScreenWidth(), GetScreenHeight(), deltaTime);
		camera.MBeginMode2D();

		player.Render();
		world.Render();

		EndDrawing();
		EndMode2D();

		DrawFPS(0, 0);
	}

	CloseWindow();
}