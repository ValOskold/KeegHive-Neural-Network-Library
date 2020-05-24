#pragma once
#include <vector>
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "GameImplement.h"
#include "pInputManager.h"
#include "Renderer.h"

class wonwonEngine
{
public:
	static wonwonEngine* setupEngine(GameImplement* game) {
		if (instance == nullptr) {
			instance = new wonwonEngine(game);
		}

		return instance;
	}

	static wonwonEngine* GetInstance() {
		if (instance == nullptr) {
			//LogManager::instance()->error("Attempted to get engine instance without a game implement!");
			instance = new wonwonEngine(nullptr);
		}
		return instance;
	}

	wonwonEngine(GameImplement* game);
	~wonwonEngine();
	//Placeholder window creation method
	void CreateWindow(GLint width, GLint height, char* title);
	void Start();

	Renderer* renderer;
	//pResourceFactory* resourceFactory;
	//pLightManager* lightManager;
	//pSceneManager* sceneManager;
	pInputManager* inputManager;
	pInputHandler* inputHandler;

	float windowWidth;
	float windowHeight;
	GLFWwindow* window;
private:
	static wonwonEngine* instance;

	//Input requires being set up AFTER the window is ready
	void SetupInput();

	void doLoop();
	GameImplement* game;
	//pModelManager* modelManager;
	//pMaterialManager* materialManager;
	//pImageManager* imageManager;
	//pShaderManager* shaderManager;
	//pAudioManager* audioManager;
	//pSceneGraph* sceneGraph;
	//pScriptManager* scriptManager;

};

