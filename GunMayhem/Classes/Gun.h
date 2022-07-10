#pragma once
#include "Bullet.h"
#include "Utils/Defines.h"

extern unordered_map<string, Texture2D> textures;

class Gun
{
private:
	const Bullet* bullet;

	const string* textureKey;
	string* displayName = new string("");
	const double* rateOfFire;
	short* ammo;
	const float* weight;
	const float* recoil;
public:
	const short& GetAmmo() const { return *ammo; };
	const double& GetRateOfFire() const { return *rateOfFire; };
	const float& GetWeight() const { return *weight; }
	const float& GetRecoil() const { return *recoil; }
	const string& GetName() const { return *textureKey; }
	const string& GetDisplayName() const { return *displayName; };

	void UpdateAmmoCount(const short& a);
	inline const bool isEmpty() const { return *ammo == 0; }
	void SetAmmo(const short a) { *ammo = a; }

	void Draw(const Rectangle& XYHS, const Direction& d) const;
	const Bullet& GetBullet() const { return *bullet; }

	//Gun() : textureKey(new string("NULL")), rateOfFire(new double(0)), ammo(new short(0)), weight(new float(0)), recoil(new float(0)), bullet(new Bullet("NULL")) {}
	Gun() {}
	Gun(const string& str);
	

	Gun(const Gun& g)
	{
		bullet = new Bullet(*g.bullet);
		textureKey = new string(*g.textureKey);
		rateOfFire = new double(*g.rateOfFire);
		ammo = new short(*g.ammo);
		weight = new float(*g.weight);
		recoil = new float(*g.recoil);
		displayName = new string(*g.displayName);
	}

	Gun& operator=(const Gun& g)
	{
		bullet = new Bullet(*g.bullet);
		textureKey = new string(*g.textureKey);
		rateOfFire = new double(*g.rateOfFire);
		ammo = new short(*g.ammo);
		weight = new float(*g.weight);
		recoil = new float(*g.recoil);
		displayName = new string(*g.displayName);

		return *this;
	}

	Gun(Gun&& g) noexcept
	{
		bullet = g.bullet;
		textureKey = g.textureKey;
		rateOfFire = g.rateOfFire;
		ammo = g.ammo;
		weight = g.weight;
		recoil = g.recoil;
		displayName = g.displayName;

		g.rateOfFire = nullptr;
		g.recoil = nullptr;
		g.textureKey = nullptr;
		g.weight = nullptr;
		g.ammo = nullptr;
		g.bullet = nullptr;
		g.displayName = nullptr;
	}

	~Gun()
	{
		if (textureKey)
		{
			delete textureKey;
			textureKey = nullptr;
		}		
		if (rateOfFire)
		{
			delete rateOfFire;
			rateOfFire = nullptr;
		}
		if (ammo)
		{
			delete ammo;
			ammo = nullptr;
		}
		if (weight)
		{
			delete weight;
			weight = nullptr;
		}
		if (recoil)
		{
			delete recoil;
			recoil = nullptr;
		}
		if (bullet)
		{
			delete bullet;
			bullet = nullptr;
		}
		if (displayName)
		{
			delete displayName;
			displayName = nullptr;
		}
	}
};

