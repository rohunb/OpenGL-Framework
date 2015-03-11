#include "Game.h"

Game::Game()
{
	engine = new Engine();
	engine->RegisterGame(this);
	engine->Run();
}


Game::~Game()
{
	delete engine;
	engine = nullptr;
}

void Game::Update(float dt)
{
	//printf("Game update\n");
}

//void Game::CreateNewGame(Game* game)
//{
//	engine->game = game;
//}
