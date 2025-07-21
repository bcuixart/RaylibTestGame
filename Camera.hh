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

	void MBeginMode2D();

protected:

private:
	Camera2D camera = { 0 };

	Vector2 cameraPosition = { 0,0 };
	float cameraSpeed = 300.0f;
};

#endif