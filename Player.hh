#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>

#include "raylib.h"
#include "raymath.h"

#define DEG_TO_RAD  M_PI / 180

#define BODY_PARTS_TEXTURES 6
#define FIRE_TEXTURES 14
#define FIRE_ACCELERATE_TEXTURES 4
#define FIRE_MOVING_TEXTURES 10

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

	const Texture playerBodyTextures[BODY_PARTS_TEXTURES] = {
		LoadTexture("Assets/Textures/Player_Body_Main.png"),
		LoadTexture("Assets/Textures/Player_Body_Window.png"),
		LoadTexture("Assets/Textures/Player_Body_Propeller_000.png"),
		LoadTexture("Assets/Textures/Player_Body_Propeller_001.png"),
		LoadTexture("Assets/Textures/Player_Body_Propeller_002.png"),
		LoadTexture("Assets/Textures/Player_Body_Top.png"),
	};
	const Color playerBodyColors[BODY_PARTS_TEXTURES] = {
		{ 213, 167, 247, 255 },
		{ 189, 129, 237, 255 },
		{ 189, 129, 237, 255 },
		{ 189, 129, 237, 255 },
		{ 189, 129, 237, 255 },
		{ 189, 129, 237, 255 },
	};
	const int textureWidth = playerBodyTextures[0].width;
	const int textureHeight = playerBodyTextures[0].height;

	const Texture fireTextures[FIRE_TEXTURES] = {
		LoadTexture("Assets/Textures/Player_Fire_Accelerate_000.png"),
		LoadTexture("Assets/Textures/Player_Fire_Accelerate_001.png"),
		LoadTexture("Assets/Textures/Player_Fire_Accelerate_002.png"),
		LoadTexture("Assets/Textures/Player_Fire_Accelerate_003.png"),
		LoadTexture("Assets/Textures/Player_Fire_Moving_000.png"),
		LoadTexture("Assets/Textures/Player_Fire_Moving_001.png"),
		LoadTexture("Assets/Textures/Player_Fire_Moving_002.png"),
		LoadTexture("Assets/Textures/Player_Fire_Moving_003.png"),
		LoadTexture("Assets/Textures/Player_Fire_Moving_004.png"),
		LoadTexture("Assets/Textures/Player_Fire_Moving_005.png"),
		LoadTexture("Assets/Textures/Player_Fire_Moving_006.png"),
		LoadTexture("Assets/Textures/Player_Fire_Moving_007.png"),
		LoadTexture("Assets/Textures/Player_Fire_Moving_008.png"),
		LoadTexture("Assets/Textures/Player_Fire_Moving_009.png"),
	};
	const Color playerFireColor = { 229, 197, 247, 255 };
	float currentFireTexture = -1;

	const float FIRE_TEXTURE_SPEED = 10;

	bool drawDirectionPoints = false;

	const bool DEBUG_PRINT_POS = false;
	const bool DEBUG_PRINT_ROT = false;
	const bool DEBUG_PRINT_VEL = false;

	const bool DEBUG_PRINT_FIRE_TEXTURE = true;
	
	const bool DEBUG_SHOW_HITBOX = false;
};

#endif