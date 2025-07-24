#ifndef OBSTACLE_HH
#define OBSTACLE_HH

#include <iostream>

#include "raylib.h"
#include "raymath.h"

#include "WorldObject.hh"

using namespace std;

class Obstacle : public WorldObject {
public:
	Obstacle(Vector2 _position, float _rotation, float _scale, const Texture& _texture);

	virtual void Render();

	virtual int CheckPlayerCollision(const Vector2& playerPos, const float playerRadius) const;

protected:

private:
	const float OBSTACLE_RADIUS_SCALE_MULTIPLIER = 250;

	const bool DEBUG_PLAYER_INVINCIBLE = false;
};

#endif