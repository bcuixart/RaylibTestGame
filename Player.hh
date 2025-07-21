#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>

#include "raylib.h"
#include "raymath.h"

#define DEG_TO_RAD  M_PI / 180

using namespace std;

class Player {
public:
	Player();

	void Update(float deltaTime);
	void Render();

	Vector2 getPlayerPosition() const;

protected:

private:
	Vector2 playerPosition = { 0, 0 };
	float playerRotation = 0;

	Vector2 playerVelocity = { 0, 0 };

	const float MAX_PLAYER_SPEED = 300.f;
	const float ACCELERATION = 350.f;
	const float DECELERATION = 100.f;
	const float DECELERATION_STOP_TOLERANCE = 0.01f;
	const float ROTATE_SPEED = -300;

	Texture playerTexture = LoadTexture("Assets/Player_Arrow.png");
	bool drawDirectionPoints = false;

	const bool DEBUG_PRINT_POS = false;
	const bool DEBUG_PRINT_ROT = false;
	const bool DEBUG_PRINT_VEL = false;
};

#endif