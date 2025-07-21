#ifndef COIN_HH
#define COIN_HH

#include <iostream>

#include "raylib.h"
#include "raymath.h"

#include "WorldObject.hh"

using namespace std;

class Coin : public WorldObject {
public:
	Coin(Vector2 _position, float _rotation, float _scale);

protected:

private:

};

#endif