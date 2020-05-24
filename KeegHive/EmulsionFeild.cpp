#include "stdafx.h"
#include "EmulsionFeild.h"

namespace GANnet{

	EmulsionFeild::EmulsionFeild(LearningAITestbed * bed, std::vector<int> hLayersNUM, std::vector<int> inputNeuronTotal, std::vector<std::vector<int>> hiddenNeuronTotal,
		std::vector<int> outputNeuronTotal, std::vector<std::vector<std::vector<FuncTypes>>> ilFuncs, std::vector<std::vector<std::vector<FuncTypes>>> hlFuncs, std::vector<std::vector<std::vector<FuncTypes>>> olFuncs,
		float lRate, int cycleTotal, float acceptableErrorRate, std::vector<std::vector<float>> tainingIns, std::vector<std::vector<float>> trainingOuts){

		std::cout << "EmulsionFeild Constructor Started" << std::endl;
		parent = bed;
		numberOfNetworks = 1;

		vNetDataStructObject.resize(1);
		CleanTheNetStruct();
		//set up advanced learning rate support aka minimal accepted error rate
		//set up inputNeuron value support
		mindPool.resize(numberOfNetworks);
		CleanThePool();
		int y = 0;
		for (int x = 0; x <= 1 - 1; x++) {
			nnDataHolder tempStructOBJ;
			tempStructOBJ.hLayerTotal = hLayersNUM.at(x);
			tempStructOBJ.iNeuronTotal = inputNeuronTotal.at(x);
			tempStructOBJ.hNeuronTotal = hiddenNeuronTotal;
			tempStructOBJ.oNeuronTotal = outputNeuronTotal.at(x);
			tempStructOBJ.inputFed = true;
			tempStructOBJ.iLayerAutoFillInfoBools = false;
			tempStructOBJ.acceptableErrorTarget = acceptableErrorRate;
			
			tempStructOBJ.oLayerAutoFillInfoBools = false;
			tempStructOBJ.iTOhLayerAutoFillInfoBools = true;

			tempStructOBJ.hTOoLayerAutoFillInfoBools = true;
			tempStructOBJ.iLayerFuncTypes = ilFuncs;
			tempStructOBJ.hLayerFuncTypes = hlFuncs;
			tempStructOBJ.oLayerFuncTypes = olFuncs;
			tempStructOBJ.learningRate = lRate;
			tempStructOBJ.learningCycleTotal = cycleTotal;
			tempStructOBJ.trainingOututs = trainingOuts;
			tempStructOBJ.trainingInputs = tainingIns;
			vNetDataStructObject.push_back(tempStructOBJ);
			AddToPool(new NeuralNetwork(this, tempStructOBJ));
		}
		std::cout << "TST" << std::endl;

	}

	EmulsionFeild::EmulsionFeild(LearningAITestbed * bed, int connectedMinds)
	{
		std::cout << "EmulsionFeild Constructor Started" << std::endl;
		parent = bed;
		numberOfNetworks = connectedMinds;
		mindPool.resize(numberOfNetworks);
		CleanThePool();
		std::cout << "EmulsionFeild Constructed Ended" << std::endl;
	}

	EmulsionFeild::~EmulsionFeild()
	{
		std::cout << "end of EmulsionFeild Destructor" << std::endl;
		for (int i = 0; i < this->mindPool.size() - 1; i++) {
			mindPool.at(i)->~NeuralNetwork();
			delete mindPool.at(i);
		}
	}
	
	std::vector<NeuralNetwork*> EmulsionFeild::AddToPool(NeuralNetwork* nw)
	{
		mindPool.push_back(nw);
		std::cout << "Neural Network added to local Emulsion Pool" << std::endl;
		//numberOfNetworks++;
		return mindPool;
	}
	
	void EmulsionFeild::CleanThePool()
	{
		for (int x = 0; x < mindPool.size(); x++)
		{
			if (mindPool[x] == nullptr) {
				mindPool.erase(mindPool.begin() + x);
				x--;
			}
			else {
				
			}
			std::cout << "Pools Clean" << std::endl;

		}
	}
	void EmulsionFeild::CleanTheNetStruct()
	{
		/*	*/
		for (int x = 0; x < vNetDataStructObject.size(); x++)
		{
			if ((vNetDataStructObject[x].hNeuronTotal.size() == 0) /*&& (vNetDataStructObject[x].oNeuronTotal.size() == 0) && (vNetDataStructObject[x].iNeuronTotal.size() == 0)*/)
			{
				vNetDataStructObject.erase(vNetDataStructObject.begin() + x);
				x--;
			}
			else {
				std::cout << "else triggered for DataNeuralNetstruct Cleaner" << std::endl;
			}
			std::cout << "vNetStruct Clean" << std::endl;

		}
	}
	EmulsionFeild::rouletWheel EmulsionFeild::modifyChanceWheel(ganHive* hiveLoc)
	{
		return rouletWheel();
	}
	void EmulsionFeild::defaultChanceWheel(ganHive* hiveLoc)
	{
		hiveLoc->chanceStruct.gNodeBias = 1;
		hiveLoc->chanceStruct.growingBias = 1;
		hiveLoc->chanceStruct.gSynBias = 1;
		hiveLoc->chanceStruct.numberOfSpins = 1;
		hiveLoc->chanceStruct.pNodeBias = 1;
		hiveLoc->chanceStruct.pruningBias = 1;
		hiveLoc->chanceStruct.pSynBias = 1;
		hiveLoc->chanceStruct.sbiasRELU = 1;
		hiveLoc->chanceStruct.sbiasLRELU = 1;
		hiveLoc->chanceStruct.sbiasLU = 1;
		hiveLoc->chanceStruct.sbiasSIGM = 1;
		hiveLoc->chanceStruct.sbiasTANH = 1;
		hiveLoc->chanceStruct.switchingBias = 1;
	}
	void EmulsionFeild::generateHive(int populationSize, std::vector<NeuralNetwork*> specimans, std::string name)
	{
		hiveHolder.push_back(new ganHive());
		hiveHolder.at(hiveHolder.size())->nm = name;
		hiveHolder.at(hiveHolder.size())->populationSize = populationSize;
		defaultChanceWheel(hiveHolder.at(hiveHolder.size()));
		hiveHolder.at(hiveHolder.size())->initialGANS = specimans;
	} 
	EmulsionFeild::ganHive* EmulsionFeild::constructHive(int populationSize, std::vector<NeuralNetwork*> startingRoster, std::string name)
	{
		ganHive* hive;
		hive->populationSize = populationSize;
		hive->initialGANS = startingRoster;
		hive->nm = name;
		defaultChanceWheel(hive);
		return hive;
	}
	void EmulsionFeild::evolveHive(ganHive * ghLoc)
	{
		for (int z = 0; z < ghLoc->populationSize; z++) {
			for (int x = 0; x < ghLoc->chanceStruct.numberOfSpins; x++) {
				float rangeMax = ghLoc->chanceStruct.pruningBias * 100 + ghLoc->chanceStruct.growingBias * 100 + ghLoc->chanceStruct.switchingBias * 100;
				float rangeMin = 1;
				float r = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
				if (r <= ghLoc->chanceStruct.pruningBias * 100) {
					rangeMax = ghLoc->chanceStruct.pNodeBias * 100 + ghLoc->chanceStruct.pSynBias * 100;
					float a = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
					if (a <= ghLoc->chanceStruct.pNodeBias * 100) {
						ghLoc->ganBoys.at(z)->pruneRandomNeuron();
					}
					else if (a > ghLoc->chanceStruct.pNodeBias * 100) {
						ghLoc->ganBoys.at(z)->pruneRandomSynapse();
					}

				}
				else if (r > ghLoc->chanceStruct.pruningBias * 100 && r <= ghLoc->chanceStruct.pruningBias * 100 + ghLoc->chanceStruct.growingBias) {
					rangeMax = ghLoc->chanceStruct.gNodeBias * 100 + ghLoc->chanceStruct.gSynBias * 100;
					float a = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
					if (a <= ghLoc->chanceStruct.gNodeBias * 100) {
						ghLoc->ganBoys.at(z)->addRandomNeuron();
					}
					else if (a > ghLoc->chanceStruct.gNodeBias * 100) {
						ghLoc->ganBoys.at(z)->addRandomSynapse();
					}
				}
				else if (r > ghLoc->chanceStruct.pruningBias * 100 + ghLoc->chanceStruct.growingBias * 100) {
					rangeMax = ghLoc->chanceStruct.sbiasRELU * 100 + ghLoc->chanceStruct.sbiasLRELU * 100 + ghLoc->chanceStruct.sbiasLU * 100 + ghLoc->chanceStruct.sbiasSIGM * 100 + ghLoc->chanceStruct.sbiasTANH * 100;
					float a = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
					int enumval;
					if (a <= ghLoc->chanceStruct.sbiasRELU * 100) {
						enumval = 0;
					}
					else if (a > ghLoc->chanceStruct.sbiasRELU * 100 && a <= ghLoc->chanceStruct.sbiasRELU * 100 + ghLoc->chanceStruct.sbiasLU * 100) {
						enumval = 1;
					}
					else if (a > ghLoc->chanceStruct.sbiasRELU * 100 + ghLoc->chanceStruct.sbiasLRELU * 100 && a <= ghLoc->chanceStruct.sbiasRELU * 100 + ghLoc->chanceStruct.sbiasLRELU * 100 + ghLoc->chanceStruct.sbiasLU * 100) {
						enumval = 2;
					}
					else if (a > ghLoc->chanceStruct.sbiasRELU * 100 + ghLoc->chanceStruct.sbiasLRELU * 100 + ghLoc->chanceStruct.sbiasLU * 100 && a <= ghLoc->chanceStruct.sbiasRELU * 100 + ghLoc->chanceStruct.sbiasLRELU * 100 + ghLoc->chanceStruct.sbiasLU * 100 + ghLoc->chanceStruct.sbiasSIGM * 100) {
						enumval = 3;
					}
					else if (a > ghLoc->chanceStruct.sbiasRELU * 100 + ghLoc->chanceStruct.sbiasLRELU * 100 + ghLoc->chanceStruct.sbiasLU * 100 + ghLoc->chanceStruct.sbiasSIGM * 100 && a <= ghLoc->chanceStruct.sbiasRELU * 100 + ghLoc->chanceStruct.sbiasLRELU * 100 + ghLoc->chanceStruct.sbiasLU * 100 + ghLoc->chanceStruct.sbiasSIGM * 100 + ghLoc->chanceStruct.sbiasTANH * 100) {
						enumval = 4;
					}
					ghLoc->ganBoys.at(z)->switchRandomNeuronFunc(enumval);
				}				
			}
		}
		//still todo test the AI against eachother and return the best one
	}
};