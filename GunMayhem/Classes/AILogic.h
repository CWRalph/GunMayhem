#include "pch.h"
#include "Player.h"
#include "Level.h"
#include "Utils/Defines.h"

extern float dt;
extern unordered_map<string, Level> levels;
extern string currentLevelKey;
extern bool titleScreen;
extern bool target;

namespace AI
{
	static inline short pindex = 0;
	static inline float minDistance = screenWidth;
	static inline float minXlen = 0;
	static inline float minYlen = 0;
	static inline Rectangle platformOn = {};
	static inline Rectangle platformWithinSingleDistance = {};
	static inline Rectangle platformWithinDoubleDistance = {};
	static inline Rectangle closestUpwardsPlatform = {};
	static inline bool platformBelow = false;
	static inline bool atEndOfPlatform = false;
	static inline Direction directionToClosestPlatform = Direction::Right;
	static inline Direction directionToSinglePlatform = Direction::Right;
	static inline Direction directionToDoublePlatform = Direction::Right;
	static inline bool print = false;

	static bool WithinSingleJumpDistanceY(Player* p, const Rectangle& platform)
	{
		return (p->GetCollider().y - SINGLE_JUMP_Y < platform.y);
	}
	static bool WithinSingleJumpDistanceX(Player* p, const Rectangle& platform)
	{
		if (p->GetCollider().x > platform.x)
		{
			if (p->GetCollider().x + (MAX_SINGLE_JUMP_X * (p->GetAverageHorizantalVelocityForGivenTime(TIME_IN_AIR_SINGLE_JUMP) / MAX_PLAYER_SPEED)) < (platform.x + platform.width))
			{
				directionToSinglePlatform = Direction::Left;
				return true;
			}
		}	
		else if ((p->GetCollider().x + p->GetCollider().width) - (MAX_SINGLE_JUMP_X * (p->GetAverageHorizantalVelocityForGivenTime(TIME_IN_AIR_SINGLE_JUMP) / MAX_PLAYER_SPEED)) < platform.x)
		{
			directionToSinglePlatform = Direction::Right;
			return true;
		}
		return false;

	}
	static bool WithinSingleJumpDistance(Player* p, const Rectangle& platform)
	{
		return (WithinSingleJumpDistanceX(p, platform) && WithinSingleJumpDistanceY(p, platform));
	}
	static bool WithinDoubleJumpDistanceY(Player* p, const Rectangle& platform)
	{
		return (p->GetCollider().y - DOUBLE_JUMP_Y < platform.y);
	}
	static bool WithinDoubleJumpDistanceX(Player* p, const Rectangle& platform)
	{
		if (p->GetCollider().x > platform.x)
		{
			if (p->GetCollider().x + (MAX_DOUBLE_JUMP_X * (p->GetAverageHorizantalVelocityForGivenTime(TIME_IN_AIR_DOUBLE_JUMP) / MAX_PLAYER_SPEED)) < (platform.x + platform.width))
			{
				directionToSinglePlatform = Direction::Left;
				return true;
			}
		}	
		else if ((p->GetCollider().x + p->GetCollider().width) - (MAX_DOUBLE_JUMP_X * (p->GetAverageHorizantalVelocityForGivenTime(TIME_IN_AIR_DOUBLE_JUMP) / MAX_PLAYER_SPEED)) < platform.x)
		{
			directionToSinglePlatform = Direction::Right;
			return true;
		}
		return false;
	}
	static bool WithinDoubleJumpDistance(Player* p, const Rectangle& platform)
	{
		return (WithinDoubleJumpDistanceX(p, platform) && WithinDoubleJumpDistanceY(p, platform));
	}
	static void OptimalJump(Player* p)
	{
		if (p->GetOnPlatform())
			p->Jump();

		p->doubleJump = true;
		
	}

	static bool IsAtEndOfPlatform(Player* p, const Rectangle& platform)
	{
		if (p->GetCenterPos().x - (p->GetHorizantalVelocity() * dt) < platform.x)
			return true;
		if ((p->GetCollider().x + p->GetCollider().width) + (p->GetHorizantalVelocity() * dt) > platform.x + platform.width)
			return true;
		return false;
	}

	static void MoveInCurrentDirection(Player* p)
	{
		if (p->GetDirection() == Direction::Left)
			p->MoveLeft();
		else
			p->MoveRight();
	}

	static void MoveInDirection(Player* p, const Direction& d)
	{
		if (d == Direction::Left)
			p->MoveLeft();
		else p->MoveRight();
			
	}

	static void MoveToCenter(Player* p)
	{
		if (p->GetCenterPos().x < screenWidth * 0.5f)
			p->MoveRight();
		else
			p->MoveLeft();
	}

	static void MoveInDirectionOfNearestPlayer(Player* p, vector<Player>& players)
	{
		if (p->GetCenterPos().x < players[pindex].GetCenterPos().x)
			p->MoveRight();
		else
			p->MoveLeft();
	}

	static void Jump1(Player* p)
	{
		if (platformWithinSingleDistance.width > 10.f)
		{
			if (!p->seekingPlatform) OptimalJump(p);
			MoveInDirection(p, directionToSinglePlatform);
		}			
		/*else if (platformWithinDoubleDistance.width > 10.f)
		{
			OptimalJump(p);
			MoveInDirection(p, directionToDoublePlatform);
		}*/			
		p->seekingPlatform = true;
	}
	static void Jump3(Player* p)
	{
		if (minYlen > HITBOX_HEIGHT * 1.1f && minYlen < (HITBOX_HEIGHT * 1.1f) + SINGLE_JUMP_Y)
		{
			//if (print) cout << "First Jump Of Double Jump\n";
			OptimalJump(p);
		}
			
	}
	static void Jump2(Player* p)
	{
		if (platformBelow) 
			Jump3(p);
		else if (platformWithinDoubleDistance.width > 10.f)
			OptimalJump(p);
		else MoveInDirection(p, directionToDoublePlatform);
	
	}	
	static void Jump(Player* p)
	{
		//if (p->runToCenter > 0.f) return;

		if (atEndOfPlatform && !platformBelow)
			Jump1(p);
		/*else if (!p->GetOnPlatform())
			Jump2(p);*/			
		else
			Jump3(p);

		if (p->GetOnPlatform() && p->seekingPlatform) 
			p->seekingPlatform = false;
	}

	static void	RunToCenter(Player* p)
	{

		//Guard clauses to stop the run to center funtion
		if (p->GetCollider().x > 95.f ||
			(p->GetCollider().x + p->GetCollider().width < screenWidth - 95.f))
		{
			p->runAwayTimer = 0.f;
			return;
		}
		if (p->runAwayTimer > 0.f)
			p->runAwayTimer -= dt;
		else
			p->runAwayTimer = AI_RUN_TO_MIDDLE_TIME;

		bool platformB = false;
		short platformI = 0;

		//Check to see if there's platofrm that the player can run off onto
		if (!platformBelow)
		{
			for (const auto& platform : levels[currentLevelKey].getPlatforms())
			{
				if (platform.y > p->GetCollider().y + p->GetCollider().height &&
					p->WithinHorizontalPosition(platform, (p->GetCollider().x + p->GetAverageHorizantalVelocityForGivenTime(((platform.y - p->GetCollider().y)) / GRAVITY * dt), true)))
				{
					platformB = true;
					break;
				}
				++platformI;
			}
		}

		//if (print) cout << "Running Towards Center\n";
		//Check if the players on a platform
		if (p->GetOnPlatform())
		{
			//If hes at teh end and theres a platform belwo fim
			if (IsAtEndOfPlatform(p, platformOn))
			{
				if (platformBelow)
					p->Drop();
				if (platformB)
					MoveInCurrentDirection(p);
				else
					MoveInDirection(p, directionToClosestPlatform);
			}
			else MoveInCurrentDirection(p);
		}
		else
		{
			Jump1(p);

			if (p->seekingPlatform)
				p->runAwayTimer = 0.f;
			else
			{
				if (p->GetCollider().x < 50)
					p->MoveRight();
				if (p->GetCollider().y > screenWidth - 50)
					p->MoveLeft();
			}				
		}
		
	}

	static void Drop(Player* p, vector<Player>& players)
	{
		if (p->seekingPlatform) return;
		if (!p->GetOnPlatform()) return;
		if (p->GetCollider().y > 600.f) return;
		if (minYlen < -385.f) return;

		if (minYlen < players[pindex].GetCollider().height * 1.3f)
		{
			if (!players[pindex].GetOnPlatform()) return;
			if (!platformBelow) return;
			//if (print) cout << "Dropping\n";
			p->Drop();
		}
	}

	static void Shoot(Player* p)
	{
		if (p->runToCenter > 0.f) return;
		if (p->seekingPlatform) return;
		if (p->GetCollider().y < 0.f) return;
		if (abs(minYlen) > HITBOX_HEIGHT * 1.5f) return;
		if (minDistance > 600.f) return;
		if (abs(minXlen) > 450.f) return;
		
		float tipOfGun = (textures[p->GetGun().GetName()].width * p->GetScale()) + (textures[p->GetGun().GetName()].width * 0.33f);
		if (p->GetDirection() == Direction::Right) tipOfGun *= -1;
		float bulletSpeed = p->GetGun().GetBullet().getSpeed() * dt;
		float bulletLifeSpan = p->GetGun().GetBullet().getLifespan() / dt;
		if (p->GetCenterPos().x + abs((bulletSpeed * bulletLifeSpan) + tipOfGun) < minXlen) return;

		p->Shoot();
	}

	static bool PathFind(Player* p, vector<Player>& players)
	{
		if (!p->pathfinding)
		{
			if (abs(minYlen) < HITBOX_HEIGHT * 2.5f)
				return false;
		}
		if (players[pindex].GetCollider().y < 0)
		{
			p->pathfinding = false;
			return false;
		}
		 
		p->pathfinding = true;
		MoveInDirection(p, directionToClosestPlatform);

		if (WithinDoubleJumpDistance(p, closestUpwardsPlatform))
			OptimalJump(p);

		if (p->GetOnPlatform() && p->pathfinding)
		{
			p->pathfinding = false;
			return false;
		}
			 
		 return true;
	}

	static void	Move(Player* p, vector<Player>& players)
	{
		print = false;
		if (p->id == 1) print = true;

		RunToCenter(p);
		if (p->runToCenter > 0.f)
		{
			//if (print) cout << "Running To Center\n";
			return;
		}
			

		if (!p->doubleJump)
		{
			Jump(p);			
		}	
		else if (p->GetVerticalVelocity() > -30.f)
		{
			p->Jump();
			//if (print) cout << "Second Jump Of Double Jump\n";
			p->doubleJump = false;
		}

		if (PathFind(p, players))
		{
			//if (print) cout << "Path Finding\n";
			return;
		}

		Drop(p, players);
		Shoot(p);

		if (abs(minXlen) < 60.f) return;

		if (p->GetOnPlatform() && platformOn.width > 10.f)
		{
			if (!p->WithinHorizontalPosition(platformOn, p->GetCollider().x - p->getNextXPos()) && !platformBelow)
				return;			
		}
		if (!players[pindex].GetOnPlatform() && players[pindex].GetCenterPos().y > 450.f) return;
		if (abs(minYlen) > 375.f) return;

		MoveInDirectionOfNearestPlayer(p, players);
		//if (print) cout << "Moving Twoards Player\n";
	}

	

	static void logic(Player* p, vector<Player>& players)
	{
		//Bomb throwing logic
		if (!p->AIBombInHand && abs(minXlen) < 150.f && Random(1500) < 1)
			p->AIBombInHand = true;

		if (p->AIBombInHand)
			p->HoldNade();

		if (p->AIBombInHand && Random(500) < 1)
		{
			p->AIBombInHand = false;
			p->ThrowNade();
		}

		//if the player is off screen don't run any Logic
		if (p->GetCollider().y < 0)
		{
			if (p->GetCenterPos().x < 200)
				p->MoveRight();
			else if (p->GetCenterPos().x > screenWidth - 200)
				p->MoveLeft();
			return;
		}

		float xlen = 0;
		float ylen = 0;
		float closetPlatformLen = screenWidth;
		short iterator = 0;
		bool shoot = false;
		bool drop = false;
		bool jump = false;

		pindex = 0;
		minDistance = screenWidth;
		minXlen = 0;
		minYlen = 0;
		platformOn = {};
		platformWithinSingleDistance = {};
		platformWithinDoubleDistance = {};
		platformBelow = false;
		atEndOfPlatform = false;

		//Finding the target player
		for (auto& pla : players)
		{
			if (!(pla == *p) && (!target || pla.GetPlayerType() != PlayerType::AI))
			{
				ylen = p->GetCenterPos().y - pla.GetCenterPos().y;
				xlen = p->GetCenterPos().x - pla.GetCenterPos().x;
				float currentHypotenuse = sqrtf(pow(ylen, 2) + pow(xlen, 2));
				if (abs(currentHypotenuse) < abs(minDistance))
				{
					minDistance = currentHypotenuse;
					pindex = iterator;
					minXlen = xlen;
					minYlen = ylen;
				}
			}
			++iterator;
		}

		//runs through all the platforms setting diffrent ones to various static rectangles
		for (const auto& platform : levels[currentLevelKey].getPlatforms())
		{
			//Store the platform the player is currently standing on
			if (CheckCollisionRecs(p->GetCollider(), platform))
			{
				platformOn = platform;
				atEndOfPlatform = IsAtEndOfPlatform(p, platformOn);
			}

			//Store the closest jumpable platform and its deirecton in coreallation to the player
			if (p->GetCollider().y > platform.y)
			{
				if (p->GetCenterPos().x < platform.x)
				{
					if (float distance = platform.x - p->GetCenterPos().x < closetPlatformLen && WithinDoubleJumpDistanceY(p, platform))
					{
						closetPlatformLen = distance;
						closestUpwardsPlatform = platform;
						directionToClosestPlatform = Direction::Right;
					}
				}
				else
				{
					if (float distance = p->GetCenterPos().x - (platform.x + platform.width) < closetPlatformLen)
					{
						closetPlatformLen = distance;
						closestUpwardsPlatform = platform;
						directionToClosestPlatform = Direction::Left;
					}
				}
			}
		
			//Check if there's a patform directly below the player that iesn't th eplatform he's currectly on
			if (!platformBelow && 
				platform.y > p->GetCollider().y + p->GetCollider().height + 5.f &&
				p->WithinHorizontalPosition(platform) && !CheckCollisionRecs(p->GetCollider(), platform))
			{
				platformBelow = true;
			}

			//Store the platform thats within a single jumps distance
			if (p->GetCenterPos().y > platform.y && platformWithinSingleDistance.width < 10.f && WithinSingleJumpDistance(p, platform))
				platformWithinSingleDistance = platform;
			
			//Store the platform within a double jump distance
			if (p->GetCenterPos().y > platform.y && platformWithinDoubleDistance.width < 10.f && WithinDoubleJumpDistance(p, platform))
				platformWithinDoubleDistance = platform;
		}

		Move(p, players);
	}
};