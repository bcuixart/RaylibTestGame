#ifndef GAMEMANAGER_HH
#define GAMEMANAGER_HH

#include <iostream>
#include <random>

#include "raylib.h"
#include "raymath.h"

#include "Player.hh"
#include "Camera.hh"
#include "World.hh"

using namespace std;

class GameManager {
public:
	GameManager();

	void Update();
	void Render();

protected:

private:
	void StartGame();

	Player player;
	CameraManager camera;
	World world;

	float playerRadius;

	const bool DEBUG_PRINT_SEED = false;
};

#endif