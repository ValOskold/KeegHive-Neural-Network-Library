#pragma once
#include "wonwonEngine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>
//#include "neuralnetFileReader.h"
#include "Vector.h"
#include "LearningAITestbed.h"
#include "EmulsionFeild.h"
#include "LoadShaders.h"
#include "Sprite.h"

//namespace tinyxml2;
//using namespace MATH;
using namespace GANnet;

class TestScene : public GameImplement
{

public:
	//screenImplement ws;

	//set up the testbed give it the number of feilds and a mindsActive vec<int> of the number of minds per emulsion feild
	LearningAITestbed* world;
	int numberOfFeilds = 1;
	// World Var^

	//each emFeild requires these variables
	EmulsionFeild* emFeild;
	int mindsActive = 1; //not implimented yet but this vector should hold the number of minds per emulsion feild
						 //EMFeild Var^

	NNType type = Backprop;
	float targ = 0.0005f; //redundant due to training sets
	float lRate = 0.4f;
	int cycleTotal = 1000;
	float acceptableErrorRate = 0.0005;
	//Neural Net Var^

	std::vector<int> inputNeuronList = { 2 };
	//std::vector <bool> iLayerAutoFillInfo = { true }; //either make one of these for each layer or make it like a map or key thing that takes a bool and also a nodelayertype specifter enum
	std::vector<std::vector<std::vector<FuncTypes>>> iLayerFuncTypes = { { {SIGM}, {SIGM} } };
	//std::vector<std::vector<std::vector<FuncTypes>>> iLayerFuncTypes = { { {SIGM }, { SIGM }, { SIGM} } };
	//Input Layer Vars^

	std::vector<int> hiddenLayers = { 2 };
	std::vector<std::vector <int>> hiddenNeuronList = { { 3 }, {3 } };
	std::vector<std::vector<std::vector<FuncTypes>>> hLayerFuncTypes = { { { SIGM }, { SIGM }, { SIGM } }, { { SIGM },{ SIGM },{ SIGM } } };
	//Hidden Layer Vars^

	std::vector<int> outputNeuronList = { 1 };
	std::vector<std::vector<std::vector<FuncTypes>>> oLayerFuncTypes = {{ { SIGM } }};
	//Output Layer Vars^

	std::vector<std::vector<float>> expectedInput = { { { 0 },{ 0 } },{ { 0 },{ 1 } },{ { 1 },{ 0 } },{ { 1 },{ 1 } } };
	std::vector<std::vector<float>> expectedOutput = { { { 0 } },{ { 1} },{ { 1 } },{ { 0 } } };

	//SynapseLayer Vars^ for the hidden to output layers
	//bool FC = true; //this limits how synapses acts between layers 
	//end of neural net vars

	std::vector<Sprite*>neuronSpriteList;
	std::vector<Sprite*>synapseSpriteList;
	std::vector<std::vector<Sprite*>>nnNeuronSprites;
	std::vector<std::vector<Sprite*>>nnSynapseSprites;
	std::vector<std::vector<Vec4>>synapseSpriteLayers;
	TestScene();
	~TestScene();
	
	void giveEngineReference(wonwonEngine* engine);

	// Inherited via GameImplement
	virtual void onStart() override;
	virtual void onUpdate(GLdouble deltaTime) override;
	virtual void onPostUpdate() override;
	virtual void onPreRender() override;
	virtual void onRender() override;
	virtual void onPostRender() override;
	virtual void onEnd() override;

private:
	wonwonEngine* engine;
	bool isLinkedToEngine;
};