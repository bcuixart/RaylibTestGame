#ifndef OBSTACLE_HH
#define OBSTACLE_HH

#include <iostream>

#include "raylib.h"
#include "raymath.h"

#include "WorldObject.hh"

using namespace std;

class Obstacle : public WorldObject {
public:
	Obstacle(Vector2 _position, float _rotation, float _scale, const vector<Texture>& _textures);

	virtual void Update(const float deltaTime);
	virtual void Render();

	virtual int CheckPlayerCollision(const Vector2& playerPos, const float playerRadius) const;

protected:

private:
	const float OBSTACLE_RADIUS_SCALE_MULTIPLIER = 67;

	const bool DEBUG_PLAYER_INVINCIBLE = false;

	float currentTexture = 0;

	const Color COLOR_BASE = { 190, 130, 237, 255 };
	const Color COLOR_CRATERS = { 150, 76, 225, 255 };

	const float ANIMATION_SPEED = 20;
};

#endif