#pragma once
#include "Utils/Defines.h"
#include "Classes/Player.h"

extern unordered_map<string, Texture2D> textures;
class Banner
{
	unordered_map<string, Rectangle> colliders;

public:
	Banner(const float& x, const float& y)
	{
		colliders.insert({ K_PL_SETUP_BANNER_OUTLINE, { x, y, (float)textures[K_PL_SETUP_BANNER_OUTLINE].width, (float)textures[K_PL_SETUP_BANNER_OUTLINE].height } });
		colliders.insert({ K_BANNER_CLEAR_SLOT, { x + 20.f, y + 12.f, (float)textures[K_BANNER_CLEAR_SLOT].width, (float)textures[K_BANNER_CLEAR_SLOT].height } });
		colliders.insert({ K_BANNER_AI_CREATE, {x + 15.f, y + 180.f, 165.f, 27.f } });
		colliders.insert({ K_BANNER_PLAYER_CREATE, {x + 15.f, y + 140.f, 165.f, 27.f } });
		colliders.insert({ K_PL_SETUP_NAME_BOX, { x + 12.f, y + 335.f, (float)textures[K_PL_SETUP_NAME_BOX].width, (float)textures[K_PL_SETUP_NAME_BOX].height + 15 } });
		colliders.insert({ K_BANNER_COLOR, {x + 125.f, y + 100.f, 50.f, 50.f} });
		colliders.insert({ K_BANNER_GUN, {x + 125.f, y + 190.f, 65.f, 35.f} });
		colliders.insert({ K_BANNER_PERK, {x + 125.f, y + 100.f + 75.f + 75.f, 65.f, 65.f} });
	}

	Banner(const Banner& b)
	{
		colliders = b.colliders;
	}

	~Banner() {}
	
	const unordered_map<string, Rectangle>& GetColliders() const { return colliders; }
	void Draw(const Player& p, const Rectangle& mouse);
	void Draw();
};

