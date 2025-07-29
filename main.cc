#include <iostream>
#include <cmath>
#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "GameManager.hh"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

int main() 
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dorga");

	SetTargetFPS(60);

	GameManager gameManager = GameManager();

	while (!WindowShouldClose()) 
	{
		int width = GetScreenWidth();
		int height = GetScreenHeight();

		gameManager.Update(width, height);
		gameManager.Render(width, height);
	}

	CloseWindow();
}