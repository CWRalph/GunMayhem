#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(const string& gunName, const float& x, const float& y)
{
	string buffer = "", temp = GetLine(GetLineFromWord("TextFiles/Bullets", gunName), "TextFiles/Bullets");
	short counter = 0;
	std::stringstream ss(temp);
	while (ss >> buffer)
	{
		++counter;
		switch (counter)
		{
			case 2:
			{
				speed = new float((stof(buffer) * 1.2f) + MAX_PLAYER_SPEED + 10);
			} break;
			case 3:
			{
				collider = new Rectangle({ x, y, stof(buffer), (float)textures["Bullet"].height });
			} break;
			case 4:
			{
				float dmg = stof(buffer);
				float mul = 5.f;
				if (dmg < 25.f) mul = 10.f;
				if (dmg > 69.f) mul = 8.5f;
				knockback = new const float(dmg * mul);
			} break;
			case 5:
			{
				soundKey = new string(buffer);
			} break;
			case 6:
			{
				*lifespan = stof(buffer);
			} break;
		}
	}
	if (!(knockback && speed && lifespan && collider && soundKey))
		TraceLog(LOG_WARNING, "BULLET: missing critical data");
}

const float Bullet::getKnockback() const
{
	if (*direction == Direction::Right) return *knockback;
	else return -(*knockback);
}

void Bullet::setDirection(const Direction& d)
{
	 *direction = d;
	 if (d == Direction::Right) *speed = abs(*speed);
	 else *speed = -abs(*speed);
}

void Bullet::setPosition(const float& x, const float& y)
{
	collider->x = x;
	collider->y = y;
}

const bool& Bullet::update()
{
	*lifespan -= dt;
	collider->x += *speed * dt;

	if (*lifespan <= 0 || collider->x > screenWidth + 200 || collider->x < -200)
		*isActive = false;

	return *isActive;
}

void Bullet::Draw() const
{
	DrawTextureRec(textures[K_BULLET], {0,0, collider->width, collider->height}, { collider->x, collider->y }, WHITE);
}
