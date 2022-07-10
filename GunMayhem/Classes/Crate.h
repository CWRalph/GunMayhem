#pragma once
#include "Gun.h"
#include "Utils/Utils.h"
#include "Utils/Defines.h"

extern std::pair<unordered_map<string, Gun>, unordered_map<string, Gun>> guns;
extern unordered_map<string, Texture2D> textures;
extern float dt;


class Crate
{
	Gun* gun;
	Rectangle* collider = new Rectangle();
	float* verticalVel = new float(0.f);
	double* lifespan = new double(10);

public:
	Crate()
	{
		auto it = guns.first.begin();
		std::advance(it, (int)Random((int)guns.first.size() - 1));
		gun = &it->second;
		*collider = { (float)Random(600, 200), -(float)textures[K_CRATE].height, (float)textures[K_CRATE].width, (float)textures[K_CRATE].height };
	}

	Crate(const Crate& c)
	{
		gun = c.gun;
		collider = new Rectangle(*c.collider);
		verticalVel = new float(*c.verticalVel);
		lifespan = new double(*c.lifespan);
	}

	~Crate()
	{
		if (gun)
		{
			gun = nullptr;
		}
		if (collider)
		{
			delete collider;
			collider = nullptr;
		}
		if (verticalVel)
		{
			delete verticalVel;
			verticalVel = nullptr;
		}
		if (lifespan)
		{
			delete lifespan;
			lifespan = nullptr;
		}
	}

	bool Update();
	void Gravity();
	inline const Rectangle& GetCollider() const { return *collider; }
	inline const Gun& getGun() const { return *gun; }
	inline void SetVertVelocity(const float& Vv) { *verticalVel = Vv; }
	inline void SetY(const float& y) { collider->y = y; }
	void Draw() const;
};