#include "pch.h"
#include "Level.h"

void Level::Draw() const
{
	//Draw background
	DrawTexture(textures[BG], 0, 0, WHITE);

	//Draw platforms
	for (const auto& p : platforms)
		DrawTextureRec(textures[Platform], {0,0, p.width,(float)textures[Platform].height }, { p.x, p.y - textures[Platform].height * 0.5f}, WHITE);
}
