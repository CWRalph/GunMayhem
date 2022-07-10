#include "pch.h"
#include "Controls.h"
#include "Utils/Utils.h"
#include "Utils/IO.h"

extern unordered_map<string, Font> fonts;
extern vector<vector<string>> Ckeys;

void CBanners::Draw(const Rectangle& mouse, const bool& k) const
{ 
	short j = 0;
	DrawTextEx(fonts[K_UI_FONT_BOLD], ("Player " + to_string(playerNum)).c_str(), { UI_xPos[playerNum - 1], 110.f }, 40.f, 1.5f, ORANGE);
	DrawTexture(textures[K_PL_SETUP_BANNER_OUTLINE], UI_xPos[playerNum - 1], 150, WHITE);
	for (const auto& b : colliders)
	{
		DrawRectangle(b.second);
		if (!k && CheckCollisionRecs(mouse, b.second))
			DrawRectangle(b.second, { 255,255,255,165 });

		DrawRectangleLines(b.second, BLACK);
		DrawTextEx(fonts[K_UI_FONT], Ckeys[playerNum - 1][j].c_str(), { b.second.x + 3, b.second.y + 20 }, 15.f, 1.f, BLACK);
		DrawTextEx(fonts[K_UI_FONT], b.first.substr(1).c_str(), { b.second.x, b.second.y - 15.f }, 12.f, 1.f, GRAY);
		++j;
	}
}