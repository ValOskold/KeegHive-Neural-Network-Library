#include "stdafx.h"
#include "wonwonEngine.h"

//using namespace GANnet;
wonwonEngine* wonwonEngine::instance = NULL;

wonwonEngine::wonwonEngine(GameImplement* game)
{
	//Attempt to initialize GLFW
	if (!glfwInit()) {
		//GLFW failed to initialize

		printf("GLFW INIT ERROR");
	}


	this->game = game;
	renderer = new Renderer(window);
	//Create an instance of the managers
	//modelManager = new pModelManager();
	//materialManager = new pMaterialManager();
	//imageManager = new pImageManager();
	//shaderManager = new pShaderManager();
	//lightManager = pLightManager::instance();
	//audioManager = new pAudioManager();
	//scriptManager = new pScriptManager();

	//Give the modelmanager the other managers
	//modelManager->setMaterialManager(materialManager);
	//modelManager->setImageManager(imageManager);

	//Create an instance of the factory and give it the managers
	//resourceFactory = pResourceFactory::instance();
	//resourceFactory->setModelManager(modelManager);
	//resourceFactory->setMaterialManager(materialManager);
	//resourceFactory->setImageManager(imageManager);
	//resourceFactory->setShaderManager(shaderManager);
	//resourceFactory->setAudioManager(audioManager);
	//resourceFactory->setScriptManager(scriptManager);

	//create an instance of the sceneManager
	//sceneManager = pSceneManager::instance();
}

wonwonEngine::~wonwonEngine()
{
	//Destroy the window
	glfwDestroyWindow(window);

	//End glfw processes
	glfwTerminate();

	//Destruct the renderer
	renderer->~Renderer();
	delete renderer;

	//TODO: CLEARING KEYS AND VALUES CAUSES AN ERROR!!!
	//delete resourceFactory;
	//delete modelManager;
	//delete materialManager;
	//delete imageManager;


	//Delete managers and factory
	//modelManager->~pModelManager();
	//materialManager->~pMaterialManager();
	//imageManager->~pImageManager();
	//resourceFactory->~pResourceFactory();
}

void wonwonEngine::CreateWindow(GLint width, GLint height, char * title)
{
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	windowWidth = width;
	windowHeight = height;

	if (!window) {
		//Window or OpenGL context creation failed
	}

	//Set the preferred OpenGL version to 4.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//Set the minimum supported OpenGL version to 3.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Set the context to the current window
	glfwMakeContextCurrent(window);

	//Start GLEW
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		//glew failed to initialize
		printf("GLEW INIT ERROR");

	}

	//Enable gl debug messages
	glEnable(GL_DEBUG_OUTPUT);


	//Set up input mode
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Get version info, do with these what you will (probably print to log)
	const GLubyte* renderVersion = glGetString(GL_RENDERER); //Renderer version
	const GLubyte* glVersion = glGetString(GL_VERSION); //OpenGL Version

	printf("Renderer: %s\n", renderVersion);
	printf("Supported OGL Version: %s\n", glVersion);

	//renderer = pRenderer::instance();
	//renderer->setWindowRef(window);

	//Now that a context exists, input can be initialized
	SetupInput();
}

void wonwonEngine::Start()
{
	//Start the loop!
	doLoop();
}

void wonwonEngine::SetupInput()
{
	//Create an instance of and set up the input handler
	inputManager = pInputManager::instance(window);
	inputHandler = pInputHandler::instance(window);
	inputManager->Initialize(window, inputHandler);

	//Set error callback
	inputHandler->setErrorCallback(inputManager->error_callback);

	//Set context
	inputHandler->setCurrentContext(window);

	//Set up key callbacks
	inputHandler->setKeyCallback(window, inputManager->advancedKey_callback);

}

void wonwonEngine::doLoop()
{
	//While the window isn't being closed, call the looped functions
	game->onStart();
	//sceneManager->startScene();
	//scriptManager->StartScripts();
	//Create the last time
	double lastTick = glfwGetTime();
	do {
		//Get the current time
		double currentTick = glfwGetTime();
		//Calculate delta time from the time differences (in ms) * 10 (for seconds)
		double deltaTime = (currentTick - lastTick) * 10;
		//Store the current tick as the last one, then run loop
		lastTick = currentTick;
		glfwPollEvents();
		inputManager->inputUpdate(deltaTime);
		game->onUpdate(deltaTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//sceneManager->updateScene(deltaTime);
		//scriptManager->UpdateScripts(deltaTime);
		game->onPostUpdate();
		game->onPreRender();
		//sceneManager->renderScene(pRenderer::instance());
		game->onRender();
		game->onPostRender();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
	this->~wonwonEngine();
	//sceneManager->endScene();
	//scriptManager->StopScripts();
	game->onEnd();
}
