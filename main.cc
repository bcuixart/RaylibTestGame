#include <iostream>
#include <cmath>
#include "raylib.h"
#include "raymath.h"

#include "Player.hh"
#include "Camera.hh"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

int main() 
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dorga");

	Player player = Player();
	CameraManager camera = CameraManager();

	while (!WindowShouldClose()) 
	{
		float deltaTime = GetFrameTime();

		player.Update(deltaTime);

		ClearBackground({ 0, 82, 172, 255 });
		BeginDrawing();

		camera.Update(player.getPlayerPosition(), GetScreenWidth(), GetScreenHeight(), deltaTime);
		camera.MBeginMode2D();

		player.Render();

		EndDrawing();
		EndMode2D();
	}

	CloseWindow();
}