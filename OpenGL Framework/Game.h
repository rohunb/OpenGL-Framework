#pragma once
//#include <stdio.h>
#include "Engine.h"

class Game
{
public:
	Game();
	virtual ~Game();

	Engine* engine;

	virtual void Update(float dt);
	//virtual void CreateNewGame(Game* game);
};

