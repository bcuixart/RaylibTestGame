#ifndef WORLDOBJECT_HH
#define WORLDOBJECT_HH

#include <iostream>

#include "raylib.h"
#include "raymath.h"

using namespace std;

class WorldObject {
public:
	WorldObject(Vector2 _position, float _rotation, float _scale);
	virtual ~WorldObject() = default;

	virtual void Update();
	virtual void Render();

	Vector2 getPosition() const;
	float getRotation() const;
	float getScale() const;

protected:
	Vector2 position;
	float rotation;
	float scale;

private:

};

#endif