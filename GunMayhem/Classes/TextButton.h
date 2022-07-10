#pragma once
#include "Utils/Utils.h"
#include "Utils/Defines.h"

extern std::unordered_map<string, Font> fonts;

class TextButton
{
private:
	Rectangle* collider = new Rectangle();
	string* text = new string();
	string* secondaryText = new string();
	string* fontKey = new string();
	float* rotation = new float();
	float* fontSize = new float();

public:
	TextButton() {}
	//Constructor starting from right side of screen
	TextButton(const float& y, const string& f, const float& rot, const float& size, const string& msg)
	{
		secondaryText = nullptr;
		*fontKey = f;
		*text = msg;
		*rotation = rot;
		*fontSize = size;
		Vector2 vec = MeasureTextEx(fonts[*fontKey], (*text).c_str(), *fontSize, 2);
		*collider = {(screenWidth - vec.x - 50), y, vec.x, vec.y};
	}
	TextButton(const float& y, const string& f, const float& rot, const float& size, const string& msg, const string& leftmsg)
	{
		*fontKey = f;
		*text = msg;
		*rotation = rot;
		*fontSize = size;
		*secondaryText = leftmsg;
		Vector2 vec = MeasureTextEx(fonts[*fontKey], (*text).c_str(), *fontSize, 2);
		*collider = { (screenWidth - vec.x - 50), y, vec.x, vec.y };
	}
	//Constructor with x position
	TextButton(const float& x, const float& y, const string& f, const float& rot, const float& size, const string& msg)
	{
		*fontKey = f;
		secondaryText = nullptr;
		*text = msg;
		*rotation = rot;
		*fontSize = size;
		Vector2 vec = MeasureTextEx(fonts[*fontKey], (*text).c_str(), *fontSize, 2);
		*collider = { x, y, vec.x, vec.y };
	}

	TextButton(const TextButton& b)
	{
		fontKey = new string(*b.fontKey);
		text = new string(*b.text);
		secondaryText = new string(*b.secondaryText);
		rotation = new float(*b.rotation);
		fontSize = new float(*b.fontSize);
		collider = new Rectangle(*b.collider);
	}
	TextButton(TextButton&& b) noexcept
	{
		collider = b.collider;
		fontKey = b.fontKey;
		text = b.text;
		fontSize = b.fontSize;
		rotation = b.rotation;
		secondaryText = b.secondaryText;
		b.secondaryText = nullptr;
		b.fontKey = nullptr;
		b.text = nullptr;
		b.fontSize = nullptr;
		b.rotation = nullptr;
		b.collider = nullptr;
	}
	~TextButton()
	{
		if (secondaryText)
		{
			delete secondaryText;
			secondaryText = nullptr;
		}
		if (collider)
		{
			delete collider;
			collider = nullptr;
		}
		if (rotation)
		{
			delete rotation;
			rotation = nullptr;
		}
		if (fontSize)
		{
			delete fontSize;
			fontSize = nullptr;
		}
		if (text)
		{
			delete text;
			text = nullptr;
		}
		if (fontKey)
		{
			delete fontKey;
			fontKey = nullptr;
		}
	}

	inline const Rectangle& getCollider() const { return *collider; }
	inline void updateCollider(const float& x, const float& y) { collider->x += x; collider->y += y; };
	inline void setCollider(const float& x, const float& y) { collider->x = x; collider->y = y; };
	void Draw(const Rectangle& mouse) const;
};

