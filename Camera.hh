#ifndef CAMERA_HH
#define CAMERA_HH

#include <iostream>

#include "raylib.h"
#include "raymath.h"

using namespace std;

class CameraManager {
public:
	CameraManager();

	void Update(Vector2 playerPosition, int screenWidth, int screenHeight, float deltaTime);

	void Start();

	void MBeginMode2D();

	Vector2 getCameraPosition();

protected:

private:
	Camera2D camera = { 0 };

	Vector2 cameraPosition = { 0,0 };

	const float CAMERA_FAST_DISTANCE = 50;
	const float CAMERA_SPEED_SLOW = 150;
	const float CAMERA_SPEED_FAST = 300;

	float cameraSpeed;
};

#endif