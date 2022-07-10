#pragma once
#include "pch.h"
#include "Utils/VariableType.h"
#include "Utils/Defines.h"

extern unordered_map<string, Texture2D> textures;
extern float dt;

class Item
{
	float updateValue;
	VariableType type;
	Rectangle collider;
	string keyValue;
	double timer = 10;

public:
	Item() : keyValue(""), collider({0}), type(VariableType::Undefined), updateValue(1.f) {}
	Item(const string& kv, const float& uv, const VariableType& vt) : keyValue(kv), updateValue(uv), type(vt), collider({-100.f, -100.f, (float)textures[kv].width, (float)textures[kv].height}) {}
	Item(const Item& i)
	{
		updateValue = i.updateValue;
		type = i.type;
		collider = i.collider;
		keyValue = i.keyValue;
		timer = i.timer;
	}
	Item& operator= (const Item& i)
	{
		updateValue = i.updateValue;
		type = i.type;
		collider = i.collider;
		keyValue = i.keyValue;
		timer = i.timer;

		return *this;
	}
	~Item() {}

	inline const float& GetUpdateValue() const { return updateValue; }
	inline const VariableType& GetType() const { return type; }
	inline const Rectangle& GetCollider() const { return collider; }
	inline const string& GetTextureKey() const { return keyValue; }
	inline void UpdatePosition(const float& x, const float& y) { collider.x += x, collider.y += y; }
	inline void SetPosition(const float& x, const float& y) { collider.x = x, collider.y = y; }
	void Draw() const;
	void Update();
};

