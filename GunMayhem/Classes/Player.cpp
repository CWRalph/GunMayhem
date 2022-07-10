#include "pch.h"
#include "Player.h"
#include "AILogic.h"

extern const float UI_xPos[4];
extern unordered_map<string, Perk> perks;
inline static bool keyDown = false;
extern bool titleScreen;

Player::Player(const float& x, const float& y, const int& ku, const int& kdwn, const int& kr, const int& kl, const int& ks, const int& kb, const string& name, const Color& color, const PlayerType& playertype)
    : controls(kr, kl, ku, kdwn, kb, ks), color(color), name(name), type(playertype)
{
    direction = Direction::Left;
    inHand = Weapon::Pistol;
    collider = { x, y, (float)textures[K_PLAYER].width, HITBOX_HEIGHT };
    sourceRec = { 0, 0, (float)textures[K_PLAYER].width, (float)textures[K_PLAYER].height };
    grenades.reserve(numOfNades);
    explosions.reserve(numOfNades * 3);
    while (grenades.size() < numOfNades)
        grenades.push_back(Grenade(x, y));
    SetKnockbackScale(0.3f, 0.5f);
    id = ID;
    ++ID;
}

Player::Player(const Player& p)
{
    controls = p.controls;
    activeBullets = p.activeBullets;
    canJump = p.canJump;
    collider = p.collider;
    color = p.color;
    direction = p.direction;
    grenades = p.grenades;
    explosions = p.explosions;
    gunWeight = p.gunWeight;
    horizontalVel = p.horizontalVel;
    infinitePistolAmmo = p.infinitePistolAmmo;
    inHand = p.inHand;
    type = p.type;
    lives = p.lives;
    name = p.name;
    onPlatform = p.onPlatform;
    numOfJumps = p.numOfJumps;
    maxNumOfJumps = p.maxNumOfJumps;
    if (p.pistol)
        pistol = new Gun(*p.pistol);
    else pistol = new Gun(guns.second[K_COOL_PISTOL]);
    if (p.primary)
        primary = new Gun(*p.primary);
    else primary = nullptr;
    if (p.perk)
        perk = new Perk(*p.perk);
    else perk = new Perk(perks[K_PERK_NULL]);
    randomGun = p.randomGun;
    recoil = p.recoil;
    scale = p.scale;
    shield = p.shield;
    sourceRec = p.sourceRec;
    timeSinceShot = p.timeSinceShot;
    verticalVel = p.verticalVel;
    nadeVel = p.nadeVel;
    grenadeIndex = p.grenadeIndex;
    knockback = p.knockback;
    name = p.name;
    id = p.id;
    AIBombInHand = p.AIBombInHand;
    runAwayTimer = p.runAwayTimer;
    runToCenter = p.runToCenter;
    pathfinding = p.pathfinding;
    doubleJump = p.doubleJump;
}
Player& Player::operator=(const Player& p)
{
    controls = p.controls;
    type = p.type;
    activeBullets = p.activeBullets;
    canJump = p.canJump;
    collider = p.collider;
    color = p.color;
    direction = p.direction;
    grenades = p.grenades;
    explosions = p.explosions;
    gunWeight = p.gunWeight;
    horizontalVel = p.horizontalVel;
    infinitePistolAmmo = p.infinitePistolAmmo;
    inHand = p.inHand;
    lives = p.lives;
    name = p.name;
    onPlatform = p.onPlatform;
    numOfJumps = p.numOfJumps;
    maxNumOfJumps = p.maxNumOfJumps;
    if (p.pistol)
        pistol = new Gun(*p.pistol);
    else pistol = new Gun(guns.second[K_COOL_PISTOL]);
    if (p.primary)
        primary = new Gun(*p.primary);
    else primary = nullptr;
    if (p.perk)
        perk = new Perk(*p.perk);
    else perk = new Perk(perks[K_PERK_NULL]);
    randomGun = p.randomGun;
    recoil = p.recoil;
    scale = p.scale;
    shield = p.shield;
    sourceRec = p.sourceRec;
    timeSinceShot = p.timeSinceShot;
    verticalVel = p.verticalVel;
    nadeVel = p.nadeVel;
    grenadeIndex = p.grenadeIndex;
    knockback = p.knockback;
    name = p.name;
    id = p.id;
    AIBombInHand = p.AIBombInHand;
    runAwayTimer = p.runAwayTimer;
    runToCenter = p.runToCenter;
    pathfinding = p.pathfinding;
    doubleJump = p.doubleJump;

    return *this;
}


void Player::UpdatePosition(const float& x, const float& y)
{
    this->collider.x += x;
    this->collider.y += y;
}

void Player::SetCollider(const float& x, const float& y)
{
    collider.x = x;
    collider.y = y;
}

void Player::UpdateHorVelocity(const float& xVel, const bool& finite)
{
    if (finite)
    {
        if (xVel < 0 && horizontalVel <= xVel)
            return;
        if (xVel > 0 && horizontalVel >= xVel)
            return;
    }
    horizontalVel += xVel;
}

void Player::SetControls(const vector<int>& c)
{
    controls.SetJumpkey(c[0]);
    controls.SetDropKey(c[1]);
    controls.SetRightKey(c[2]);
    controls.SetLeftKey(c[3]);
    controls.SetShootKey(c[4]);
    controls.SetBombKey(c[5]);
}

void Player::Shoot()
{
    //Exit Funtion if the player can't shoot
    if (timeSinceShot < GetGun().GetRateOfFire())
      return;
 
     if (!(infinitePistolAmmo && inHand == Weapon::Pistol))
        GetGunNonConst().UpdateAmmoCount(-1);

    //set where the bullet should be spawned
    float x = (textures[GetGun().GetName()].width * scale) + textures[GetGun().GetName()].width * 0.33f;
    if (direction == Direction::Left) x *= -1;

    //Activate the bullet and give it the correct values according teh players inHand gun
    activeBullets.push_back(GetGun().GetBullet());
    activeBullets.end().operator--()->setDirection(direction);
    activeBullets.end().operator--()->SetActive(true);
    activeBullets.end().operator--()->setPosition(GetCenterPos().x + x, collider.y + collider.height * 0.333f);

    //Play sound
    if (GetSoundsPlaying() < 32) PlaySoundMulti(sounds[GetGun().GetBullet().getSoundKey()]);

    //reset the players shotTime 
    timeSinceShot = 0;

    //recoil
    if (recoil)
    {
      if (direction == Direction::Right) UpdateHorVelocity(-GetGun().GetRecoil());
      else UpdateHorVelocity(GetGun().GetRecoil());
    }

    
    if (GetGun().isEmpty())
    {
        if (titleScreen)
        {
            auto it = guns.first.begin();
            std::advance(it, (int)Random((int)guns.first.size() - 1));
            primary = new Gun(it->second);
            inHand = Weapon::Primary;
        }
        else if (inHand == Weapon::Primary)
        {
            primary = nullptr;
            inHand = Weapon::Pistol;
            timeSinceShot = -pistol->GetRateOfFire();
            pistol->SetAmmo(guns.second[pistol->GetName()].GetAmmo());
        }
        else if (inHand == Weapon::Pistol)
        {
            inHand = Weapon::Pistol;
            timeSinceShot = -pistol->GetRateOfFire();
            pistol->SetAmmo(guns.second[pistol->GetName()].GetAmmo());
        }
    }
}

void Player::Jump()
{
    if (numOfJumps >= maxNumOfJumps) return;

    collider.y -= 2;
    verticalVel = -435;

    if (!onPlatform) ++numOfJumps;
    if (numOfJumps == maxNumOfJumps - 1)
    numOfJumps = maxNumOfJumps;
}

void Player::MoveRight()
{
  direction = Direction::Right;
  float movementSpeed = MAX_PLAYER_SPEED * speed;
  if (gunWeight) movementSpeed -= GetGun().GetWeight();
  if (!(horizontalVel >= movementSpeed * 0.5f))
    horizontalVel += movementSpeed * dt * speed;
  keyDown = true;
}

void Player::MoveLeft()
{
  direction = Direction::Left;
  float movementSpeed = MAX_PLAYER_SPEED * speed;
  if (gunWeight) movementSpeed -= GetGun().GetWeight();
  if (!(horizontalVel <= movementSpeed * -0.5f))
    horizontalVel -= movementSpeed * dt * speed;
  keyDown = true;
}

void Player::Drop()
{
  collider.y += 2;
}

void Player::ThrowNade()
{
    if (grenades.empty() || grenadeIndex > grenades.size() - 1) return;
    grenades[grenadeIndex].SetVertVelocity(nadeVel * -0.5f);
    if (direction == Direction::Left) nadeVel *= -1;
    grenades[grenadeIndex].SetHorVelocity(nadeVel / 1.5f);
    grenades[grenadeIndex].SetActive(true);
    nadeVel = GRENADE_VELOCITY;
    ++grenadeIndex;
}

void Player::HoldNade()
{
    if (grenades.empty() || grenadeIndex > grenades.size() - 1) return;
    if (nadeVel < 500.f) nadeVel += 375.f * dt;
    grenades[grenadeIndex].SetCollider(collider.x - (10.f * scale), collider.y + (15.f * scale));
    grenades[grenadeIndex].SetDraw(true);  
}

void Player::CheckInput()
{
    if (IsKeyDown(controls.GetBombKey()))
    {
      HoldNade();
    }

    if (IsKeyReleased(controls.GetBombKey()))
    {
      ThrowNade();
    }

    if (IsKeyPressed(controls.GetDropKey()) && onPlatform)
      Drop();


    if (IsKeyPressed(controls.GetJumpkey()))
    {
      Jump();
    }

    if (IsKeyDown(controls.GetRightKey()))
      MoveRight();

    if (IsKeyDown(controls.GetLeftKey()))
      MoveLeft();


    //Constrols the players shooting
    if (IsKeyDown(controls.GetShootKey()))
      Shoot();
}

void Player::ColliderMovement()
{
  if (!keyDown)
  {
    if (horizontalVel > 0)
    {
      if (onPlatform) horizontalVel -= FRICTION * dt;
      else horizontalVel -= (FRICTION * 0.666666f) * dt;

      if (horizontalVel < 0) horizontalVel = 0;
    }
    if (horizontalVel < 0)
    {
      if (onPlatform) horizontalVel += FRICTION * dt;
      else horizontalVel += (FRICTION * 0.666666f) * dt;
      if (horizontalVel > 0) horizontalVel = 0;
    }
  }
  this->collider.x += horizontalVel * dt * speed;

  if (collider.x > screenWidth + 200.f || collider.x < -200.f || collider.y > screenHeight + 110)
  {
    --lives;
    collider.y = -1000.f;
    collider.x = (float)Random(screenWidth - (int)collider.width);
    Reset(-100.f);
  }
}

const float Player::getNextXPos() const
{
    float movementSpeed = MAX_PLAYER_SPEED * speed;
    if (gunWeight) movementSpeed -= GetGun().GetWeight();

    if (direction == Direction::Right)
        return collider.x + (horizontalVel + (movementSpeed * dt * speed) * dt * speed);
    else
        return collider.x - (horizontalVel - (movementSpeed * dt * speed) * dt * speed);
}

void Player::SetName(const string& str)
{
    name = str;

    if (name.length() > 15)
        name.erase(name.begin() + 15, name.end());
}

void Player::SetPerk(const Perk& p)
{
    maxNumOfJumps = 2;
    recoil = true;
    infinitePistolAmmo = false;
    randomGun = false;
    gunWeight = true;
    numOfNades = 3;
    perk = nullptr;

    switch (p.getType())
    {
    case VariableType::Jumps:
    {
        maxNumOfJumps = 3;
        perk = new Perk(perks[K_PERK_TRIPLE_JUMP]);
    } break;
    case VariableType::Recoil:
    {
        recoil = false;
        perk = new Perk(perks[K_PERK_NO_RECOIL]);
    } break;
    case VariableType::PistolAmmo:
    {
        infinitePistolAmmo = true;
        perk = new Perk(perks[K_PERK_PISTOLAMMO]);
    }  break;
    case VariableType::Weight:
    {
        gunWeight = false;
        perk = new Perk(perks[K_PERK_WEIGHT]);
    } break;
    case VariableType::RandomGun:
    {
        randomGun = true;
        auto it = guns.first.begin();
        std::advance(it, (int)Random((int)guns.first.size() - 1));
        primary = new Gun(it->second);
        inHand = Weapon::Primary;
        perk = new Perk(perks[K_PERK_RANDOM_GUN]);
    } break;
    case VariableType::Grenades:
    {
        numOfNades = 5;
        while (grenades.size() < numOfNades)
            grenades.push_back(Grenade(0, 0));
        perk = new Perk(perks[K_PERK_EXTRA_NADES]);
    } break;
    case VariableType::Undefined:
        perk = new Perk(perks[K_PERK_NULL]);
        break;

    }
}

//Set the player's primary Gun using a gun reference
void Player::SetPrimary(const Gun& g)
{
    if (primary)
    {
        delete primary;
        primary = nullptr;
    }

    primary = new Gun(g);
    timeSinceShot = primary->GetRateOfFire();
    inHand = Weapon::Primary;
}

void Player::SetPistol(const string& key)
{
    if (pistol)
    {
        delete pistol;
        pistol = nullptr;
    }

    pistol = new Gun(guns.second[key]);
}

void Player::SetPistol(const Gun& g)
{
    if (pistol)
    {
        delete pistol;
        pistol = nullptr;
    }

    pistol = new Gun(g);
}


//Set the player's primary Gun using a string as a key to the guns map
void Player::SetPrimary(const string& key)
{
    if (primary)
    {
        delete primary;
        primary = nullptr;
    }

    primary = new Gun(guns.first[key]);
    timeSinceShot = primary->GetRateOfFire();
    inHand = Weapon::Primary;
}

//Sets the scale of the player to any size
void Player::SetScale(const float& scale)
{
    collider.width = textures[K_PLAYER].width * scale;
    collider.height = HITBOX_HEIGHT * scale;
    if (scale != 1.f)
        ScaleTimer = 12.f;
    else
    {
        ScaleTimer = 0.f;
        if (this->scale != 1.f) collider.y -= collider.height * (1.1f - this->scale);
    }
    this->scale = scale;
}

void Player::SetSpeedScale(const float& s)
{
    speed = s;
    if (speed != 1.f)
        SpeedTimer = 13.5f;
    else
        SpeedTimer = 0.f;
}

void Player::SetKnockbackScale(const float& k, const float& time)
{
    knockback = k;
    if (k != 1.f)
        ShieldTimer = time;
    else
        ShieldTimer = 0.f;
}

void Player::RemoveBullet(list<Bullet>::const_iterator& it)
{
    it = activeBullets.erase(it);
}

//Gets the gun the player currently has equipped - allows for changes
Gun& Player::GetGunNonConst()
{
    if (inHand == Weapon::Primary)
        return *this->primary;
    return *this->pistol;
}

//Gets the gun the player currently has equipped
const Gun& Player::GetGun() const
{
    if (inHand == Weapon::Primary)
        return *this->primary;
    return *this->pistol;
}

const Gun& Player::GetPistol() const
{
    if (pistol == nullptr) return guns.second[K_COOL_PISTOL];
    return *pistol;
}

const bool Player::WithinHorizontalPosition(const Rectangle& platform, const float& offset, const bool& recoil, const short& numOfrecoils) const
{
    float r = 0.f;
    if (recoil)
        r = GetGun().GetRecoil() * (float)numOfrecoils;

    if ((collider.x + collider.width + r + offset) < platform.x || collider.x + r + offset > (platform.x + platform.width)) return false;
    return true;
}

const Vector2 Player::GetCenterPos() const
{
    float x = collider.x + (collider.width * 0.5f);
    float y = collider.y + (collider.height * 0.5f);
    return { x, y };
}

const float Player::GetAverageHorizantalVelocityForGivenTime(const float& time, const bool& total) const
{
    if (dt <= 0.f) return 0.f;

    float hVel = horizontalVel;
    float movementSpeed = MAX_PLAYER_SPEED * speed;
    int iterations = 0;
    for (float t = time; t > 0; t -= dt, iterations++)
    {
        if (gunWeight) movementSpeed -= GetGun().GetWeight();
        if (!(hVel >= movementSpeed * 0.5f))
            hVel += movementSpeed * dt * speed;
    }
    if (total) return hVel;
    return hVel / (float)iterations;
}

void Player::Draw(const short& index, const bool& drawUI)
{
    if (isDead) return;
    //Wether or not to flip the players texture
    if (direction == Direction::Left && sourceRec.width < 0) sourceRec.width *= -1;
    else if (direction == Direction::Right && sourceRec.width > 0) sourceRec.width *= -1;

    //Setting the postion and scale of the player
    Rectangle dest = { collider.x, collider.y + (HITBOX_HEIGHT * scale) - textures[K_PLAYER].height * scale, textures[K_PLAYER].width * scale, textures[K_PLAYER].height * scale };
    DrawTexturePro(textures[K_PLAYER], sourceRec, dest, { 0.0f, 0.0f }, 0.0f, color);
    //DrawRectangleLines(collider.x, collider.y, collider.width, collider.height, RED);
    //DrawRectangleLines(collider.x, collider.y + collider.height - 2, collider.width, 2, RED);


    //Printing the players gun and bullets
    this->GetGun().Draw({collider.width  *0.333f + collider.x, collider.y, collider.height, scale}, direction);
    for (const auto& it : activeBullets)
        it.Draw();

    for (const auto& g : grenades)
        g.Draw(scale);

    for (const auto& it : explosions)
        it.Draw();

    //Drawing the Players UI element
    //The White BG UI Box Template
    if (drawUI)
    {
        const Vector2 startPos = { UI_xPos[index] + (float)textures[K_PLAYER].width * 0.3f, UI_YPOS + 10 };
        DrawTexture(textures[K_UI], (int)UI_xPos[index], (int)UI_YPOS, WHITE);

        //The little Player Cutout
        dest = { startPos.x, startPos.y, (float)textures[K_PLAYER].width, (float)textures[K_PLAYER].height * 0.6f };
        Rectangle source = { 0, 0, (float)textures[K_PLAYER].width, (float)textures[K_PLAYER].height - HITBOX_HEIGHT * 0.5f };
        DrawTexturePro(textures[K_PLAYER], source, dest, { 0.f, 0.f }, 0.f, color);

        //The Player's name, gun, lives, and bullet count
        DrawTextEx(fonts[K_UI_FONT], to_string(lives).c_str(), { startPos.x + 62, startPos.y + 36 }, 35, 1, BLACK);
        DrawTextEx(fonts[K_UI_FONT], to_string(GetGun().GetAmmo()).c_str(), { startPos.x + 130, startPos.y + 45 }, 20, 1, RED);
        DrawTextEx(fonts[K_UI_FONT], GetGun().GetDisplayName().c_str(), { startPos.x + 107, startPos.y + 22 }, 12, 1, BLACK);
        DrawTextEx(fonts[K_UI_FONT], name.c_str(), { startPos.x + 70, startPos.y }, 12, 1, BLACK);

        if (knockback < 1.f)
            if (ShieldTimer > 1.3f || ShieldTimer < 1.3f && int(ShieldTimer * 10) % 2 == 0)
                DrawCircle(GetCenterPos().x, GetCenterPos().y, collider.width, { 100, 100, 100, 100 });
    }



    if (collider.x > screenWidth)
        DrawTexture(textures[K_OFF_SCREEN_INDICATOR_X], screenWidth - (int)textures[K_OFF_SCREEN_INDICATOR_X].width - 5, (int)collider.y, color);
    else if (collider.x < -collider.width)
        DrawTexturePro(textures[K_OFF_SCREEN_INDICATOR_X], { 0, 0, -(float)textures[K_OFF_SCREEN_INDICATOR_X].width, (float)textures[K_OFF_SCREEN_INDICATOR_X].height }, { 0, collider.y, (float)textures[K_OFF_SCREEN_INDICATOR_X].width, (float)textures[K_OFF_SCREEN_INDICATOR_X].height }, { 0.f, 0.f }, 0.f, color);
    else if (collider.y < -collider.height)
        DrawTexture(textures[K_OFF_SCREEN_INDICATOR_Y], (int)collider.x, 0, color);
}

void Player::Reset(const float& Vv, const float& Hv)
{
    if (lives <= 0)
    {
        isDead = true;
        return;
    }
    horizontalVel = Hv;
    verticalVel = Vv;
    primary = nullptr;
    pathfinding = false;
    doubleJump = false;
    seekingPlatform = false;
    grenadeIndex = 0;
    AIBombInHand = false;
    runAwayTimer = 0.f;
    runToCenter = 0.f;
    pathfinding = false;
    doubleJump = false;

    if (randomGun || titleScreen)
    {
        auto it = guns.first.begin();
        std::advance(it, (int)Random((int)guns.first.size() - 1));
        primary = new Gun(it->second);
        inHand = Weapon::Primary;
    }
    else
    {
        inHand = Weapon::Pistol;
        pistol->SetAmmo(guns.second[pistol->GetName()].GetAmmo());
    }
    numOfJumps = 0;
    grenadeIndex = 0;

    if (lives != numOfLives)
        SetKnockbackScale(0.3f, 2.65f);
    SetScale(1.f);
    SetSpeedScale(1.f);
    //grenades.clear();
    while (grenades.size() < numOfNades)
        grenades.push_back(Grenade(0, 0));
}

void Player::Update(vector<Player>& players)
{

  if (isDead)
      return;

  timeSinceShot += dt;

  if (ShieldTimer <= 0.f)
      SetKnockbackScale(1.f);
  else
      ShieldTimer -= dt;

  if (ScaleTimer <= 0.f)
      SetScale(1.f);
  else
      ScaleTimer -= dt;

  if (SpeedTimer <= 0.f)
      SetSpeedScale(1.f);
  else
      SpeedTimer -= dt;

  keyDown = false;

  if (type == PlayerType::Player) CheckInput();
  else AI::logic(this, players);

  ColliderMovement();

  //Updates and Bullets And Deletes the ones that have gone 200px off screen
  auto it_bullets = activeBullets.begin();
  auto it_grenades = grenades.begin();

  while (it_bullets != activeBullets.end())
  {
      if (it_bullets->update()) ++it_bullets;
      else it_bullets = activeBullets.erase(it_bullets);
  }

  while (it_grenades != grenades.end())
  {
      if (it_grenades->update())
      {
          explosions.push_back(Explosion(it_grenades->getCollider()));
          //cout << "Explosion\n";
          it_grenades = grenades.erase(it_grenades);
          --grenadeIndex;
      }
      else ++it_grenades;
  }

  auto it_explosion = explosions.begin();
  while (it_explosion != explosions.end())
  {
      if (it_explosion->update()) it_explosion = explosions.erase(it_explosion);
      else ++it_explosion;
  }
}

void Player::Gravity()
{
    verticalVel += GRAVITY * dt;
    if (verticalVel > 4000.f) verticalVel = 4000.f;
    collider.y += verticalVel * dt;
}

const bool Player::operator==(const Player& p) const
{
    if (id != p.id) return false;
    if (name != p.name) return false;
    if (!(controls == p.controls)) return false;
    if (color.r != p.color.r) return false;
    if (color.b != p.color.b) return false;
    if (color.g != p.color.g) return false;
    return true;
}
