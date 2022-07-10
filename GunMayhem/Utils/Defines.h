#pragma once
#define screenHeight 950
#define screenWidth 950
#define GRAVITY 975
#define HITBOX_HEIGHT 83.f
#define MAX_PLAYER_SPEED 600
#define FRICTION 700 
#define UI_YPOS 830
#define GRENADE_VELOCITY 100.f
#define EXPLOSION_MAGNITUDE 800.f
#define EXPLOSION_LIFESPAN 1.f
#define MAX_PLAYERS 4
#define SLIDER_HEIGHT 15
#define SLIDER_START_Y 570
#define SLIDER_START_X 450
#define MAX_SINGLE_JUMP_X 190
#define SINGLE_JUMP_Y 60
#define MAX_DOUBLE_JUMP_X 420 
#define DOUBLE_JUMP_Y 120
#define TIME_IN_AIR_SINGLE_JUMP	0.35f
#define TIME_IN_AIR_DOUBLE_JUMP	0.81f
#define AI_RUN_TO_MIDDLE_TIME 0.63f

#define K_PLAYER "Player"
#define K_UI "UI"

#define CBAN_LEFT "dLeft"
#define CBAN_RIGHT "cRight"
#define CBAN_JUMP "aJump"
#define CBAN_DROP "bDrop"
#define CBAN_SHOOT "eShoot"
#define CBAN_BOMB "fBomb"
#define CBAN_PROMPT "Prompt"

#define K_GREY_SMG "GreySMG"
#define K_CHEAP "CheapSMG"
#define K_CHROME_SMG "ChromeSMG"
#define K_POLICE "PoliceSMG"
#define K_TATICAL_SMG "TaticalSMG"
#define K_COMPACT "CompactAR"

#define K_ASSAULT_CARBINE "AssaultCarbine"
#define K_BULLPUP_MG "BullpupMachineGun"
#define K_CLASSIC "ClassicAR"
#define K_LONG_RANGE "LongRangeAR"
#define K_RELIABLE "ReliableAR"
#define K_TOP_LOAD "TopLoadMachineGun"

#define K_ASSAULT_SG "AssaultShotgun"
#define K_CHROM_SG "ChromeShotgun"
#define K_STANDAR_SG "StandardShotgun"
#define K_STUBBY_SG "StubyShotgun"

#define K_BULLPUP_SNIPER "BullpupSniper"
#define K_RUGGED_SNIPER "RuggedSniper"
#define K_SINGLE_SHOT "SingleShotSniper"

#define K_COOL_PISTOL "CoolPistol"
#define K_FIFTY_EIGHT_PISTOL "FiftyEight"
#define K_ANGRY_COW_PISTOL "AngryCow"
#define K_GLICK_PISTOL "Glick"
#define K_SAND_HAWK_PISTOL "SandHawk"
#define K_SNAKE_PISTOL "Snake"

#define K_BULLET "Bullet"
#define K_UI_FONT "UIFont"
#define K_CRATE "Crate"
#define K_LEVEL1 "Level1"
#define K_LEVEL2 "Level2"
#define K_LEVEL1_BG "Level1BG"
#define K_LEVEL2_BG "Level2BG"
#define K_LEVEL1_PLAT "Level1Platform"
#define K_LEVEL2_PLAT "Level2Platform"
#define K_OFF_SCREEN_INDICATOR_X "IndicatorX"
#define K_OFF_SCREEN_INDICATOR_Y "IndicatorY"
#define K_GRENADE "Grenade"
#define K_SHOOT_SOUND "shoot"
#define K_EXPLOSION_SOUND "explosion"
#define K_CRATE_SOUND "crateSound"
#define K_PERK_BG "PerkBG"
#define	K_PERK_EXTRA_NADES "ExtraNades"
#define	K_PERK_WEIGHT "Weight"
#define	K_PERK_PISTOLAMMO "PistolAmmo"
#define	K_PERK_TRIPLE_JUMP "TripleJump"
#define	K_PERK_NO_RECOIL "NoRecoil"
#define	K_PERK_RANDOM_GUN "RanGun"
#define	K_PERK_NULL "NULL"
#define K_BANNER_CLEAR_SLOT "ClearSlot"
#define K_PL_SETUP_EMPTY_BANNER "Empty"
#define K_PL_SETUP_NAME_BOX "Name"
#define K_UI_START_BUTTON "Start"
#define K_PL_SETUP_BANNER_OUTLINE "Outline"
#define K_BANNER_COLOR "Color"
#define K_BANNER_PERK "Perk"
#define K_BANNER_GUN "Gun"
#define K_CONTINUE_BUTTON "Continue"
#define K_BANNER_PLAYER_CREATE "PlayerCreate"
#define K_BANNER_AI_CREATE "AICreate"
#define K_START_BUTTON "Start"
#define K_PL_SETUP_COLOR_BG "ColorBG"
#define K_PL_SETUP_GUN_BG "GunBG"

#define K_SONG_1 "Song1"
#define K_SONG_2 "Song2"
#define K_SONG_3 "Song3"
#define K_SONG_PAUSE "Pause"

#define K_BUTTON_CAMPAIGN "CAMPAIGN"
#define K_BUTTON_CUSTOM "CUSTOM GAME"
#define K_BUTTON_CHALLENGES "CHALLENGES"
#define K_BUTTON_WEAPON "WEAPON LIBRARY"
#define K_BUTTON_OPTIONS "OPTIONS"
#define K_BUTTON_CREDITS "CREDITS"


#define K_ITEM_1UP "1up"
#define K_ITEM_SPEED "Speed"
#define K_ITEM_SHIELD "Shield"
#define K_ITEM_MINIMIZE "Mini"
#define K_ITEM_UNDEFINED "Undefined"

#define K_SOUND_SMALL_PISTOL "sPistol"
#define K_SOUND_AR "AR"
#define K_SOUND_SNIPER "Sniper"
#define K_SOUND_LARGE_PISTOL "lPistol"
#define K_SOUND_SHOTGUN "Shotgun"
#define K_SOUND_SMG "SMG"

#define K_UI_FONT_BOLD "CandaraBold"

#define LEFT_CLICKED IsMouseButtonPressed(MOUSE_BUTTON_LEFT)

enum class GameScreen { TITLE, CONTROLS, MODESELECTION, MAPSECLECTION, PLAYERSETUP, GAMEPLAY };