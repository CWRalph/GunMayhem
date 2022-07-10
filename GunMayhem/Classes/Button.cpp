#include "pch.h"
#include "Button.h"
#include "Utils/Utils.h"
#include "Utils/Defines.h"

void Button::Draw(const float& scale, const Color& c) const
{
	DrawTextureEx(*skin, { collider->x, collider->y }, 0.f, scale, c);
}

