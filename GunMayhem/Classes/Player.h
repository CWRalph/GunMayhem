#pragma once
#include "Clicker.h"
#include "Gun.h"
#include "Perk.h"
#include "Grenade.h"
#include "Utils/VariableType.h"
#include "Utils/Direction.h"
#include "Utils/Defines.h"
#include "Utils/Utils.h"


extern unordered_map<string, Texture2D> textures;
extern std::pair<unordered_map<string, Gun>, unordered_map<string, Gun>> guns;
extern unordered_map <string, Font> fonts;
extern unordered_map<string, Sound> sounds;
extern unordered_map<string, Perk> perks;

extern float dt;
extern short numOfLives;

static inline int ID = 1;

enum class Weapon
{
	Pistol,
	Primary
};

enum class PlayerType
{
	Player,
	AI
};

class Controls
{
	int right = 0;
	int left = 0;
	int jump = 0;
	int drop = 0;
	int bomb = 0;
	int shoot = 0;

public:
	Controls(const int& r, const int& l, const int& j, const int& d, const int& b, const int& s) :
		right(r), left(l), jump(j), drop(d), bomb(b), shoot(s) {}
	Controls(const Controls& c) { drop = c.drop; bomb = c.bomb; jump = c.jump; left = c.left; right = c.right; shoot = c.shoot; }
	Controls() {}
	~Controls() {}

	void SetJumpkey(const int& key) { jump = key; }
	void SetDropKey(const int& key) { drop = key; }
	void SetRightKey(const int& key) { right = key; }
	void SetLeftKey(const int& key) { left = key; }
	void SetShootKey(const int& key) { shoot = key; }
	void SetBombKey(const int& key) { bomb = key; }

	const int& GetJumpkey() const { return jump; }
	const int& GetDropKey() const { return drop; }
	const int& GetRightKey() const { return right; }
	const int& GetLeftKey() const { return left; }
	const int& GetShootKey() const { return shoot; }
	const int& GetBombKey() const { return bomb; }

	inline const bool operator==(const Controls& c) const
	{
		if (right != c.right) return false;
		if (left != c.left) return false;
		if (drop != c.drop) return false;
		if (jump != c.jump) return false;
		if (bomb != c.bomb) return false;
		if (shoot != c.shoot) return false;
		return true;
	}
};

class Player
{
private:
	//Main Variables
	Rectangle collider;
	Rectangle sourceRec;
	PlayerType type;
	Gun* pistol = new Gun(guns.second[K_COOL_PISTOL]);
	Gun* primary = nullptr;
	Perk* perk = new Perk(perks[K_PERK_NULL]);
	vector<Grenade> grenades;
	vector<Explosion> explosions;
	list<Bullet> activeBullets;
	Controls controls;
	Weapon inHand;
	

	//Drawing Variables
	string name;
	Direction direction;
	Color color;
	float scale = 1.f;

	//movement Variables
	float verticalVel = 0;

	//Gameplay Variables
	short lives = numOfLives;
	double timeSinceShot = 0;
	float nadeVel = GRENADE_VELOCITY;
	short grenadeIndex = 0;
	bool isDead = false;
	float horizontalVel = 0;
	short maxNumOfJumps = 2;
	short numOfJumps = 0;
	float knockback = 1.f;
	float ShieldTimer = 7.5f;
	float ScaleTimer = 12.f;
	float SpeedTimer = 13.5f;
	float speed = 1.f;

	//Perks
	bool canJump = false;
	bool recoil = true;
	bool infinitePistolAmmo = false;
	bool randomGun = false;
	bool gunWeight = true;
	bool shield = false;
	bool onPlatform = false;	
	short numOfNades = 3;
	short movementSim = 0;


	void CheckInput();
	void BotLogic();
	void ColliderMovement();



public:
	Player(const float& x, const float& y, const int& ku, const int& kdwn, const int& kr, const int& kl, const int& ks, const int& kb, const string& name = "Player", const Color& color = WHITE, const PlayerType& playertype = PlayerType::Player);

	Player(const Player& p);
	Player& operator= (const Player& p);
	inline ~Player()
	{
		if (pistol)
		{
			delete pistol;
			pistol = nullptr;
		}
		if (primary)
		{
			delete primary;
			primary = nullptr;
		}
		if (perk)
		{
			delete perk;
			perk = nullptr;
		}
	}
	void Shoot();
	void Jump();
	void MoveRight();
	void MoveLeft();
	void Drop();
	void ThrowNade();
	void HoldNade();
	bool AIBombInHand = false;
	float runAwayTimer = 0.f;
	float runToCenter = 0.f;
	bool seekingPlatform = false;
	bool pathfinding = false;
	bool doubleJump = false;
	int id;

	void UpdatePosition(const float& x, const float& y = 0);
	void SetCollider(const float& x, const float& y);
	inline void SetY(const float& y) { collider.y = y; }
	void UpdateHorVelocity(const float& xVel, const bool& finite = true);
	void SetControls(const vector<int>& c);


	inline const float getNextYPos() const { return (float)(collider.y + (verticalVel + GRAVITY * dt) * dt); }
	const float getNextXPos() const;

	void SetName(const string& str);
	void SetPerk(const Perk& p);
	void SetPrimary(const Gun& g);
	void SetPistol(const string& key);
	void SetPistol(const Gun& g);
	void SetPrimary(const string& key);
	void SetScale(const float& scale = 0.5f);
	void SetSpeedScale(const float& s);
	inline void SetPlayerType(const PlayerType& t) { type = t; }
	inline void SetColor(const Color& c) { color = c; }
	inline void SetVertVelocity(const float& v) { verticalVel = v; }
	inline void SetHorVelocity(const float& v) { horizontalVel = v; }
	inline void SetJumpCounter(const short& j) { numOfJumps = j; }
	inline void SetMovementSim(int x) { movementSim = x; }
	inline void SetDirection(Direction dir) { direction = dir; }
	inline void SetOnPlatform(const bool& b) { onPlatform = b; }
	inline void SetLives(const short& l = numOfLives) { lives = l; if (l > 0) isDead = false; }
	void SetKnockbackScale(const float& k, const float& time = 7.5f);

	inline const float& GetScale() const { return scale; }
	inline const float& GetTimeSinceShot() const { return timeSinceShot; }
	inline const PlayerType& GetPlayerType() const { return type; }
	inline const Direction& GetDirection() const { return direction; }
	inline const bool& GetOnPlatform() const { return onPlatform; }
	inline const int GetMovementSim() const { return movementSim; }
	inline const Perk& GetPerk() const { return *perk; };
	inline const string& GetName() const { return name; }
	inline const short& GetLives() const { return lives; }
	inline const Weapon& GetWeapon() const { return inHand; }
	inline const Rectangle& GetCollider() const { return collider; }
	inline const list<Bullet>& GetBullets() const { return activeBullets; }
	inline vector<Grenade>& GetGrenades() { return grenades; }
	inline const vector<Explosion>& GetExplosions() const { return explosions; }
	inline const float& GetSpeedScale() const { return speed; }
	inline const float& GetVerticalVelocity() const { return verticalVel; }
	inline const float& GetHorizantalVelocity() const { return horizontalVel; }
	inline const Color& GetColor() const { return color; }
	inline const bool& IsDead() const { return isDead; }
	void RemoveBullet(list<Bullet>::const_iterator& it);
	Gun& GetGunNonConst();
	const Gun& GetGun() const;
	const Gun& GetPistol() const;	
	const bool WithinHorizontalPosition(const Rectangle& platform, const float& offset = 0.f, const bool& recoil = false, const short& numOfrecoils = 4) const;
	const Vector2 GetCenterPos() const;	
	const float& GetKnockBackScale() const { return knockback; }
	const float GetAverageHorizantalVelocityForGivenTime(const float& time, const bool& total = false) const;


	void Reset(const float& Vv = 0, const float& Hv = 0);
	void Update(vector<Player>& players);
	void Gravity();
	void Draw(const short& index, const bool& drawUI = true);


	const bool operator==(const Player& p) const;

};
