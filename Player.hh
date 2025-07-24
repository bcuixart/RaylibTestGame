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

	int Update(float deltaTime);
	void Render();

	void Start();

	void KillPlayer();

	Vector2 getPlayerPosition() const;
	float getPlayerRadius() const;

protected:

private:
	enum PlayerState { WaitingToStart, Playing, Dead };

	PlayerState currentState = WaitingToStart;

	Vector2 playerPosition = { 0, 0 };
	float playerRotation = 0;

	Vector2 playerVelocity = { 0, 0 };

	const float MAX_PLAYER_SPEED = 300.f;
	const float ACCELERATION = 350.f;
	const float DECELERATION = 100.f;
	const float DECELERATION_STOP_TOLERANCE = 0.01f;
	const float ROTATE_SPEED = -300;

	const float HITBOX_RADIUS = 12;

	const Texture playerTextures[2] = { 
		LoadTexture("Assets/Player_Rocket_001.png"),
		LoadTexture("Assets/Player_Rocket_002.png"),
	};
	int textureWidth = playerTextures[0].width;
	int textureHeight = playerTextures[0].height;
	int currentPlayerTexture = 0;

	bool drawDirectionPoints = false;

	const bool DEBUG_PRINT_POS = false;
	const bool DEBUG_PRINT_ROT = false;
	const bool DEBUG_PRINT_VEL = false;
	
	const bool DEBUG_SHOW_HITBOX = false;
};

#endif