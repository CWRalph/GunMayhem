#include "pch.h"
#include "Grenade.h"

extern unordered_map<string, Sound> sounds;

bool Grenade::update()
{
	if (!*isActive) return false;

	if (*onPlatform)
	{
		if (*horizontalVelocity > 0)
		{
			*horizontalVelocity -= FRICTION * dt;
			if (*horizontalVelocity < 0) *horizontalVelocity = 0;
		}

		if (*horizontalVelocity < 0)
		{
			*horizontalVelocity += FRICTION * dt;
			if (*horizontalVelocity > 0) *horizontalVelocity = 0;
		}
	}
		
		collider->x += *horizontalVelocity * dt;
		*fuse -= dt;
	if (*fuse > 0) 	return false;

	PlaySoundMulti(sounds[K_EXPLOSION_SOUND]);
	return true;
}



void Grenade::Draw(const float& scale) const
{
	if (!*doDraw) return;

	DrawTextureEx(textures[K_GRENADE], { collider->x, collider->y }, 0.f, scale, WHITE);
}

void Grenade::Gravity()
{
	*verticalVelocity += GRAVITY * 0.75f * dt;
	collider->y += *verticalVelocity * dt;
}
