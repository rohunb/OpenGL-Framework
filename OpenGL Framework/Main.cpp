//#include "Engine.h"
#include <iostream>
#include "Game.h"
//#include "TestApp.h"
//Engine* engine;
//TestApp* testApp;
using namespace rb;
Game* game;
//void Render();
void Update(float dt);
//void HandleTimer(int ID);
//void Keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
	//glutInit(&argc, argv);
	game = new Game();
	/*engine = new Engine();
	engine->RegisterUpdateCallback(Update);
	engine->Run();*/



	/*glutDisplayFunc(Render);
	glutTimerFunc(500, HandleTimer, 1);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();*/
	
	//testApp = new TestApp();


	delete game;
	game = nullptr;
}
void Update(float dt)
{
	std::cout << "Update Callback " << dt << std::endl;
}
//void Render()
//{
//	engine->Render();
//	
//}
//void HandleTimer(int ID)
//{
//	engine->Update();
//
//	glutPostRedisplay();
//	glutTimerFunc(16, HandleTimer, 1);
//}
//void Keyboard(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case 27:
//		delete engine;
//		engine = nullptr;
//		exit(0);
//		break;
//	default:
//		break;
//	}
//}