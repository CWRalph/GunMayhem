#pragma once

extern bool exitGame;
extern std::unordered_map<string, Font> fonts;

class Button
{
private:
	Rectangle* collider = new Rectangle();
	Texture2D* skin = new Texture2D();


public:
	Button() {}
	Button(float x, float y, const char* fileName)
	{
		*skin = LoadTexture(fileName);
		*collider = { x, y, (float)skin->width, (float)skin->height };
	}
	Button(float x, float y,float width, float height)
	{
		*collider = { x, y, width, height };
	}
	Button(const Button& b)
	{
		collider = new Rectangle(*b.collider);
		skin = new Texture2D(*b.skin);
	}
	Button(Button&& b) noexcept
	{
		collider = b.collider;
		skin = b.skin;

		b.skin = nullptr;
		b.collider = nullptr;
	}
	~Button()
	{
		if (collider)
		{
			delete collider;
			collider = nullptr;
		}
		if (skin)
		{
			if (exitGame) UnloadTexture(*skin);
			delete skin;
			skin = nullptr;
		}
	}

	inline const Texture2D& getSkin() const { return *skin; }
	inline const Rectangle& getCollider() const { return *collider; }
	inline void updateCollider(const float& x, const float& y) { collider->x += x; collider->y += y; };
	inline void setCollider(const float& x, const float& y) { collider->x = x; collider->y = y; };
	void Draw(const float& scale = 1.f, const Color& c = WHITE) const;
};

