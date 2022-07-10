#pragma once
#include "Utils/Direction.h"
#include "Utils/IO.h"
#include "Utils/Defines.h"

extern unordered_map<string, Texture2D> textures;
extern float dt;

class Bullet
{
private:
	const float* knockback;
	float* speed;
	float* lifespan = new float(200);
	bool* isActive = new bool(false);
	Rectangle* collider;
	Direction* direction = new Direction(Direction::Right);
	const string* soundKey;
public:
	Bullet(const string& gunName, const float& x = -100.f, const float& y = -100.f);
	Bullet(const Bullet& b)
	{
		knockback = new const float(*b.knockback);
		speed = new float(*b.speed);
		lifespan = new float(*b.lifespan);
		collider = new Rectangle(*b.collider);
		direction = new Direction(*b.direction);
		isActive = new bool(*b.isActive);
		soundKey = new string(*b.soundKey);
	}
	Bullet& operator=(const Bullet& b)
	{
		knockback = new const float(*b.knockback);
		speed = new float(*b.speed);
		lifespan = new float(*b.lifespan);
		collider = new Rectangle(*b.collider);
		direction = new Direction(*b.direction);
		isActive = new bool(*b.isActive);
		soundKey = new string(*b.soundKey);

		return *this;
	}
	/*Bullet(Bullet&& b) noexcept
	{
		knockback = b.knockback;
		speed = b.speed;
		lifespan = b.lifespan;
		collider = b.collider;
		direction = b.direction;

		b.knockback = nullptr;
		b.speed = nullptr;
		b.lifespan = nullptr;
		b.collider = nullptr;
		b.direction = nullptr;
	}*/					 
	~Bullet()
	{
		if (knockback)
		{
			delete knockback;
			knockback = nullptr;
		}
		if (speed)
		{
			delete speed;
			speed = nullptr;
		}
		if (lifespan)
		{
			delete lifespan;
			lifespan = nullptr;
		}
		if (collider)
		{
			delete collider;
			collider = nullptr;
		}
		if (direction)
		{
			delete direction;
			direction = nullptr;
		}
		if (isActive)
		{
			delete isActive;
			isActive = nullptr;
		}
		if (soundKey)
		{
			delete soundKey;
			soundKey = nullptr;
		}
	}

	const float getKnockback() const;
	const float& getSpeed() const { return *speed; }
	const Rectangle& getCollider() const { return *collider; }
	const Direction& getDirection() const { return *direction; }
	const float& getLifespan() const { return *lifespan; }
	const bool& IsActive() const { return *isActive; }
	const string& getSoundKey() const { return *soundKey; }


	void setDirection(const Direction& d);
	void SetActive(const bool& b) { *isActive = b; }
	void setPosition(const float& x, const float& y);

	const bool& update();
	void Draw() const;	
};

