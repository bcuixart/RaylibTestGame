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

	GameManager gameManager = GameManager();

	while (!WindowShouldClose()) 
	{
		gameManager.Update();
		gameManager.Render();
	}

	CloseWindow();
}