#pragma once
#include "pch.h"
#include "Utils/VariableType.h"

static int Random(int max = 100, int min = 0, const vector<int>& exclude = {})
{	
	++max;
	if (max == 0) return 0;
	if (min > 0) --min;
	unsigned int size = (unsigned int)exclude.size(), result = 0;
	bool isValid = true;
	do
	{
		isValid = true;
		std::random_device rd;
		std::mt19937 gen(rd());
		int t = gen();
		if (t < 0) t *= -1;
		result = (t % (max - min)) + min;
		for (unsigned i = 0; i < size; i++)
			if (result == exclude[i]) { isValid = false; break; }
	} while (!isValid);

	return result;
}

static void DrawRectangle(const Rectangle& r, const Color& color = {165, 165, 165, 165})
{
	DrawRectangle(r.x, r.y, r.width, r.height, color);
}

static void DrawRectangleLines(const Rectangle& r, const Color& color = RED)
{
	DrawRectangleLines(r.x, r.y, r.width, r.height, color);
}

static const bool WithinHorizontalPosition(const Rectangle& platform, const Vector2& playerVec)
{
	if ((playerVec.x + playerVec.y) < platform.x || playerVec.x> (platform.x + platform.width)) return false;
	return true;
}

