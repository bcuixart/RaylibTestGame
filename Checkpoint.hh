#ifndef CHECKPOINT_HH
#define CHECKPOINT_HH

#include <iostream>

#include <raylib.h>
#include <raymath.h>

#include "WorldObject.hh"

using namespace std;

class Checkpoint : public WorldObject {
public:
	Checkpoint(Vector2 _position, float _rotation, float _scale, const vector<Texture>& _textures);

	virtual void Update(const float deltaTime);
	virtual void Render();

	virtual int CheckPlayerCollision(const Vector2& playerPos, const float playerRadius) const;
	void Collect();

protected:

private:
	const float CHECKPOINT_ROTATE_SPEED = 10;

	const float CHECKPOINT_RADIUS_SCALE_MULTIPLIER = 500;
};

#endif