#ifndef R_GAME_H_
#define R_GAME_H_

#include "Engine.h"
namespace rb
{
	class Game
	{
	public:
		Engine* engine;

		Game();
		virtual ~Game();
		virtual void Update(float dt);
		//virtual void CreateNewGame(Game* game);
	};
}
#endif // !R_GAME_H_
