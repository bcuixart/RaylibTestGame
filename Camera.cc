#include "Camera.hh"

CameraManager::CameraManager()
{

}

void CameraManager::Update(Vector2 playerPosition, int screenWidth, int screenHeight, float deltaTime)
{
	camera = { 0 };

	camera.target = playerPosition;
	camera.offset = (Vector2){ float(screenWidth / 2), float(screenHeight / 2) };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
}

void CameraManager::MBeginMode2D()
{
	BeginMode2D(camera);
}