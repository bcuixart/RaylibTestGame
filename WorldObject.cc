#include "WorldObject.hh"

WorldObject::WorldObject(Vector2 _position, float _rotation, float _scale) 
{
	position = _position;
	rotation = _rotation;
	scale = _scale;
}

Vector2 WorldObject::getPosition() const
{
	return position;
}

float WorldObject::getRotation() const
{
	return rotation;
}

float WorldObject::getScale() const
{
	return scale;
}

void WorldObject::Update() 
{

}

void WorldObject::Render() 
{

}