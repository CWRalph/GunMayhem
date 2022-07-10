#include "pch.h"
#include "Classes/Game.h"
#include "SymbolDefines.h"


int main()
{
	InitWindow(screenWidth, screenHeight, "Gun Pandemonium");
	InitAudioDevice();
	SetMasterVolume(0.1f);
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
	SetExitKey(NULL);
	Image icon = LoadImage("Assests/GameAssests/Icon.png");
	SetWindowIcon(icon);
	GameScreen currentScreen = GameScreen::TITLE;

	Game::Initialize();

	while (!WindowShouldClose())
	{
		dt = GetFrameTime();

		switch (currentScreen)
		{
		case GameScreen::TITLE:
			Game::TitleScreenLogic(currentScreen);
			break;
		case GameScreen::CONTROLS:
			Game::ControlsLogic(currentScreen);
			break;
		case GameScreen::MODESELECTION:
			break;
		case GameScreen::MAPSECLECTION:
			break;
		case GameScreen::PLAYERSETUP:
			Game::PlayerSetUpLogic(currentScreen);
			break;
		case GameScreen::GAMEPLAY:
			Game::GamePlayLogic(currentScreen);
			break;

		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		switch (currentScreen)
		{
		case GameScreen::TITLE:
			Game::TitleScreenDraw();
			break;
		case GameScreen::CONTROLS:
			Game::ConstrolsDraw();
			break;
		case GameScreen::MODESELECTION:
			break;
		case GameScreen::MAPSECLECTION:
			break;
		case GameScreen::PLAYERSETUP:
			Game::PlayerSetUpDraw();
			break;
		case GameScreen::GAMEPLAY:
			Game::GamePlayDraw();
			break;
		}
		EndDrawing();
	}
	
	exitGame = true;

	Game::DeConstruct();
	UnloadImage(icon);
	CloseWindow();
	CloseAudioDevice();

	return 0;
}