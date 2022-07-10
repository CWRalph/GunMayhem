#pragma once
#include "pch.h"
#include "Classes/Level.h"


extern unordered_map<string, Level> levels;

static bool CrateCollision(vector<Player>& p, const list<Crate>& c)
{
	for (const auto& crate : c)
	{
		for (auto& player : p)
		{
			if (!player.IsDead())
			{
				if (CheckCollisionRecs(player.GetCollider(), crate.GetCollider()))
				{
					player.SetPrimary(crate.getGun());
					return true;
				}
			}			
		}
	}
	return false;
}

static void ItemCollsion(vector<Player>& players, Item& i)
{
	for (auto& p : players)
	{
		if (!p.IsDead())
		{
			if (CheckCollisionRecs(p.GetCollider(), i.GetCollider()))
			{					
				switch (i.GetType())
				{
				case VariableType::Lives:
					p.SetLives(p.GetLives() + i.GetUpdateValue());
					break;
				case VariableType::Speed:
					p.SetSpeedScale(i.GetUpdateValue());
					break;
				case VariableType::Scale:
					p.SetScale(i.GetUpdateValue());
					break;				
				case VariableType::Knockback:
					p.SetKnockbackScale(i.GetUpdateValue());
					break;
				case VariableType::Undefined:
				default:
					return;
					break;
				}
				i = Item(K_ITEM_UNDEFINED, 1.f, VariableType::Undefined);
				return;
			}	
		}
	}
	i.Update();
	return;
}

static void BulletCollsion(vector<Player>& player)
{
	for (short i = 0; i < player.size(); i++)
	{
		for (short y = 0; y < player.size(); y++)
		{
			if (i != y && !player[i].IsDead())
			{				
				auto it = player[y].GetBullets().begin();
				while (it != player[y].GetBullets().end())
				{
					if (CheckCollisionRecs(player[i].GetCollider(), it->getCollider()))
					{
						player[i].UpdateHorVelocity(it->getKnockback() * player[i].GetKnockBackScale());
						player[y].RemoveBullet(it);
					}					
					else ++it;
				}
			}
		}
	}
}

static void FloorCollision(vector<Player>& players, const string& levelKey)
{
	for (auto& p : players)
	{
		//The bool collided stops the player from falling if it is true, ex if the player hits a platform
		if (!p.IsDead())
		{
			bool collided = false;
			for (const auto& platforms : levels[levelKey].getPlatforms())
			{
				/*This lengthy condition checks a few things :
				- The player is horizontally within the platform
				- The player is above the platform (not below since you should be able to jump through
				- The player will be below the platform next time the gravity function is applied */

				if (p.WithinHorizontalPosition(platforms) && (p.GetCollider().y + p.GetCollider().height) <= platforms.y && (p.getNextYPos() + p.GetCollider().height) > platforms.y)
				{
					collided = true;
					p.SetVertVelocity(0.f);

					//Do not do the p.GetCollider().height + 1 it messes this up for some reason
					p.SetY(platforms.y - p.GetCollider().height);
					p.SetJumpCounter(0);
					p.SetOnPlatform(true);
				}
			}
			if (!collided)
			{
				p.SetOnPlatform(false);
				p.Gravity();
			}
		}
	}					
}

static void FloorCollision(list<Crate>& crates, const string& levelKey)
{
	for (auto& c : crates)
	{
		bool collided = false;
		for (const auto& platforms : levels[levelKey].getPlatforms())
		{
			if (CheckCollisionRecs(platforms, c.GetCollider()))
			{
				collided = true;
				c.SetVertVelocity(0.f);
				c.SetY(platforms.y - c.GetCollider().height + 1);
			}
		}
		if (!collided)
		{
			c.Gravity();
		}
	}
}

static void GrenadeCollision(vector<Player>& players, const string& levelKey)
{
	for (auto& p : players)
	{
		if (!p.IsDead())
		{
			for (auto& g : p.GetGrenades())
			{
				if (g.getActive())
				{
					bool collided = false;
					for (auto& platforms : levels[levelKey].getPlatforms())
					{
						if (CheckCollisionRecs(g.getCollider(), platforms) && g.GetVertVelocity() >= 0)
						{
							collided = true;
							g.SetVertVelocity(0);
							g.SetY(platforms.y - g.getCollider().height + 1);
							g.SetOnPlatform(true);
						}
					}
					if (!collided)
					{
						g.Gravity();
					}
				}
			}
		}
    }
}

static void ExplosionCollsion(vector<Player>& players)
{
	for (auto& pl : players)
	{
		for (auto& p : players)
		{
			for (const auto& e : p.GetExplosions())
			{
				if (e.GetLifespan() > EXPLOSION_LIFESPAN - (3.f * dt))
				{
					if (CheckCollisionCircleRec(e.GetPosition(), e.GetRadius(), pl.GetCollider()))
					{
						float xlen = pl.GetCenterPos().x - e.GetPosition().x;
						float ylen = pl.GetCenterPos().y - e.GetPosition().y;
						float angle = atan2f(ylen, xlen);

						/*cout << "Cos is: " << cos(angle) << std::endl;
						cout <<  "Sin is: " << -sin(angle) << std::endl;*/

						pl.SetHorVelocity(cos(angle) * EXPLOSION_MAGNITUDE);
						pl.SetVertVelocity(sin(angle) * EXPLOSION_MAGNITUDE);
					}
				}
			}
		}
	}								 				
}