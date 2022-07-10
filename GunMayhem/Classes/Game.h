#pragma once
#include "Player.h"
#include "Crate.h"
#include "Perk.h"
#include "Item.h"
#include "Controls.h"
#include "Utils/Defines.h"
#include "TextButton.h"


class Game
{
private:
	inline static unordered_map<string, Music> music = {};
	inline static vector<Player> players = {};
	inline static list<Crate> crates = {};
	inline static unordered_map<string, Button> buttons = {};
	inline static unordered_map<string, TextButton> textButtons = {};
	inline static list<Item> items = {};
	inline static const vector<CBanners> controlsBanners = { CBanners(1), CBanners(2), CBanners(3),	CBanners(4) };
		
	static void ColorSelectionDraw();
	static void ColorSelectionLogic();
	static void PerkSelectionLogic();
	static void PerkSelectionDraw();
	static void PistolSelectionLogic();
	static void PistolSelectionDraw();
	static void ChangeNameLogic();
	
public:

	static void Initialize();
	static void TitleScreenLogic(GameScreen& cs);
	static void AddPlayer(const Color& color = WHITE, const string& name = "Player", const PlayerType& playertype = PlayerType::Player);
	static void RemovePlayer(const Player& p);
	static void RemovePlayer(const short& index);
	static void PlayerSetUpLogic(GameScreen& cs);
	static void PlayerSetUpDraw();
	static void GamePlayLogic(GameScreen& cs);
	static void GamePlayDraw();
	static void DeConstruct();
	static void TitleScreenDraw();
	static void ControlsLogic(GameScreen& cs);
	static void ConstrolsDraw();
};