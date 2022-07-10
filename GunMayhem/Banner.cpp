#include "pch.h"
#include "Banner.h"

extern bool name;

void Banner::Draw(const Player& p, const Rectangle& mouse)
{
	DrawTexture(textures[K_PL_SETUP_BANNER_OUTLINE], colliders[K_PL_SETUP_BANNER_OUTLINE].x, colliders[K_PL_SETUP_BANNER_OUTLINE].y, WHITE);
	DrawTexture(textures[K_PL_SETUP_NAME_BOX], colliders[K_PL_SETUP_NAME_BOX].x, colliders[K_PL_SETUP_NAME_BOX].y, WHITE);	
	DrawTexture(textures[K_BANNER_CLEAR_SLOT], colliders[K_BANNER_CLEAR_SLOT].x, colliders[K_BANNER_CLEAR_SLOT].y, WHITE);
	DrawRectangle(colliders[K_BANNER_COLOR].x, colliders[K_BANNER_COLOR].y, colliders[K_BANNER_COLOR].width, colliders[K_BANNER_COLOR].height, p.GetColor());
	DrawRectangleLines(colliders[K_BANNER_COLOR].x, colliders[K_BANNER_COLOR].y, colliders[K_BANNER_COLOR].width, colliders[K_BANNER_COLOR].height, BLACK);
	DrawTextEx(fonts[K_UI_FONT], p.GetName().c_str(), { colliders[K_PL_SETUP_NAME_BOX].x + 12.f, colliders[K_PL_SETUP_NAME_BOX].y + 20.f }, 15.f, 1.f, BLACK);

	DrawTextureEx(textures[p.GetPistol().GetName()], { colliders[K_BANNER_COLOR].x, colliders[K_BANNER_COLOR].y + 90.f }, 0.f, 1.75f, WHITE);
	DrawTexture(p.GetPerk().getButton().getSkin(), colliders[K_BANNER_COLOR].x, colliders[K_BANNER_COLOR].y + 75.f + 75.f, WHITE);
	DrawTexture(textures[K_PLAYER], colliders[K_PL_SETUP_NAME_BOX].x + 10, 290, p.GetColor());

	if (CheckCollisionRecs(mouse, colliders[K_BANNER_CLEAR_SLOT]))
		DrawRectangle(colliders[K_BANNER_CLEAR_SLOT].x, colliders[K_BANNER_CLEAR_SLOT].y, colliders[K_BANNER_CLEAR_SLOT].width, colliders[K_BANNER_CLEAR_SLOT].height, { 165, 165 ,165 , 165 });
	else if (CheckCollisionRecs(mouse, colliders[K_BANNER_COLOR]))
		DrawTextEx(fonts[K_UI_FONT], "COLOR", { colliders[K_BANNER_COLOR].x, colliders[K_BANNER_COLOR].y + 60 }, 15.f, 1.f, BLACK);
	else if (CheckCollisionRecs(mouse, colliders[K_BANNER_GUN]))
		DrawTextEx(fonts[K_UI_FONT], "GUN", { colliders[K_BANNER_COLOR].x + 10, colliders[K_BANNER_COLOR].y + 130.f }, 15.f, 1.f, BLACK);
	else if (CheckCollisionRecs(mouse, colliders[K_BANNER_PERK]))
		DrawTextEx(fonts[K_UI_FONT], "PERK", { colliders[K_BANNER_COLOR].x + 12, colliders[K_BANNER_COLOR].y + 75.f + 75.f + 60.f }, 15.f, 1.f, BLACK);	

	if (p.GetPlayerType() == PlayerType::AI)
		DrawTextEx(fonts[K_UI_FONT_BOLD], "BOT", { colliders[K_PL_SETUP_BANNER_OUTLINE].x + 50.f,  colliders[K_PL_SETUP_BANNER_OUTLINE].y + 60.f }, 35.f, 1.f, ORANGE);
		

		
	/*if (CheckCollisionRecs(mouse, colliders[K_PL_SETUP_NAME_BOX]))
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
	else SetMouseCursor(MOUSE_CURSOR_DEFAULT);*/
}

void Banner::Draw()
{
	DrawTexture(textures[K_PL_SETUP_EMPTY_BANNER], colliders[K_PL_SETUP_BANNER_OUTLINE].x, colliders[K_PL_SETUP_BANNER_OUTLINE].y, WHITE);
}
