// KeegHive.cpp : Defines the entry point for the console application.
#include "wonwonEngine.h"
#include "TestScene.h"
#include "stdafx.h"

TestScene* game;
wonwonEngine* engine;
int windowWidth = 1920;
int windowHeight = 1080;
char* windowTitle = "RNN TestBed";

int main(int argc, char** argv)
{
	//Create a test scene to use the engine
	game = new TestScene();

	//Set up the engine and get the reference
	engine = wonwonEngine::setupEngine(game);

	//Feed the engine pointer to the game
	game->giveEngineReference(engine);

	//Set the engine window
	engine->CreateWindow(windowWidth, windowHeight, windowTitle);

	//Start the engine loop
	engine->Start();

	return 0;
}