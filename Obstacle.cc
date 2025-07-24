#include "Obstacle.hh"

Obstacle::Obstacle(Vector2 _position, float _rotation, float _scale, const Texture& _texture)
	: WorldObject(_position, _rotation, _scale, _texture)
{
	position = _position;
	rotation = _rotation;
	scale = _scale;

	texture = _texture;
}

int Obstacle::CheckPlayerCollision(const Vector2& playerPos, const float playerRadius) const
{
	if (CheckCollisionCircles(position, scale * OBSTACLE_RADIUS_SCALE_MULTIPLIER, playerPos, playerRadius)) return 0;
	return -1;
}

void Obstacle::Render()
{
	Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
	Rectangle destRec = {
		position.x - (texture.width * scale) / 2,
		position.y - (texture.height * scale) / 2,
		(float)texture.width * scale,
		(float)texture.height * scale
	};
	Vector2 origin = { 0, 0 };

	DrawTexturePro(texture, sourceRec, destRec, origin, 0, WHITE);

	if (DEBUG_SHOW_OBJECTS_HITBOX) DrawCircleLines(position.x, position.y, scale * OBSTACLE_RADIUS_SCALE_MULTIPLIER, RED);
}