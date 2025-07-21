#include "Coin.hh"

Coin::Coin(Vector2 _position, float _rotation, float _scale)
	: WorldObject(_position, _rotation, _scale)
{
	position = _position;
	rotation = _rotation;
	scale = _scale;
}