#pragma once
#include "pch.h"
#include "Classes/Gun.h"
#include "Utils/Defines.h"
#include "Classes/Level.h"
#include "Classes/Button.h"
#include "Classes/TextButton.h"

extern std::unordered_map<string, Texture2D> textures;
extern std::pair<unordered_map<string, Gun>, unordered_map<string, Gun>> guns;
extern std::unordered_map<string, Font> fonts;
extern unordered_map<string, Level> levels;
extern unordered_map<string, Sound> sounds;
extern unordered_map<string, Perk> perks;
extern vector<vector<string>> Ckeys;

static void LoadGameTextures()
{

#pragma region Player

	textures.insert({ K_PLAYER, LoadTexture("Assests/Player/Default.png") });
	textures.insert({ K_UI, LoadTexture("Assests/Player/UI.png") });
	textures.insert({ K_OFF_SCREEN_INDICATOR_X, LoadTexture("Assests/Player/IndicatorX.png") });
	textures.insert({ K_OFF_SCREEN_INDICATOR_Y, LoadTexture("Assests/Player/IndicatorY.png") });

#pragma endregion

#pragma region Guns

	textures.insert({ K_GREY_SMG, LoadTexture("Assests/Guns/SMG/Grey.png") });
	textures.insert({ K_CHEAP, LoadTexture("Assests/Guns/SMG/Cheap.png") });
	textures.insert({ K_BULLET, LoadTexture("Assests/Guns/Bullet.png") });
	textures.insert({ K_ANGRY_COW_PISTOL ,LoadTexture("Assests/Guns/Pistols/Cow.png") });
	textures.insert({ K_GLICK_PISTOL ,LoadTexture("Assests/Guns/Pistols/Glick.png") });
	textures.insert({ K_SAND_HAWK_PISTOL ,LoadTexture("Assests/Guns/Pistols/Hawk.png") });
	textures.insert({ K_FIFTY_EIGHT_PISTOL ,LoadTexture("Assests/Guns/Pistols/58.png") });
	textures.insert({ K_SNAKE_PISTOL ,LoadTexture("Assests/Guns/Pistols/Snake.png") });
	textures.insert({ K_COOL_PISTOL, LoadTexture("Assests/Guns/Pistols/Cool.png") });
	textures.insert({ K_CHROME_SMG, LoadTexture("Assests/Guns/SMG/Chrome.png") });
	textures.insert({ K_COMPACT, LoadTexture("Assests/Guns/SMG/Compact.png") });
	textures.insert({ K_POLICE, LoadTexture("Assests/Guns/SMG/Police.png") });
	textures.insert({ K_TATICAL_SMG, LoadTexture("Assests/Guns/SMG/Tatical.png") });
	textures.insert({ K_ASSAULT_CARBINE, LoadTexture("Assests/Guns/AR/AssaultCarbine.png") });
	textures.insert({ K_BULLPUP_MG, LoadTexture("Assests/Guns/AR/Bullpup.png") });
	textures.insert({ K_CLASSIC, LoadTexture("Assests/Guns/AR/Classic.png") });
	textures.insert({ K_LONG_RANGE, LoadTexture("Assests/Guns/AR/LongRange.png") });
	textures.insert({ K_RELIABLE, LoadTexture("Assests/Guns/AR/Reliable.png") });
	textures.insert({ K_TOP_LOAD, LoadTexture("Assests/Guns/AR/TopLoad.png") });
	textures.insert({ K_BULLPUP_SNIPER, LoadTexture("Assests/Guns/Sniper/Bullpup.png") });
	textures.insert({ K_RUGGED_SNIPER, LoadTexture("Assests/Guns/Sniper/Rugged.png") });
	textures.insert({ K_SINGLE_SHOT, LoadTexture("Assests/Guns/Sniper/Single.png") });
	textures.insert({ K_ASSAULT_SG, LoadTexture("Assests/Guns/Shotgun/Assault.png") });
	textures.insert({ K_CHROM_SG, LoadTexture("Assests/Guns/Shotgun/Chrome.png") });
	textures.insert({ K_STANDAR_SG, LoadTexture("Assests/Guns/Shotgun/Standard.png") });
	textures.insert({ K_STUBBY_SG, LoadTexture("Assests/Guns/Shotgun/Stubby.png") });
	
#pragma endregion

#pragma region Levels
	textures.insert({ K_LEVEL1_BG, LoadTexture("Assests/LevelAssets/BGs/minecraftPOG.png")});
	textures.insert({ K_LEVEL1_PLAT, LoadTexture("Assests/LevelAssets/Platforms/default_platform.png")});
	textures.insert({ K_LEVEL2_BG, LoadTexture("Assests/LevelAssets/Bgs/Level2BG.png")});
	textures.insert({ K_LEVEL2_PLAT, LoadTexture("Assests/LevelAssets/Platforms/Level2Platform.png")});
	
#pragma endregion

#pragma region GameAssests
	
	fonts.insert({ K_UI_FONT, LoadFont("Assests/GameAssests/Candara.ttf") });
	fonts.insert({ K_UI_FONT_BOLD, LoadFont("Assests/GameAssests/CandaraBold.ttf") });
	
	textures.insert({ K_CRATE, LoadTexture("Assests/GameAssests/Crate.png") });
	textures.insert({ K_GRENADE, LoadTexture("Assests/GameAssests/Grenade.png") });
	textures.insert({ K_PERK_BG, LoadTexture("Assests/Perks/BG.png") });
	textures.insert({ CBAN_PROMPT, LoadTexture("Assests/GameAssests/Controls.png") });

#pragma endregion

#pragma region Sounds
	sounds.insert({ K_SHOOT_SOUND,LoadSound("Assests/Audio/Sounds/gun_sound.wav") });
	sounds.insert({ K_EXPLOSION_SOUND,LoadSound("Assests/Audio/Sounds/explosionShort.wav") });
	sounds.insert({ K_CRATE_SOUND,LoadSound("Assests/Audio/Sounds/crate_interaction.mp3") });
	sounds.insert({ K_SOUND_AR, LoadSound("Assests/Audio/Sounds/AR.mp3") });
	sounds.insert({ K_SOUND_SMALL_PISTOL, LoadSound("Assests/Audio/Sounds/SmallPistol.mp3") });
	sounds.insert({ K_SOUND_SNIPER, LoadSound("Assests/Audio/Sounds/Sniper.mp3") });
	sounds.insert({ K_SOUND_LARGE_PISTOL, LoadSound("Assests/Audio/Sounds/LargePistol.mp3") });
	sounds.insert({ K_SOUND_SHOTGUN, LoadSound("Assests/Audio/Sounds/Shotgun.mp3") });
	sounds.insert({ K_SOUND_SMG, LoadSound("Assests/Audio/Sounds/SMG.mp3") });
#pragma endregion

#pragma region Banners
	textures.insert({ K_UI_START_BUTTON , LoadTexture("Assests/GameAssests/Start.png") });
	textures.insert({ K_BANNER_CLEAR_SLOT , LoadTexture("Assests/PlayerSetup/ClearSlot.png") });
	textures.insert({ K_PL_SETUP_EMPTY_BANNER , LoadTexture("Assests/PlayerSetup/EmptyBanner.png") });
	textures.insert({ K_PL_SETUP_NAME_BOX , LoadTexture("Assests/PlayerSetup/NameBox.png") });
	textures.insert({ K_PL_SETUP_BANNER_OUTLINE , LoadTexture("Assests/PlayerSetup/BannerOutline.png") });
	textures.insert({ K_PL_SETUP_COLOR_BG, LoadTexture("Assests/PlayerSetup/ColorBG.png") });
	textures.insert({ K_PL_SETUP_GUN_BG, LoadTexture("Assests/PlayerSetup/GunBG.png") });
#pragma endregion

#pragma region Items
	textures.insert({ K_ITEM_1UP , LoadTexture("Assests/Items/1up.png") });
	textures.insert({ K_ITEM_MINIMIZE, LoadTexture("Assests/Items/Mini.png") });
	textures.insert({ K_ITEM_SHIELD, LoadTexture("Assests/Items/Shield.png") });
	textures.insert({ K_ITEM_SPEED, LoadTexture("Assests/Items/Speed.png") });
	textures.insert({ K_ITEM_UNDEFINED, LoadTexture("Assests/Items/null.png") });

#pragma endregion

}

static void LoadGuns()
{
	fstream inFile("TextFiles/Guns.txt");
	string temp = "", key = "", type = "";
	while (!inFile.eof())
	{
		std::getline(inFile, temp);
		stringstream ss(temp);
		ss >> type;
		ss >> key;
		if (type == "1") guns.first.insert({ key, Gun(temp) });			
		else guns.second.insert({ key, Gun(temp) });
	}		
}

static void LoadLevels()
{
	fstream inFile("TextFiles/levels.txt");
	string temp = "", x = "", name = "";
	bool inLevel = false;
	vector<int> xPos;
	xPos.reserve(4);
	short platform_count = 0, counter = 0, levelNum = 0;
	while (!inFile.eof())
	{
		std::getline(inFile, temp);
		stringstream ss(temp);
		if (!inLevel)
		{
			++levelNum;
			name = "Level" + to_string(levelNum);
			inLevel = true;			
			ss >> temp;			
			while (ss >> x)
				xPos.push_back(stoi(x));
			platform_count = stoi(temp);
			levels.insert({name , Level("Level" + to_string(levelNum) + "BG", "Level" + to_string(levelNum) + "Platform", xPos)});
			xPos.clear();
		}
		else
		{
			Rectangle rec = {0, 0, 0, 4};
			counter = 0;
			while (ss >> temp)
			{
				switch (counter)
				{
				case 0:
				{
					rec.x = stof(temp);
				}break;
				case 1:
				{
					rec.y = stof(temp);
				}break;
				case 2:
				{
					rec.width = stof(temp);
				}break;				
				}
				++counter;
			}
			--platform_count;
			levels[name].addPlatform(rec);
			if(platform_count == 0) inLevel = false;
		}
	}
}

static void LoadPerks()
{
	perks.insert({ K_PERK_EXTRA_NADES, Perk(VariableType::Grenades, 325, 350, "Assests/Perks/ExtraNades.png", "5 Grenades Every Life") });
	perks.insert({ K_PERK_WEIGHT , Perk(VariableType::Weight, 425, 350, "Assests/Perks/GunWeight.png", "No Gun Weight") });
	perks.insert({ K_PERK_PISTOLAMMO, Perk(VariableType::PistolAmmo, 525, 350, "Assests/Perks/infinitePistol.png", "Infinite Pistol Ammo") });
	perks.insert({ K_PERK_TRIPLE_JUMP, Perk(VariableType::Jumps, 325, 450, "Assests/Perks/Jump.png", "3 Jumps") });
	perks.insert({ K_PERK_NO_RECOIL, Perk(VariableType::Recoil, 425, 450, "Assests/Perks/NoRecoil.png", "No Recoil On Any Gun") });
	perks.insert({ K_PERK_RANDOM_GUN, Perk(VariableType::RandomGun, 525, 450, "Assests/Perks/RandomGun.png", "Random Gun At Spawn") });
	perks.insert({ K_PERK_NULL, Perk(VariableType::Undefined, 625, 400, "Assests/Perks/NoPerk.png", "No Perk For The God Gamer") });
}

static void LoadButtons(unordered_map<string, Button>& b, unordered_map<string, TextButton>& tb)
{
	b.insert({ K_START_BUTTON, Button(595.f, 875.f, "Assests/GameAssests/Start.png") });
	b.insert({ K_CONTINUE_BUTTON, Button(595.f, 875.f, "Assests/GameAssests/Continue.png") });

	tb.insert({ K_BUTTON_CUSTOM,TextButton(100.f,K_UI_FONT_BOLD, -5.f, 32.f,K_BUTTON_CUSTOM)});
	tb.insert({ K_BUTTON_CAMPAIGN,TextButton(200.f,K_UI_FONT_BOLD, -5.f, 32.f,K_BUTTON_CAMPAIGN) });
	tb.insert({ K_BUTTON_CREDITS,TextButton(300.f,K_UI_FONT_BOLD, -5.f, 32.f,K_BUTTON_CREDITS) });
	tb.insert({ K_BUTTON_OPTIONS,TextButton(400.f,K_UI_FONT_BOLD, -5.f, 32.f,K_BUTTON_OPTIONS) });
	tb.insert({ K_BUTTON_CHALLENGES,TextButton(500.f,K_UI_FONT_BOLD, -5.f, 32.f, K_BUTTON_CHALLENGES) });
	tb.insert({ K_BUTTON_WEAPON,TextButton(600.f,K_UI_FONT_BOLD, -5.f, 32.f, K_BUTTON_WEAPON) });
}

static void LoadMusic(unordered_map<string, Music>& m)
{
	m.insert({ K_SONG_1, LoadMusicStream("Assests/Audio/Music/Song1.mp3") });
	m.insert({ K_SONG_2, LoadMusicStream("Assests/Audio/Music/Song2.mp3") });
	m.insert({ K_SONG_3, LoadMusicStream("Assests/Audio/Music/Song3.mp3") });
	for (auto& it : m)
		SetMusicVolume(it.second, 1.2f);

	m.insert({ K_SONG_PAUSE, LoadMusicStream("Assests/Audio/Music/Pause.mp3") });

	PlayMusicStream(m[K_SONG_PAUSE]);
}

static void LoadControls()
{	
	fstream inFile("TextFiles/Controls.txt");
	string temp;
	short i = 0;
	while (!inFile.eof())
	{
		std::getline(inFile, temp);
		stringstream ss(temp);
		short j = 0;
		while (ss >> temp)
		{
			int k = stoi(temp);
			switch (k)
			{			
			case KEY_ENTER:
				Ckeys[i][j] = "Enter";
					break;
			case KEY_RIGHT:
				Ckeys[i][j] = "Right";
					break;
			case KEY_LEFT:
				Ckeys[i][j] = "Left";
					break;
			case KEY_DOWN:
				Ckeys[i][j] = "Down";
					break;
			case KEY_UP:
				Ckeys[i][j] = "Up";
					break;
			case KEY_LEFT_SHIFT:
				Ckeys[i][j] = "LShift";
					break;
			case KEY_LEFT_CONTROL:
				Ckeys[i][j] = "LCtrl";
					break;
			case KEY_LEFT_ALT:
				Ckeys[i][j] = "LAlt";
					break;
			case KEY_RIGHT_SHIFT:
				Ckeys[i][j] = "RShift";
					break;
			case KEY_RIGHT_CONTROL:
				Ckeys[i][j] = "RCtrl";
					break;
			case KEY_RIGHT_ALT:
				Ckeys[i][j] = "RAlt";
					break;
			case KEY_KP_0:
				Ckeys[i][j] = "KP0";
					break;
			case KEY_KP_1:
				Ckeys[i][j] = "KP1";
					break;
			case KEY_KP_2:
				Ckeys[i][j] = "KP2";
					break;
			case KEY_KP_3:
				Ckeys[i][j] = "KP3";
					break;
			case KEY_KP_4:
				Ckeys[i][j] = "KP4";
					break;
			case KEY_KP_5:
				Ckeys[i][j] = "KP5";
					break;
			case KEY_KP_6:
				Ckeys[i][j] = "KP6";
					break;
			case KEY_KP_7:
				Ckeys[i][j] = "KP7";
					break;
			case KEY_KP_8:
				Ckeys[i][j] = "KP8";
					break;
			case KEY_KP_9:
				Ckeys[i][j] = "KP9";
					break;
			case KEY_KP_DECIMAL:
				Ckeys[i][j] = "KP.";
					break;
			case KEY_KP_DIVIDE:
				Ckeys[i][j] = "KP/";
					break;
			case KEY_KP_MULTIPLY:
				Ckeys[i][j] = "KP*";
					break;
			case KEY_KP_SUBTRACT:
				Ckeys[i][j] = "KP-";
					break;
			case KEY_KP_ADD:
				Ckeys[i][j] = "KP+";
					break;
			case KEY_KP_ENTER:
				Ckeys[i][j] = "KP_Enter";
					break;
			case KEY_KP_EQUAL:
				Ckeys[i][j] = "KP=";
				break;
			case KEY_SPACE:
				Ckeys[i][j] = "Space";
				break;
			default:
				Ckeys[i][j] = static_cast<char>(k);
				break;
			}
			++j;
		}
		++i;
	}
	inFile.close();
}