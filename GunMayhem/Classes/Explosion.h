#pragma once
#include "pch.h"
#include "Utils/Defines.h"

extern float dt;

class Explosion
{
	Vector2* centerPos;
	float* radius = new float(85.f);
	float* lifespan = new float(EXPLOSION_LIFESPAN);

public:

	Explosion(const Vector2& pos) : centerPos(new Vector2(pos)) {}
	Explosion(const float& x, const float& y) : centerPos(new Vector2({ x, y })) {}
	Explosion(const Rectangle& r) : centerPos(new Vector2({ r.x, r.y })) {}
	Explosion(Explosion&& e) noexcept
	{
		radius = e.radius;
		centerPos = e.centerPos;

		e.centerPos = nullptr;
		e.radius = nullptr;
	}
	Explosion(const Explosion& e)
	{
		centerPos = new Vector2(*e.centerPos);
		radius = new float(*e.radius);
		lifespan = new float(*e.lifespan);
	}
	Explosion& operator=(const Explosion& e)
	{
		centerPos = new Vector2(*e.centerPos);
		radius = new float(*e.radius);
		lifespan = new float(*e.lifespan);

		return *this;
	}
	~Explosion()
	{
		if (radius)
		{
			delete radius;
			radius = nullptr;
	    }
		if (centerPos)
		{
			delete centerPos;
			centerPos = nullptr;
		}
	}

	inline const Vector2& GetPosition() const { return *centerPos; }
	inline const float& GetRadius() const { return *radius; }
	inline const float& GetLifespan() const { return *lifespan; }

	void Draw() const;
	bool update();
};

