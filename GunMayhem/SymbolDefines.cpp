#include "pch.h"
#include "SymbolDefines.h"
#include "Classes/Player.h"
#include "Classes/Bullet.h"
#include "Classes/Crate.h"
#include "Classes/Perk.h"
#include "Classes/Item.h"
#include "Classes/Button.h"
#include "Utils/Collision.h"
#include "Classes/Explosion.h"
#include "Utils/LoadAssests.h"
#include "Classes/Level.h"


extern float dt{};
extern bool exitGame = false;
extern bool name = false;
extern bool titleScreen = true;
extern bool teams = false;
extern short numOfLives = 10;
extern bool target = false;
extern string currentLevelKey = K_LEVEL1;
extern std::pair<unordered_map<string, Gun>, unordered_map<string, Gun>> guns{};
extern unordered_map<string, Texture2D> textures{};
extern unordered_map<string, Perk> perks{};
extern unordered_map<string, Font> fonts{};
extern unordered_map<string, Level> levels{};
extern unordered_map<string, Sound> sounds = {};
extern unordered_map<string, Button> buttons = {};
extern vector<vector<string>> Ckeys = {};
extern const float UI_xPos[4] = { 25.f, 225.f + 25.f, (225.f * 2) + 25.f, (225.f * 3) + 25.f };
