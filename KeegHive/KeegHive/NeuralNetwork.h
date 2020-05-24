#pragma once
#include"EmulsionFeild.h"
#include "Vector.h"
#include <math.h>   
using namespace MATH;
namespace GANnet{
class NeuralNetwork
	{
	public:
		friend class NodeLayer;
		friend class SynapseLayer;
	
		NeuralNetwork(EmulsionFeild * eFeild, EmulsionFeild::nnDataHolder dHolder);
		NeuralNetwork(EmulsionFeild* eFeild, int inputNum, int hiddenNum, int outputNum, std::vector<float> learningTarget); //limited constructor
		~NeuralNetwork();
		//remember to clean up the base constructer in the world and main
		EmulsionFeild* parentFeild;
		std::vector<float> target;
		std::vector<float> score;
		std::vector<float> cost;
		std::vector<std::vector<float>>hWebs;
		float ittrTotal;
		float learningRate; //diffrent than the alphaVal but similar mechanically, it is on the right side of the back prop equasion and has to do with how the AI converges on answers.
		float alphaVal; //diffrent than the learning rate but similar mechanically, it is on the left side of the back prop equasion has to do with how the AI converges on answers.
		float acceptableErrorRate;

		struct learningDataSet{
			std::vector<std::vector<float>>expectedInputData;
			std::vector<std::vector<float>>expectedOutputData;
		};

		learningDataSet learningSet;

		NodeLayer* inputContainer;
		std::vector<NodeLayer*> hiddenContainer;
		NodeLayer* outputContainer;
	
		SynapseLayer* iTOhContainer;
		std::vector<SynapseLayer*> hTOhContainer;
		SynapseLayer* hTOoContainer;

		void changeTarget(float newTarg, int outputPos);
		void modTarget(float modVal, int outputPos);

		void mocNN();
		std::vector<std::vector<float>> randomiseData();
		void Fprop(std::vector<float>inputdata);
		void gradiantDescent();
		void bProp();
		void genCost(int outputPos);
		float genError();
		float getError();
		void compareResult();
		//void fcGen();
		void genMSEinput();
		void clearGradiants();

		float sigmoidFunc(float val);
		float linearFunc(float val);
		float tanhFunc(float val);
		float recLineFunc(float val);
		float leakyRecLineFunc(float val);

		float sigmoidPrime(float val);
		float fakeSigmoidPrime(float val);
		float linearPrime(float val);
		float tanhPrime(float val);
		float recLinePrime(float val);
		float leakyRecLinePrime(float val);
		//edit enums for these functiontypes also make softmax and maxout functions https://en.wikipedia.org/wiki/Activation_function
	
		//for NEAT support, genetic methods
		void pruneRandomSynapse();
		void pruneRandomNeuron();
		void addRandomSynapse();
		void addRandomNeuron();
		void switchRandomNeuronFunc(int enumVal);

		//this is used with the multi layer hidden support
		void sortG1();
		void sortG2();
		int getG1();
		int getG2();
		//Shader* shaderInfo;
		//GLfloat vertInfo[4] = {0,0,0,0,0,0,0,0,0,0,0,0};
		//GLfloat colorData[4] = {1,0,0,0,1,0,0,0,1,1,1,1};
		//std::vector<Sprite*>neuronSpriteList;
		//std::vector<Sprite*>synapseSpriteList;
		//void setupSprites();
		//void setupShaderInfo(Shader* shInfo, GLfloat verts[], GLfloat colors[] );

	private:
		int inputLayerTotal; int hiddenLayerTotal; int outputLayerTotal;
		int hiddenLayersSortedG1;
		int hiddenLayersSortedG2;
		bool inputValFed;

		FuncTypes returnFType(int enumVal);
		void setUpBiasVals();
		};//end of NeuralNetwork
};