#include "pch.h"
#include "Explosion.h"

void Explosion::Draw() const
{
	DrawCircleLines(centerPos->x, centerPos->y, *radius, RED);
}

bool Explosion::update()
{
	*lifespan -= dt;
	if (*lifespan <= 0) return true;
	return false;
}
