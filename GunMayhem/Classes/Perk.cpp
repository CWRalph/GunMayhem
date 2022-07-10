#include "pch.h"
#include "Perk.h"

extern unordered_map<string, Font> fonts;

void Perk::Draw(const Rectangle& pointer) const
{
	float scale = 1.f;
	if (CheckCollisionRecs(pointer, button->getCollider()))
	{
		scale = 1.5;
		DrawTextEx(fonts[K_UI_FONT], name, { 400.f, 550.f }, 25.f, 1.f, WHITE);
	}		
	button->Draw(scale);
}
