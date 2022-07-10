#pragma once
#include "Utils/Defines.h"

extern std::unordered_map<string, Texture2D> textures;
extern const float UI_xPos[4];

class CBanners
{
	std::map<string, Rectangle> colliders;
	short playerNum;

public:
	CBanners(const short& playerNumber) : playerNum(playerNumber)
	{
		float y = 170.f;	
		colliders.insert({ CBAN_JUMP ,{UI_xPos[playerNum - 1] + 109 - 35, 75.f + y - 20.f, 50.f, 50.f} });
		colliders.insert({ CBAN_DROP ,{UI_xPos[playerNum - 1] + 109 - 35, 75 + 50.f + y, 50.f, 50.f} });
		colliders.insert({ CBAN_RIGHT ,{UI_xPos[playerNum - 1] + 109 + 54 - 35, 75 + 50.f + y, 50.f, 50.f} });
		colliders.insert({ CBAN_LEFT ,{UI_xPos[playerNum - 1] + 54 - 35, 75 + 50.f + y, 50.f, 50.f} });
		colliders.insert({ CBAN_SHOOT ,{UI_xPos[playerNum - 1] + 50, 75 + 250.f + 125, 50.f, 50.f} });
		colliders.insert({ CBAN_BOMB ,{UI_xPos[playerNum - 1] + 50 + 54, 75 + 250.f + 125, 50.f, 50.f} });
		
	}

	void Draw(const Rectangle& mouse, const bool& k) const;
	inline const std::map<string, Rectangle>& GetColliders() const { return colliders; }
};