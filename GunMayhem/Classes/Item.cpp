#include "pch.h"
#include "Item.h"

void Item::Draw() const
{	
	if (type != VariableType::Undefined)
		DrawCircle(collider.x + (collider.width * 0.5f), collider.y + (collider.height * 0.5f), collider.height * 0.5f, { 50, 50, 50, 95 });
	DrawTexture(textures[keyValue], collider.x, collider.y, WHITE);
}

void Item::Update()
{
	if (type == VariableType::Undefined) return;

	timer -= dt;
	if (timer <= 0)
	{
		type = VariableType::Undefined;
		keyValue = K_ITEM_UNDEFINED;
	}	
}
