#pragma once
#include "LearningAITestbed.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace MATH;
namespace GANnet{

	class EmulsionFeild{
		friend class EmulsionFeild;
		friend class NeuralNetwork;
		public:
			
			EmulsionFeild(LearningAITestbed * bed, std::vector<int> hLayersNUM, std::vector<int> inputNeuronTotal, std::vector<std::vector<int>> hiddenNeuronTotal,
				std::vector<int> outputNeuronTotal, std::vector<std::vector<std::vector<FuncTypes>>> ilFuncs, std::vector<std::vector<std::vector<FuncTypes>>> hlFuncs, std::vector<std::vector<std::vector<FuncTypes>>> olFuncs, 
				float lRate, int cycleTotal, float acceptableErrorRate, std::vector<std::vector<float>> tainingIns, std::vector<std::vector<float>> trainingOuts);
			//bigconstructor

			EmulsionFeild(LearningAITestbed* bed, int connectedMinds); //INCOMPLETE CONSTRUCTOR USED WHEN CREATING THE WORLDOBJ
			~EmulsionFeild();
		
			LearningAITestbed* parent;
			std::vector<NeuralNetwork*> mindPool;
			std::vector<NeuralNetwork*>AddToPool(NeuralNetwork* nw);
			//add remove function also make sure adding to pools increces the number of networks int


			struct nnDataHolder {
				NNType nType;
				int hLayerTotal;
				int iNeuronTotal;
				std::vector<std::vector<int>> hNeuronTotal;
				int oNeuronTotal;
				bool iLayerAutoFillInfoBools;
				std::vector<std::vector<bool>> hLayerAutoFillInfoBools;
				bool oLayerAutoFillInfoBools;
				bool iTOhLayerAutoFillInfoBools;
				std::vector<std::vector<bool>> hTOhLayerAutoFillInfoBools;
				bool hTOoLayerAutoFillInfoBools;
				std::vector<std::vector<std::vector<FuncTypes>>> iLayerFuncTypes;
				std::vector<std::vector<std::vector<FuncTypes>>> hLayerFuncTypes;
				std::vector<std::vector<std::vector<FuncTypes>>> oLayerFuncTypes;
				float learningRate;
				int learningCycleTotal;
				float acceptableErrorTarget;
				bool inputFed;
				std::vector<std::vector<float>> trainingOututs;
				std::vector<std::vector<float>> trainingInputs;
			};

			struct rouletWheel {
				int numberOfSpins;
				//flat bias
				float pruningBias;
				float growingBias;
				float switchingBias;
				//specialised bias
				float pSynBias;
				float pNodeBias;
				float gSynBias;
				float gNodeBias;
				float sNodeFBias;
				//Sub-SwitchingBias
				float sbiasRELU = 1;
				float sbiasLRELU = 1;
				float sbiasLU = 1;
				float sbiasSIGM = 1;
				float sbiasTANH = 1;
			};
			
			struct ganHive {
				std::string nm;
				rouletWheel chanceStruct;
				int populationSize;
				std::vector<NeuralNetwork*>ganBoys;
				NeuralNetwork* bestBoy;
				std::vector<NeuralNetwork*>bestBoyArchive;
				std::vector<NeuralNetwork*>initialGANS;
			};

			ganHive* constructHive(int populationSize, std::vector<NeuralNetwork*>startingRoster, std::string name);
			void evolveHive(ganHive* ghLoc);

	private:
		void CleanThePool();
		void CleanTheNetStruct();
		int numberOfNetworks;
		std::vector<nnDataHolder> vNetDataStructObject;
		std::vector<ganHive*> hiveHolder;
		rouletWheel modifyChanceWheel(ganHive* hiveLoc);
		void defaultChanceWheel(ganHive* hiveLoc);
		void generateHive(int populationSize, std::vector<NeuralNetwork*>specimans, std::string name);
		
	};
};