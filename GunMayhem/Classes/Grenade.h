#pragma once
#include "Utils/Defines.h"
#include "Explosion.h"

extern unordered_map<string, Texture2D> textures;
extern float dt;

class Grenade
{	
	Rectangle* collider = new Rectangle();
	float* horizontalVelocity = new float(0.f);
	float* verticalVelocity = new float(0.f);
	bool* isActive = new bool(false);
	bool* doDraw = new bool(false);
	float* fuse = new float(1.32f);
	bool* onPlatform = new bool(false);

public:

	Grenade(const float& x, const float& y)
	{
		*collider = { x, y, (float)textures["Grenade"].width, (float)textures["Grenade"].height };
	}

	Grenade(const Grenade& g)
	{
		collider = new Rectangle(*g.collider);
		horizontalVelocity = new float(*g.horizontalVelocity);
		isActive = new bool(*g.isActive);
		fuse = new float(*g.fuse);
		doDraw = new bool(*g.doDraw);
		verticalVelocity = new float(*g.verticalVelocity);
		onPlatform = new bool(*g.onPlatform);
	}

	Grenade(Grenade&& g) noexcept
	{
		collider = g.collider;
		horizontalVelocity = g.horizontalVelocity;
		isActive = g.isActive;
		fuse = g.fuse;
		verticalVelocity = g.verticalVelocity;
		doDraw = g.doDraw;
		onPlatform = g.onPlatform;

		g.fuse = nullptr;
		g.horizontalVelocity = nullptr;
		g.isActive = nullptr;
		g.collider = nullptr;
		g.verticalVelocity = nullptr;
		g.doDraw = nullptr;
		g.onPlatform = nullptr;
	}

	Grenade& operator=(const Grenade& g)
	{
		collider = new Rectangle(*g.collider);
		horizontalVelocity = new float(*g.horizontalVelocity);
		isActive = new bool(*g.isActive);
		fuse = new float(*g.fuse);
		verticalVelocity = new float(*g.verticalVelocity);
		doDraw = new bool(*g.doDraw);
		onPlatform = new bool(*g.onPlatform);

		return *this;
	}

	~Grenade()
	{
		if (collider)
		{
			delete collider;
			collider = nullptr;
	    }
		if (horizontalVelocity)
		{
			delete horizontalVelocity;
			horizontalVelocity = nullptr;
		}
		if (isActive)
		{
			delete isActive;
			isActive = nullptr;
		}
		if (fuse)
		{
			delete fuse;
			fuse = nullptr;
		}
		if (doDraw)
		{
			delete doDraw;
			doDraw = nullptr;
		}
		if (verticalVelocity)
		{
			delete verticalVelocity;
			verticalVelocity = nullptr;
		}
		if (onPlatform)
		{
			delete onPlatform;
			onPlatform = nullptr;
		}
	}
	
	inline void SetOnPlatform(bool value) { *onPlatform = value; }
	inline void SetHorVelocity(const float& v) { *horizontalVelocity = v; }
	inline void SetVertVelocity(const float& v) { *verticalVelocity = v; }
	inline float GetVertVelocity() { return *verticalVelocity; }

	inline void UpdateVelocity(const float& v) { *horizontalVelocity += v; }
	inline void SetActive(const bool& b) { *isActive = b; }
	inline void SetCollider(const float& x, const float& y) { collider->x = x; collider->y = y; }
	inline void UpdateCollider(const float& x, const float& y) { collider->x += x; collider->y += y; }
	inline void SetDraw(const bool& b) { *doDraw = b; }
	inline void SetY(const float& y) { collider->y = y; }

	inline const Rectangle& getCollider() const { return *collider; }
	inline const float& getHorizantalVelocity() const { return *horizontalVelocity; }
	inline const bool& getActive() const { return *isActive; }
	inline const double& getFuseTime() const { return *fuse; }
	inline void updateFuseTime(double time) { *fuse += time; }
	inline const bool& getDraw() const { return *doDraw; }

	bool update();
	void Draw(const float& scale = 1.f) const;
	void Gravity();
};				  

