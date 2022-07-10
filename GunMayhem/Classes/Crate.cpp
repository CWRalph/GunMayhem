#include "pch.h"
#include "Crate.h"

bool Crate::Update()
{
	*lifespan -= dt;
	if (*lifespan <= 0) return true;
	return false;
}

void Crate::Gravity()
{
	*verticalVel += GRAVITY * dt;
	if (*verticalVel > 1000.f) *verticalVel = 1000.f;
	collider->y += *verticalVel * dt;
}

void Crate::Draw() const
{
	DrawTexture(textures[K_CRATE], (int)collider->x, (int)collider->y, WHITE);
}