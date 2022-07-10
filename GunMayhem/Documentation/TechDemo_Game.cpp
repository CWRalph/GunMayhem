#include "pch.h"
#include "Game.h"
#include "Item.h"
#include "Button.h"
#include "Utils/Collision.h"
#include "Utils/LoadAssests.h"
#include "Banner.h"

extern unordered_map<string, Perk> perks;
extern bool name;
extern short numOfLives;
extern string currentLevelKey;
extern bool titleScreen;

inline static vector<Banner> banners = {};
inline static short playerIndex = 0;
inline static Clicker mouse{};
inline static float crateTimer = 0.f;
inline static float winnerTimer = 4.f;
inline static float itemTimer = 14.f;
inline static bool colorSelection = false;
inline static bool perkSelection = false;
inline static bool gunSelection = false;
inline static bool isWinner = false;
inline static Music* GameplayMusic = nullptr;
inline static vector<Rectangle> colorColliders = {};
inline static vector<Rectangle> GunColliders = {};
inline static vector<Color> colors = {};
inline static vector<string> TitleButtons = {};
inline static Item item;

void Game::Initialize()
{
	players.reserve(4);
	sounds.reserve(20);
	music.reserve(7);
	textures.reserve(60);
	levels.reserve(5);
	guns.first.reserve(35);
	guns.second.reserve(10);
	perks.reserve(6);
	buttons.reserve(20);
	textButtons.reserve(20);
	colors.reserve(8);
	colorColliders.reserve(8);
	banners.reserve(4);
	TitleButtons.reserve(6);
	
	LoadGameTextures();
	LoadGuns();
	LoadLevels();
	LoadPerks();
	LoadButtons(buttons,textButtons);
	LoadMusic(music);

	item = Item(K_ITEM_UNDEFINED, 1.f, VariableType::Undefined);

	for (float x = 40.f; x < (225 * 4) + 40.f; x += 225.f)
		banners.push_back(Banner(x, 150.f));

	for (float j = 450.f; j < (100 * 2) + 450.f; j += 100.f)
		for (float i = 300.f; i < (100 * 4) + 300.f; i += 100.f)
			colorColliders.push_back({ i, j, 50.f, 50.f });

	for (float y = 350.f; y <= 450.f; y += 100.f)
		for (float x = 290.f; x < (125 * 3) + 290.f; x += 125.f)
			GunColliders.push_back({ x, y, 65.f, 40.f });

	colors.push_back(WHITE);
	colors.push_back(RED);
	colors.push_back(BLUE);
	colors.push_back(GREEN);
	colors.push_back(ORANGE);
	colors.push_back(PURPLE);
	colors.push_back(PINK);
	colors.push_back(YELLOW);

	
	//Keys for title screen buttons
	TitleButtons.push_back(K_BUTTON_CAMPAIGN);
	TitleButtons.push_back(K_BUTTON_CHALLENGES);
	TitleButtons.push_back(K_BUTTON_CREDITS);
	TitleButtons.push_back(K_BUTTON_CUSTOM);
	TitleButtons.push_back(K_BUTTON_OPTIONS);
	TitleButtons.push_back(K_BUTTON_WEAPON);

	items.push_back(Item(K_ITEM_1UP, 1.f, VariableType::Lives));
	items.push_back(Item(K_ITEM_MINIMIZE, 0.5f, VariableType::Scale));
	items.push_back(Item(K_ITEM_SPEED, 1.2f, VariableType::Speed));
	items.push_back(Item(K_ITEM_SHIELD, 0.3f, VariableType::Knockback));


	int e = Random(colors.size() - 1);
	AddPlayer(colors[e], "BOOT", PlayerType::AI);
	AddPlayer(colors[Random(colors.size() - 1, 0, { e })], "BOOT1", PlayerType::AI);

	for (auto& p : players)
		p.SetPrimary(std::next(guns.first.begin(), Random((int)guns.first.size() - 1))->second);
}

void Game::AddPlayer(const Color& color, const string& name, const PlayerType& playertype)
{
	short size = (short)players.size(), index = 0;
	//if (size >= GetNumberOfLines("TextFiles/Controls") || size >= 4) return;

	//players.push_back(Player((float)levels[currentLevelKey].GetXPositions()[size], -100.f, 0, 0, 0, 0, 0, 0, name, color, playertype));
	players.push_back(Player((float)Random(600, 200), -100.f, 0, 0, 0, 0, 0, 0, name, color, playertype));

	fstream inFile("TextFiles/Controls.txt");
	string temp = "";
	while (!inFile.eof() && index < players.size())
	{
		if(players[index].GetPlayerType() == PlayerType::Player)
		{
			std::getline(inFile, temp);
			vector<int> c;
			stringstream ss(temp);
			while (ss >> temp)
				c.push_back(stoi(temp));
			players[index].SetControls(c);
			if (players[index].GetPlayerType() == PlayerType::AI) players[index].SetName(name);
			else if(players[index].GetName().find("Player") != string::npos)
				players[index].SetName("Player" + to_string(index + 1));
		}
		++index;
	}
	inFile.close();
}

void Game::RemovePlayer(const Player& p)
{
	for (short i = 0; i < players.size(); i++)
		if (players[i] == p)
		{
			players.erase(players.begin() + i);
			for (short j = 0; j < players.size(); j++)
			{
				if (players[j].GetPlayerType() == PlayerType::AI) continue;
				if (players[j].GetName().find("Player") != string::npos)
					players[j].SetName("Player" + to_string(j + 1));
			}
			return;
		}
}
void Game::RemovePlayer(const short& index)
{
	if (index < players.size())
		players.erase(players.begin() + index);
	for (short j = 0; j < players.size(); j++)
	{
		if (players[j].GetPlayerType() == PlayerType::AI) continue;
		if (players[j].GetName().find("Player") != string::npos)
			players[j].SetName("Player" + to_string(j + 1));
	}
}

void Game::TitleScreenLogic(GameScreen& cs)
{
	FloorCollision(players, currentLevelKey);
	mouse.UpdatePosition();
	if (LEFT_CLICKED)
	{
		if (CheckCollisionRecs(mouse.GetCollider(), textButtons.at(K_BUTTON_CAMPAIGN).getCollider()))
		{
			cs = GameScreen::TITLE;
			titleScreen = false;
		}
		else if (CheckCollisionRecs(mouse.GetCollider(), textButtons.at(K_BUTTON_CUSTOM).getCollider()))
		{
			cs = GameScreen::PLAYERSETUP;
			while (!players.empty())
				RemovePlayer(players[0]);
			
			AddPlayer(colors[2]);
			AddPlayer(colors[Random(colors.size() - 1, 0, { 2 })], "BOOT", PlayerType::AI);
			titleScreen = false;

		}
		else if (CheckCollisionRecs(mouse.GetCollider(), textButtons.at(K_BUTTON_CHALLENGES).getCollider()))
		{
			cs = GameScreen::TITLE;
			titleScreen = false;
		}
		else if (CheckCollisionRecs(mouse.GetCollider(), textButtons.at(K_BUTTON_WEAPON).getCollider()))
		{
			cs = GameScreen::TITLE;
			titleScreen = false;
		}
		else if (CheckCollisionRecs(mouse.GetCollider(), textButtons.at(K_BUTTON_OPTIONS).getCollider()))
		{
			cs = GameScreen::TITLE;
			titleScreen = false;
		}
		else if (CheckCollisionRecs(mouse.GetCollider(), textButtons.at(K_BUTTON_CREDITS).getCollider()))
		{
			cs = GameScreen::TITLE;
			titleScreen = false;
		}
	}

	for (auto& p : players)
		p.Update(players);

	BulletCollsion(players);
	GrenadeCollision(players, currentLevelKey);
	ExplosionCollsion(players);

	//for (auto& i : players)
	//{
	//	switch (i.GetMovementSim())
	//	{
	//	case 0:
	//		//Jump and move right
	//		i.SetDirection(Direction::Right);
	//		if (i.GetOnPlatform())
	//		{
	//			i.SetVertVelocity(-870);
	//		}
	//		i.SetHorVelocity(150);
	//		i.UpdateSim();
	//		if (i.GetCollider().x > 600) i.SetMovementSim(3);
	//		break;
	//	case 1:
	//		//Jump and move left
	//		i.SetDirection(Direction::Left);
	//		if (i.GetOnPlatform())
	//		{
	//			i.SetVertVelocity(-870);
	//		}
	//		i.SetHorVelocity(-150);
	//		i.UpdateSim();
	//		if (i.GetCollider().x < 250) i.SetMovementSim(2);
	//		break;
	//	case 2:
	//		//Drop and move right
	//		i.SetDirection(Direction::Right);
	//		if (i.GetOnPlatform())
	//		{
	//			i.UpdatePosition(0, 2);
	//			i.SetMovementSim(6);
	//		}
	//		i.SetHorVelocity(150);
	//		i.UpdateSim();
	//		break;
	//	case 3:
	//		//Drop and move left
	//		i.SetDirection(Direction::Left);
	//		if (i.GetOnPlatform())
	//		{
	//			i.UpdatePosition(0, 2);
	//			i.SetMovementSim(5);
	//		}
	//		i.SetHorVelocity(-150);
	//		i.UpdateSim();
	//		break;
	//	case 4:
	//		//Move right
	//		i.SetDirection(Direction::Right);
	//		i.SetHorVelocity(150);
	//		i.UpdateSim();
	//		if (i.GetCollider().x > 600) i.SetMovementSim(1);
	//		break;
	//	case 5:
	//		//Move left
	//		i.SetDirection(Direction::Left);
	//		i.SetHorVelocity(-150);
	//		i.UpdateSim();
	//		if (i.GetCollider().x < 250) i.SetMovementSim(4);
	//		break;
	//	case 6:
	//		//Reset
	//		i.SetDirection(Direction::Left);
	//		i.SetHorVelocity(-150);
	//		i.UpdateSim();
	//		if (i.GetCollider().x < 250) i.SetMovementSim(0);
	//		break;
	//	default:
	//		break;
	//	}
	//}
}
void Game::TitleScreenDraw()
{
	levels[currentLevelKey].Draw();

	for (short i = 0; i < players.size(); i++)
		players[i].Draw(i, false);

	for (short i = 0; i < TitleButtons.size(); i++)
		textButtons[TitleButtons[i]].Draw(mouse.GetCollider());

}

void Game::PlayerSetUpLogic(GameScreen& cs)
{
	UpdateMusicStream(music[K_SONG_PAUSE]);
	mouse.UpdatePosition();
	short i = 0;
	if (!(colorSelection || gunSelection || name || perkSelection))
	{
		for (; i < players.size(); i++)
		{
			if (LEFT_CLICKED)
			{
				if (CheckCollisionRecs(mouse.GetCollider(), banners[i].GetColliders().at(K_BANNER_CLEAR_SLOT)))
				{
					RemovePlayer(i);
					return;
				}
				else if (CheckCollisionRecs(mouse.GetCollider(), banners[i].GetColliders().at(K_BANNER_PERK)))
				{
					perkSelection = true;
					playerIndex = i;
					return;
				}
				else if (CheckCollisionRecs(mouse.GetCollider(), banners[i].GetColliders().at(K_BANNER_COLOR)))
				{
					colorSelection = true;
					playerIndex = i;
					return;
				}
				else if (CheckCollisionRecs(mouse.GetCollider(), banners[i].GetColliders().at(K_BANNER_GUN)))
				{
					gunSelection = true;
					playerIndex = i;
					return;
				}
				else if (CheckCollisionRecs(mouse.GetCollider(), banners[i].GetColliders().at(K_PL_SETUP_NAME_BOX)))
				{
					name = true;
					playerIndex = i;
					SetMouseCursor(MOUSE_CURSOR_IBEAM);
					return;
				}
			}
		}

		for (; i < MAX_PLAYERS; i++)
		{
			if (LEFT_CLICKED)
			{
				if (CheckCollisionRecs(mouse.GetCollider(), banners[i].GetColliders().at(K_BANNER_PLAYER_CREATE)))
					AddPlayer(colors[Random((int)colors.size() - 1)]);
				else if (CheckCollisionRecs(mouse.GetCollider(), banners[i].GetColliders().at(K_BANNER_AI_CREATE)))
					AddPlayer(colors[Random((int)colors.size() - 1)], "Player", PlayerType::AI);
			}
		}

		if (players.size() > 1 && LEFT_CLICKED && CheckCollisionRecs(mouse.GetCollider(), buttons[K_START_BUTTON].getCollider()))
		{
			cs = GameScreen::GAMEPLAY;
			int r = Random(3, 0);
			while (music.find("Song" + to_string(r)) == music.end())
				r = Random(3, 0);

			GameplayMusic = &music.at("Song" + to_string(r));
			PlayMusicStream(*GameplayMusic);
			HideCursor();

			for (short i = 0; i < 50; i++)				
				AddPlayer(colors[Random(colors.size() - 1, 0, { 2 })], ("BOOT" + to_string(i + 2)).c_str(), PlayerType::AI);
	

			for (auto& p : players)
				p.SetKnockbackScale(0.3f, 0.5f);
		}
	}

	if (colorSelection)
		ColorSelectionLogic();
	if (perkSelection)
		PerkSelectionLogic();
	if (name)
		ChangeNameLogic();
	if (gunSelection)
		PistolSelectionLogic();
}
void Game::PerkSelectionLogic()
{
	if (IsKeyPressed(KEY_ESCAPE))
		perkSelection = false;
	mouse.UpdatePosition();
	if (LEFT_CLICKED)
		for (const auto& it : perks)
			if (CheckCollisionRecs(mouse.GetCollider(), it.second.getButton().getCollider()))
			{
				players[playerIndex].SetPerk(it.second);
				perkSelection = false;
			}

}
void Game::PistolSelectionLogic()
{
	mouse.UpdatePosition();
	for (short i = 0; i < GunColliders.size(); i++)
	{
		if (LEFT_CLICKED && CheckCollisionRecs(mouse.GetCollider(), GunColliders[i]))
		{
			auto it = guns.second.begin();
			std::advance(it, i);
			players[playerIndex].SetPistol(it->second);
			gunSelection = false;
			return;
		}
	}
	if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER))
		gunSelection = false;
}
void Game::ChangeNameLogic()
{
	if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER))
	{
		name = false;
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		return;
	}

	SetMousePosition(MeasureTextEx(fonts[K_UI_FONT], players[playerIndex].GetName().c_str(), 15.f, 1.f).x + banners[playerIndex].GetColliders().at(K_PL_SETUP_NAME_BOX).x + 12.f, banners[playerIndex].GetColliders().at(K_PL_SETUP_NAME_BOX).y + 25.f);
	string temp = players[playerIndex].GetName();
	if (IsKeyPressed(KEY_BACKSPACE) && !temp.empty())
		temp.pop_back();
	else
	{
		char c = GetCharPressed();
		if (c == '\0') return;
		if (IsKeyDown(KEY_LEFT_SHIFT))
			c = toupper(c);
		temp += c;
	}

	players[playerIndex].SetName(temp);
}
void Game::ColorSelectionLogic()
{
	if (IsKeyPressed(KEY_ESCAPE))
		colorSelection = false;
	for (short i = 0; i < colorColliders.size(); i++)
		if ((LEFT_CLICKED && CheckCollisionRecs(mouse.GetCollider(), colorColliders[i])))
		{
			players[playerIndex].SetColor(colors[i]);
			colorSelection = false;
		}

}

void Game::PlayerSetUpDraw()
{
	short i = 0;
	for (; i < players.size(); i++)
	{
		banners[i].Draw(players[i], mouse.GetCollider());
		//Draws Hitboxes for testing only
		/*for (const auto& it : banners[i].GetColliders())
		{
			DrawRectangleLines(it.second.x, it.second.y, it.second.width, it.second.height, RED);
		}*/
	}

	for (; i < MAX_PLAYERS; i++)
		banners[i].Draw();

	if (players.size() > 1)
	{
		if (CheckCollisionRecs(mouse.GetCollider(), buttons[K_START_BUTTON].getCollider()))
			buttons[K_START_BUTTON].Draw(1.f, DARKGRAY);
		else buttons[K_START_BUTTON].Draw();
	}

	if (colorSelection)
		ColorSelectionDraw();
	if (perkSelection)
		PerkSelectionDraw();
	if (gunSelection)
		PistolSelectionDraw();
}
void Game::PerkSelectionDraw()
{
	DrawTexture(textures[K_PERK_BG], 190, 200, WHITE);
	for (const auto& it : perks)
		it.second.Draw(mouse.GetCollider());
}
void Game::PistolSelectionDraw()
{
	DrawTexture(textures[K_PL_SETUP_GUN_BG], 150, 200, WHITE);
	short j = 0;
	bool exit = false;
	
	for (int i = SLIDER_START_Y; i < (25 * 4) + SLIDER_START_Y; i += 25)
		DrawRectangle(SLIDER_START_X, i, 75, SLIDER_HEIGHT, GRAY);

	for (const auto& it : guns.second)
	{
		float scale = 1.75f;
		if (CheckCollisionRecs(mouse.GetCollider(), GunColliders[j]))
		{
			scale = 2.35f;
			DrawTextEx(fonts[K_UI_FONT], it.second.GetDisplayName().c_str(), { 400.f, 540.f }, 25.f, 1.f, WHITE);
			DrawRectangle(SLIDER_START_X, SLIDER_START_Y, 75 * abs(it.second.GetBullet().getKnockback()) / 250, SLIDER_HEIGHT, LIGHTGRAY);			
			DrawRectangle(SLIDER_START_X, SLIDER_START_Y + 25, 75 * (0.17 / abs(it.second.GetRateOfFire())), SLIDER_HEIGHT, LIGHTGRAY);
			DrawRectangle(SLIDER_START_X, SLIDER_START_Y + 50, 75 * abs(it.second.GetAmmo()) / 25, SLIDER_HEIGHT, LIGHTGRAY);
			DrawRectangle(SLIDER_START_X, SLIDER_START_Y + 75, 75 * abs(it.second.GetRecoil()) / 140, SLIDER_HEIGHT, LIGHTGRAY);			
			exit = true;
		}
		DrawTextureEx(textures[it.second.GetName()], { GunColliders[j].x, GunColliders[j].y }, 0.f, scale, WHITE);
		++j;
	}
	if (!exit)
	{
		DrawTextEx(fonts[K_UI_FONT], "...", { 450.f, 540.f }, 25.f, 1.f, WHITE);
		for (int i = SLIDER_START_Y; i < (25 * 4) + SLIDER_START_Y; i += 25)
			DrawRectangle(SLIDER_START_X, i, 10, SLIDER_HEIGHT, LIGHTGRAY);
	}
	DrawTextEx(fonts[K_UI_FONT], "Firepower", { 375.f, SLIDER_START_Y }, 12.f, 1.f, WHITE);
	DrawTextEx(fonts[K_UI_FONT], "Rate Of Fire", { 365.f, SLIDER_START_Y + 25 }, 12.f, 1.f, WHITE);
	DrawTextEx(fonts[K_UI_FONT], "Ammo Capacity", { 350.f, SLIDER_START_Y + 50 }, 12.f, 1.f, WHITE);
	DrawTextEx(fonts[K_UI_FONT], "Recoil", { 400.f, SLIDER_START_Y + 75 }, 12.f, 1.f, WHITE);
}
void Game::ColorSelectionDraw()
{
	DrawTexture(textures[K_PL_SETUP_COLOR_BG], 150, 325, WHITE);

	for (short i = 0; i < colorColliders.size(); i++)
	{
		DrawRectangle(colorColliders[i], colors[i]);
		if (CheckCollisionRecs(mouse.GetCollider(), colorColliders[i]))
			DrawRectangle(colorColliders[i]);
	}

}

void Game::GamePlayLogic(GameScreen& cs)
{
	//Player Logic
	UpdateMusicStream(*GameplayMusic);
	short playersAlive = 0;
	if (isWinner)
	{
		winnerTimer -= dt;
		if (winnerTimer < 0.f)
		{
			cs = GameScreen::PLAYERSETUP;
			winnerTimer = 0.f;
			isWinner = false;
			StopMusicStream(*GameplayMusic);
			ResumeMusicStream(music[K_SONG_PAUSE]);
			GameplayMusic = nullptr;
			ShowCursor();
			for (short i = 0; i < players.size(); i++)
			{
				players[i].SetCollider((float)levels[currentLevelKey].GetXPositions()[i], -1000.f);
				players[i].SetLives();
				players[i].Reset(-100.f);
			}
		}		
		return;
	}

	

	for (short i = 0; i < players.size(); i++)
	{
		if (!players[i].IsDead()) ++playersAlive;
		players[i].Update(players);
	}		
	if (playersAlive <= 1)
	{
		isWinner = true;
		winnerTimer = 4.f;
		return;		
	}


	//Crate Logic 
	if (crates.empty())
	{
		crateTimer += dt;
		if (crateTimer > 6.7f)
		{
			crates.push_back(Crate());
			crateTimer = 0;
		}
	}
	else
	{
		for (auto& it : crates)
			if (it.Update())
			{
				crates.clear();
				break;
			}
	}

	//Item Logic
	if (item.GetType() == VariableType::Undefined)
	{
		itemTimer += dt;
		if (itemTimer > 14.3f)
		{
			item = *std::next(items.begin(), Random((int)items.size() - 1));
			int randPlatform = Random(levels[currentLevelKey].getPlatformCount() - 1);
			int minX = levels[currentLevelKey].getPlatforms()[randPlatform].x;
			int maxX = minX + levels[currentLevelKey].getPlatforms()[randPlatform].width;
			while (minX < 0)
				minX += 25;
      
			while (maxX > screenWidth)
				maxX -= 25;

			item.SetPosition((float)Random(maxX - item.GetCollider().width, minX), (float)levels[currentLevelKey].getPlatforms()[randPlatform].y - item.GetCollider().height);
			itemTimer = 0.f;
		}
	}
	else
		ItemCollsion(players, item);
		

	FloorCollision(players, currentLevelKey);
	FloorCollision(crates, currentLevelKey);
	GrenadeCollision(players, currentLevelKey);

	if (CrateCollision(players, crates))
	{
		crates.clear();
		PlaySound(sounds[K_CRATE_SOUND]);
	}

	
	ExplosionCollsion(players);
	BulletCollsion(players);
}
void Game::GamePlayDraw()
{
	levels[currentLevelKey].Draw();

	for (short i = 0; i < (short)players.size(); i++)
		players[i].Draw(i);

	for (const auto& it : crates)
		it.Draw();

	item.Draw();

	if (isWinner)
	{
		short i = 0;
		for (; i < (short)players.size(); i++)
			if (!players[i].IsDead())
				break;

		DrawTextEx(fonts[K_UI_FONT_BOLD], "WINNER:", {screenWidth * 0.5f - 100, screenHeight * 0.5f}, 100.f, 2.1f, ORANGE);
		DrawTextEx(fonts[K_UI_FONT_BOLD], players[i].GetName().c_str(), {screenWidth * 0.5f - 100, screenHeight * 0.5f + 100.f}, 85.f, 2.1f, BLACK);
		DrawTextEx(fonts[K_UI_FONT_BOLD], to_string((int)winnerTimer).c_str(), { screenWidth * 0.5f, screenHeight * 0.5f + 200 }, 75.f, 2.1f, RED);
	}

	DrawFPS(5, 5);
}

void Game::DeConstruct()
{
	for (auto& it : textures)
		UnloadTexture(it.second);

	for (auto& it : fonts)
		UnloadFont(it.second);

	GameplayMusic = nullptr;

	for (auto& it : music)
	{
		if (IsMusicStreamPlaying(it.second))
			StopMusicStream(it.second);
		UnloadMusicStream(it.second);
	}

	StopSoundMulti();
	for (auto& it : sounds)
	{
		if (IsSoundPlaying(it.second))
			StopSound(it.second);
		UnloadSound(it.second);
	}

	ShowCursor();
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}