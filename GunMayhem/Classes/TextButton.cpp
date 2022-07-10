#include "pch.h"
#include "TextButton.h"

void TextButton::Draw(const Rectangle& mouse) const
{
	if (CheckCollisionRecs(mouse, *collider))
	{
		//DrawRectangleLines(*collider, RED);
		DrawRectanglePro({ -100,collider->y+(collider->height*1.75f),screenWidth*2,(collider->height*1.5f) }, { 0,0 }, *rotation, { 75,75,75,200 });
		if (secondaryText) DrawTextPro(fonts[*fontKey] , (*secondaryText).c_str(), {50,collider->y + (2 * collider->height)}, {0,0}, *rotation, (*fontSize / 2), 2, WHITE);
	}
	DrawTextPro(fonts[*fontKey], (*text).c_str(), { collider->x,collider->y }, { 0,0 }, *rotation, *fontSize, 2, WHITE);
}
