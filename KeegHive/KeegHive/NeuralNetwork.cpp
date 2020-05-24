#include "stdafx.h"
#include "NeuralNetwork.h"

namespace GANnet{
	NeuralNetwork::NeuralNetwork(EmulsionFeild * eFeild, EmulsionFeild::nnDataHolder dHolder)
	{
		std::cout << "NeuralNetwork Constructor Entered" << std::endl;
		parentFeild = eFeild;

		ittrTotal = dHolder.learningCycleTotal;
		//learningRate = dHolder.learningRate;
		learningRate = 0.1;
		hiddenLayerTotal = dHolder.hLayerTotal;
		inputLayerTotal = 1;
		outputLayerTotal = 1;
		std::vector<float> tmpTarg = {0};
		target = tmpTarg;
		hiddenLayersSortedG1 = 0;
		hiddenLayersSortedG2 = 0;
		inputValFed = dHolder.inputFed;
		acceptableErrorRate = dHolder.acceptableErrorTarget;
		int ittr = 0;

		if (inputValFed) {
			for (int x = 0; x < inputLayerTotal; x++) {
				inputContainer = new NodeLayer(this, NodeTypes::INPUT, dHolder.iNeuronTotal, dHolder.iLayerFuncTypes.at(0), ittr);
				std::cout << "Adding element #" << x << " of #" << inputLayerTotal << " to a NeuralNetworks inputContainer" << std::endl;
				ittr++;
			}
			int y = 0;
			for (int x = 0; x < hiddenLayerTotal; x++) {
				hiddenContainer.push_back(new NodeLayer(this, NodeTypes::HIDDEN, dHolder.hNeuronTotal.at(x).at(0), dHolder.hLayerFuncTypes.at(x), ittr)); std::cout << "Adding element #" << x << " of #" << dHolder.hNeuronTotal.size() << " to a NeuralNetworks hiddenContainer" << std::endl;
				//hiddenContainer.push_back(new NodeLayer(this, NodeTypes::HIDDEN, dHolder.hNeuronTotal.at(x).at(0), dHolder.hLayerAutoFillInfoBools.at(x).at(0), dHolder.vHlayerInfo.at(x).y, dHolder.vHlayerInfo.at(x).x, dHolder.funcType, ittr)); std::cout << "Adding element #" << x << " of #" << dHolder.hNeuronTotal.size() << " to a NeuralNetworks hiddenContainer" << std::endl;
				y++;
				ittr++;
			}
			for (int x = 0; x < outputLayerTotal; x++) {
				outputContainer = new NodeLayer(this, NodeTypes::OUTPUT, dHolder.oNeuronTotal, dHolder.oLayerFuncTypes.at(0), ittr);
				std::cout << "Adding element #" << x << " of #" << dHolder.oNeuronTotal << " to a NeuralNetworks outputContainer" << std::endl;
				ittr++;
			}
		}
		else if (!inputValFed) {
			for (int x = 0; x < inputLayerTotal; x++) {
				inputContainer = new NodeLayer(this, NodeTypes::INPUT, dHolder.iNeuronTotal, dHolder.iLayerFuncTypes.at(0), ittr);
				std::cout << "Adding element #" << x << " of #" << inputLayerTotal << " to a NeuralNetworks inputContainer" << std::endl;
				ittr++;
			}

			int y = 0;
			for (int x = 0; x < hiddenLayerTotal; x++) {
				hiddenContainer.push_back(new NodeLayer(this, NodeTypes::HIDDEN, dHolder.hNeuronTotal.at(x).at(0), dHolder.hLayerFuncTypes.at(x), ittr)); std::cout << "Adding element #" << x << " of #" << dHolder.hNeuronTotal.size() << " to a NeuralNetworks hiddenContainer" << std::endl;
				y++;
				ittr++;
			}
			for (int x = 0; x < outputLayerTotal; x++) {
				outputContainer = new NodeLayer(this, NodeTypes::OUTPUT, dHolder.oNeuronTotal, dHolder.oLayerFuncTypes.at(0), ittr);
				std::cout << "Adding element #" << x << " of #" << dHolder.oNeuronTotal << " to a NeuralNetworks outputContainer" << std::endl;
				ittr++;
			}
		}

		iTOhContainer = new SynapseLayer(this, NetTypes::INPUTtoHIDDEN, inputContainer, hiddenContainer.at(0), 1, 0, dHolder.iTOhLayerAutoFillInfoBools);
		for (int i = 0; i < dHolder.hLayerTotal - 1; i++) {
			hTOhContainer.push_back(new SynapseLayer(this, NetTypes::HIDDENtoHIDDEN, hiddenContainer.at(i), hiddenContainer.at(i + 1), 1, 0, true));
		}

		hTOoContainer = new SynapseLayer(this, NetTypes::HIDDENtoOUTPUT, hiddenContainer.at(dHolder.hLayerTotal - 1), outputContainer, 1, 0, dHolder.hTOoLayerAutoFillInfoBools); //maybe make dHolder.hLayerTotal -1

		for (int x = 0; x < outputContainer->nodeList.size(); x++) {
			score.push_back(0);
			cost.push_back(0);
		}

		setUpBiasVals();

		if (dHolder.trainingInputs.size() != 0 && dHolder.trainingOututs.size() != 0) {
			learningSet.expectedInputData = dHolder.trainingInputs;
			learningSet.expectedOutputData = dHolder.trainingOututs;
			//compareResult();
		}

		bProp();

		std::cout << "a Neural Networks outputContainers are accounted for" << std::endl;
		std::cout << "NeuralNetwork Constructor Ended" << std::endl;

		//addRandomNeuron(); //fix it so its not a full wireing on create
		//addRandomSynapse();
	}

	NeuralNetwork::NeuralNetwork(EmulsionFeild* eFeild, int inputNum, int hiddenNum, int outputNum, std::vector<float> learningTarget)
	{
		std::cout << "NeuralNetwork partial Constructor Entered" << std::endl;
		parentFeild = eFeild;
		hiddenLayerTotal = hiddenNum;
		inputLayerTotal = inputNum;
		outputLayerTotal = outputNum;
		//target = learningTarget;
		target = std::vector<float>();
		std::cout << "NeuralNetwork partial Constructor Exited" << std::endl;
	}

	NeuralNetwork::~NeuralNetwork()
	{
		std::cout << "end of empty NeuralNetwork destructor" << std::endl;
	}

	void NeuralNetwork::changeTarget(float newTarg, int outputPos)
	{
		std::cout << "a NeuralNetworks target has been set to a new val of #" << newTarg << std::endl;
		this->target.at(outputPos) = newTarg;
	}

	void NeuralNetwork::modTarget(float modVal, int outputPos)
	{
		std::cout << "a NeuralNetworks target has been modifyed by a new val of #" << modVal << std::endl;
		this->target.at(outputPos) += modVal;
	}

	void NeuralNetwork::mocNN()
	{
		float tmp = 0.01;
		for (int i = 0; i < iTOhContainer->web.size(); i++) {
			iTOhContainer->web.at(i)->weight = tmp;
			tmp = tmp + 0.05;
		}
		for (int h = 0; h < hTOhContainer.size(); h++) {
			for (int i = 0; i < hTOhContainer.at(h)->web.size(); i++) {
				hTOhContainer.at(h)->web.at(i)->weight = tmp;
				tmp = tmp + 0.05;
			}
		}
		for (int i = 0; i < hTOoContainer->web.size(); i++) {
			hTOoContainer->web.at(i)->weight = tmp;
			tmp = tmp + 0.05;
		}
	}

	std::vector<std::vector<float>> NeuralNetwork::randomiseData()
	{
		//what i want to do is take my inputdataset and return a randomly ordered dataset we can fprop with to train the network efficiantly
		std::vector<std::vector<float>> mocDataset = std::vector<std::vector<float>>();
		for (int s = 0; s < learningSet.expectedInputData.size(); s++) {
			mocDataset.push_back(std::vector<float>());
			for (int sn = 0; sn < learningSet.expectedInputData.at(s).size(); sn++) {
				mocDataset.at(s).push_back(learningSet.expectedInputData.at(s).at(sn));
			}
		}
		
		//now the mocDataset should be loaded with the inputdata we need to randomlyselect from its elements and push it to a randomDataset
		std::vector<std::vector<float>>randomisedDataSet = std::vector<std::vector<float>>();
		int randMin = 0;
		int randMax = mocDataset.size();
		int count = randMax;
		for (int x = 0; x < randMax; x++) {
			//count--;
			int r = 0;
			//if (randMax - count == 0) {
			if (count - randMin == 0) {
				 r = 0;
			}
			else {
				r = randMin + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / (count - randMin)));
			}
			if (r == mocDataset.size()) {
				randomisedDataSet.push_back(mocDataset.at(r - 1));
				mocDataset.erase(mocDataset.begin() + r -1);

			}
			else {
				randomisedDataSet.push_back(mocDataset.at(r));
				mocDataset.erase(mocDataset.begin() + r);
			}
			count--;
		}
		
		return randomisedDataSet;
	}

	void NeuralNetwork::Fprop(std::vector<float>data) {
		float tmp = 0;
		score = std::vector<float>();
		for (int i = 0; i < data.size(); i++) {
			inputContainer->nodeList.at(i + 1)->valPreActivator = data.at(i);
			inputContainer->nodeList.at(i + 1)->valPostActivator = data.at(i);
		}
		compareResult(); //This trys the find each target for each output neuron given the inputs given to the network

		for (int x = 0; x < iTOhContainer->neuronGroup2.size(); x++) {
			tmp = 0;
			for (int y = 0; y < iTOhContainer->neuronGroup2.at(x)->dendriticConnections.size(); y++) {
				tmp += iTOhContainer->neuronGroup2.at(x)->dendriticConnections.at(y)->weight * iTOhContainer->neuronGroup2.at(x)->dendriticConnections.at(y)->cell1->valPreActivator;
			}
			iTOhContainer->neuronGroup2.at(x)->setPreActivatorVal(tmp);
			tmp = 0;
			if (iTOhContainer->neuronGroup2.at(x)->functionType == FuncTypes::LRELU) {
				iTOhContainer->neuronGroup2.at(x)->setPostActivatorVal(leakyRecLineFunc(iTOhContainer->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
			}
			else if (iTOhContainer->neuronGroup2.at(x)->functionType == FuncTypes::LU) {
				iTOhContainer->neuronGroup2.at(x)->setPostActivatorVal(linearFunc(iTOhContainer->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
			}
			else if (iTOhContainer->neuronGroup2.at(x)->functionType == FuncTypes::RELU) {
				iTOhContainer->neuronGroup2.at(x)->setPostActivatorVal(recLineFunc(iTOhContainer->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
			}
			else if (iTOhContainer->neuronGroup2.at(x)->functionType == FuncTypes::SIGM) {
				iTOhContainer->neuronGroup2.at(x)->setPostActivatorVal(sigmoidFunc(iTOhContainer->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
			}
			else if (iTOhContainer->neuronGroup2.at(x)->functionType == FuncTypes::TANH) {
				iTOhContainer->neuronGroup2.at(x)->setPostActivatorVal(tanhFunc(iTOhContainer->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
			}

		}

		for (int l = 0; l < hTOhContainer.size(); l++) {
			for (int x = 0; x < hTOhContainer.at(l)->neuronGroup2.size(); x++) {
				tmp = 0;
				for (int y = 0; y < hTOhContainer.at(l)->neuronGroup2.at(x)->dendriticConnections.size(); y++) {
					tmp += hTOhContainer.at(l)->neuronGroup2.at(x)->dendriticConnections.at(y)->weight *  hTOhContainer.at(l)->neuronGroup2.at(x)->dendriticConnections.at(y)->cell1->valPostActivator;
				}
				hTOhContainer.at(l)->neuronGroup2.at(x)->setPreActivatorVal(tmp);
				tmp = 0;
				if (hTOhContainer.at(l)->neuronGroup2.at(x)->functionType == FuncTypes::LRELU) {
					hTOhContainer.at(l)->neuronGroup2.at(x)->setPostActivatorVal(leakyRecLineFunc(hTOhContainer.at(l)->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
				}
				else if (hTOhContainer.at(l)->neuronGroup2.at(x)->functionType == FuncTypes::LU) {
					hTOhContainer.at(l)->neuronGroup2.at(x)->setPostActivatorVal(linearFunc(hTOhContainer.at(l)->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
				}
				else if (hTOhContainer.at(l)->neuronGroup2.at(x)->functionType == FuncTypes::RELU) {
					hTOhContainer.at(l)->neuronGroup2.at(x)->setPostActivatorVal(recLineFunc(hTOhContainer.at(l)->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
				}
				else if (hTOhContainer.at(l)->neuronGroup2.at(x)->functionType == FuncTypes::SIGM) {
					hTOhContainer.at(l)->neuronGroup2.at(x)->setPostActivatorVal(sigmoidFunc(hTOhContainer.at(l)->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
				}
				else if (hTOhContainer.at(l)->neuronGroup2.at(x)->functionType == FuncTypes::TANH) {
					hTOhContainer.at(l)->neuronGroup2.at(x)->setPostActivatorVal(tanhFunc(hTOhContainer.at(l)->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
				}
			}
		}

		for (int x = 0; x < hTOoContainer->neuronGroup2.size(); x++) {
			tmp = 0;
			for (int y = 0; y < hTOoContainer->neuronGroup2.at(x)->dendriticConnections.size(); y++) {
				tmp += hTOoContainer->neuronGroup2.at(x)->dendriticConnections.at(y)->weight * hTOoContainer->neuronGroup2.at(x)->dendriticConnections.at(y)->cell1->valPostActivator;
			}
			hTOoContainer->neuronGroup2.at(x)->setPreActivatorVal(tmp);
			tmp = 0;
			if (hTOoContainer->neuronGroup2.at(x)->functionType == FuncTypes::LRELU) {
				hTOoContainer->neuronGroup2.at(x)->setPostActivatorVal(leakyRecLineFunc(hTOoContainer->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
			}
			else if (hTOoContainer->neuronGroup2.at(x)->functionType == FuncTypes::LU) {
				hTOoContainer->neuronGroup2.at(x)->setPostActivatorVal(linearFunc(hTOoContainer->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
			}
			else if (hTOoContainer->neuronGroup2.at(x)->functionType == FuncTypes::RELU) {
				hTOoContainer->neuronGroup2.at(x)->setPostActivatorVal(recLineFunc(hTOoContainer->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
			}
			else if (hTOoContainer->neuronGroup2.at(x)->functionType == FuncTypes::SIGM) {
				hTOoContainer->neuronGroup2.at(x)->setPostActivatorVal(sigmoidFunc(hTOoContainer->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
			}
			else if (hTOoContainer->neuronGroup2.at(x)->functionType == FuncTypes::TANH) {
				hTOoContainer->neuronGroup2.at(x)->setPostActivatorVal(tanhFunc(hTOoContainer->neuronGroup2.at(x)->getPreVal())); //feed in the preActivationVal but mod it with a sigmoidfunction
			}
			score.push_back(hTOoContainer->neuronGroup2.at(x)->getPostVal());
			//float a = inputContainer->nodeList.at(0)->valPostActivator;
			//float b = inputContainer->nodeList.at(1)->valPostActivator;
			//float c = inputContainer->nodeList.at(2)->valPostActivator;
			//float d = target.at(0);
			//float e = outputContainer->nodeList.at(0)->valPostActivator;
			//std::cout << "";
		}
	}

	void NeuralNetwork::gradiantDescent() //could the problem be me not updating my bias stuff properly?
	{	//get the first set of partial Derivitives for all output neurons
		for (int x = 0; x < this->outputContainer->nodeList.size(); x++) {
			//in this case its easy its the product of the feed forward network contrasted to the expected result
			//target - guesse = error
			float tmp = (target.at(x) - outputContainer->nodeList.at(x)->valPostActivator);
			outputContainer->nodeList.at(x)->partialDeriviative.push_back(tmp);
		}

		//now that we have the partial derivitives we can use them to get the gradiant
		for (int x = 0; x < hTOoContainer->web.size(); x++) {
			float tmp = 0;
			if (hTOoContainer->web.at(x)->cell2->functionType == FuncTypes::RELU) {
				tmp = recLinePrime(hTOoContainer->web.at(x)->cell2->valPostActivator);
			}
			else if (hTOoContainer->web.at(x)->cell2->functionType == FuncTypes::LRELU) {
				tmp = leakyRecLinePrime(hTOoContainer->web.at(x)->cell2->valPostActivator);
			}
			else if (hTOoContainer->web.at(x)->cell2->functionType == FuncTypes::LU) {
				tmp = linearPrime(hTOoContainer->web.at(x)->cell2->valPostActivator);
			}
			else if (hTOoContainer->web.at(x)->cell2->functionType == FuncTypes::SIGM) {
				tmp = sigmoidPrime(hTOoContainer->web.at(x)->cell2->valPreActivator);
			}
			else if (hTOoContainer->web.at(x)->cell2->functionType == FuncTypes::TANH) {
				tmp = tanhPrime(hTOoContainer->web.at(x)->cell2->valPostActivator);
			}
			hTOoContainer->web.at(x)->gradiant.push_back(hTOoContainer->web.at(x)->cell2->partialDeriviative.at(hTOoContainer->web.at(x)->cell2->partialDeriviative.size() - 1) * tmp * hTOoContainer->web.at(x)->cell1->valPostActivator);
		}

		for (int w = 0; w < hTOoContainer->web.size(); w++) {
			float tmp = 0;
			float tmpProduct = 0;
			for (int a = 0; a < hTOoContainer->web.at(w)->cell2->axonalConnections.size(); a++) {
				//to get the hidden errors we sum the functions f = 1)multiply the error of the output neron with 2)the weight of the connection between the hidden neuron x output neuron from step 1 but 3) divided that by the sum of all other synapses attacked to the output
				tmp += hTOoContainer->web.at(w)->cell2->axonalConnections.at(a)->weight;
			}
			tmpProduct = tmp / hTOoContainer->web.at(w)->weight;
		}

		for (int lhs = 0; lhs < hTOoContainer->neuronGroup1.size(); lhs++) { //here im ittertating through the last hidden layer
			float tmp = 0;
			float tmpProduct = 0;
			float sum = 0;
			for (int ld = 0; ld < hTOoContainer->neuronGroup1.at(lhs)->axonalConnections.size(); ld++) { //here i am itterating through the right hand synapses from the hidden neuron from the last nested loop
				for (int ldrha = 0; ldrha < hTOoContainer->neuronGroup1.at(lhs)->axonalConnections.at(ld)->cell2->dendriticConnections.size(); ldrha++) { //here i am itterating though the left hand synapses from neurons attached to the synapses in the past itter
					tmp += hTOoContainer->neuronGroup1.at(lhs)->axonalConnections.at(ld)->cell2->dendriticConnections.at(ldrha)->weight;
				}
				//in the matrix math it says i dont need the cancel out from tmp so for a control ill set it to 1 to see if it converges better
				tmp = 1; //remove after test
				tmpProduct = hTOoContainer->neuronGroup1.at(lhs)->axonalConnections.at(ld)->weight / tmp;
				tmpProduct = tmpProduct * hTOoContainer->neuronGroup1.at(lhs)->axonalConnections.at(ld)->cell2->partialDeriviative.at(hTOoContainer->neuronGroup1.at(lhs)->axonalConnections.at(ld)->cell2->partialDeriviative.size()-1);
				sum += tmpProduct;
			}
			hTOoContainer->neuronGroup1.at(lhs)->partialDeriviative.push_back(sum);
		}

		//for (int h = hTOhContainer.size(); h > 0; h--) { //here im ittertating through the last hidden layer
		for (int h = hTOhContainer.size() -1; h >= 0; h--) { //here im ittertating through the last hidden layer
			for (int lhs = 0; lhs < hTOhContainer.at(h)->neuronGroup1.size(); lhs++) { 
				float tmp = 0;
				float tmpProduct = 0;
				float sum = 0;
				for (int ld = 0; ld < hTOhContainer.at(h)->neuronGroup1.at(lhs)->axonalConnections.size(); ld++) { //here i am itterating through the right hand synapses from the hidden neuron from the last nested loop
					for (int ldrha = 0; ldrha < hTOhContainer.at(h)->neuronGroup1.at(lhs)->axonalConnections.at(ld)->cell2->dendriticConnections.size(); ldrha++) { //here i am itterating though the left hand synapses from neurons attached to the synapses in the past itter
						tmp += hTOhContainer.at(h)->neuronGroup1.at(lhs)->axonalConnections.at(ld)->cell2->dendriticConnections.at(ldrha)->weight;
					}
					//in the matrix math it says i dont need the cancel out from tmp so for a control ill set it to 1 to see if it converges better
					tmp = 1; //remove after test
					tmpProduct = hTOhContainer.at(h)->neuronGroup1.at(lhs)->axonalConnections.at(ld)->weight / tmp;
					tmpProduct = tmpProduct * hTOhContainer.at(h)->neuronGroup1.at(lhs)->axonalConnections.at(ld)->cell2->partialDeriviative.at(hTOhContainer.at(h)->neuronGroup1.at(lhs)->axonalConnections.at(ld)->cell2->partialDeriviative.size() - 1);
					sum += tmpProduct;
				}
				hTOhContainer.at(h)->neuronGroup1.at(lhs)->partialDeriviative.push_back(sum);
			}
		}

		//now that we have the partial derivitives we can use them to get the gradiants for the hidden to hidden and input layers
		for (int h = 0; h < hTOhContainer.size(); h++) {
			for (int x = 0; x < hTOhContainer.at(h)->web.size(); x++) {
				float tmp = 0;
				if (hTOhContainer.at(h)->web.at(x)->cell2->functionType == FuncTypes::RELU) {
					tmp = recLinePrime(hTOhContainer.at(h)->web.at(x)->cell2->valPostActivator);
				}
				else if (hTOhContainer.at(h)->web.at(x)->cell2->functionType == FuncTypes::LRELU) {
					tmp = leakyRecLinePrime(hTOhContainer.at(h)->web.at(x)->cell2->valPostActivator);
				}
				else if (hTOhContainer.at(h)->web.at(x)->cell2->functionType == FuncTypes::LU) {
					tmp = linearPrime(hTOhContainer.at(h)->web.at(x)->cell2->valPostActivator);
				}
				else if (hTOhContainer.at(h)->web.at(x)->cell2->functionType == FuncTypes::SIGM) {
					tmp = sigmoidPrime(hTOhContainer.at(h)->web.at(x)->cell2->valPreActivator);
				}
				else if (hTOhContainer.at(h)->web.at(x)->cell2->functionType == FuncTypes::TANH) {
					tmp = tanhPrime(hTOhContainer.at(h)->web.at(x)->cell2->valPostActivator);
				}
				hTOhContainer.at(h)->web.at(x)->gradiant.push_back(hTOhContainer.at(h)->web.at(x)->cell2->partialDeriviative.at(hTOhContainer.at(h)->web.at(x)->cell2->partialDeriviative.size() - 1) * tmp * hTOhContainer.at(h)->web.at(x)->cell1->valPostActivator);
			}
		}
		for (int x = 0; x < iTOhContainer->web.size(); x++) {
			float tmp = 0;
			if (iTOhContainer->web.at(x)->cell2->functionType == FuncTypes::RELU) {
				tmp = recLinePrime(iTOhContainer->web.at(x)->cell2->valPostActivator);
			}
			else if (iTOhContainer->web.at(x)->cell2->functionType == FuncTypes::LRELU) {
				tmp = leakyRecLinePrime(hTOoContainer->web.at(x)->cell2->valPostActivator);
			}
			else if (iTOhContainer->web.at(x)->cell2->functionType == FuncTypes::LU) {
				tmp = linearPrime(iTOhContainer->web.at(x)->cell2->valPostActivator);
			}
			else if (iTOhContainer->web.at(x)->cell2->functionType == FuncTypes::SIGM) {
				tmp = sigmoidPrime(iTOhContainer->web.at(x)->cell2->valPreActivator);
			}
			else if (iTOhContainer->web.at(x)->cell2->functionType == FuncTypes::TANH) {
				tmp = tanhPrime(iTOhContainer->web.at(x)->cell2->valPostActivator);
			}
			iTOhContainer->web.at(x)->gradiant.push_back(iTOhContainer->web.at(x)->cell2->partialDeriviative.at(iTOhContainer->web.at(x)->cell2->partialDeriviative.size() - 1) * tmp * iTOhContainer->web.at(x)->cell1->valPostActivator);
		}
	}

	void NeuralNetwork::bProp()
	{
		//mocNN();
		//float a = getError();
		float momentum = 0.3;
		float learningRate = 0.2;

		for (int itter = 0; itter < 10000; itter++) { //this is the itteration step
			cost = std::vector<float>(); //reset cost for when we loop
			std::vector<std::vector<float>>rData = randomiseData();
			for (int rd = 0; rd <= rData.size(); rd++) {
				rd = 0;
				std::vector<float>fpData = std::vector<float>();
				for (int rdn = 0; rdn < rData.at(rd).size(); rdn++) {
					fpData.push_back(rData.at(rd).at(rdn));
				}
				rData.erase(rData.begin() + rd);
				Fprop(fpData); //This stimulates the brain generating an a set of outputs, it also recordes the error by comparing output neruons score vs target
				for (int x = 0; x < outputContainer->nodeList.size(); x++) {
					//target - calculated final output
					genCost(x);
				}
				gradiantDescent();
				//we then update the synapses with the formula delta weight(t) = E * (dE/dW(t)) + a delta weight(t-1)
				for (int o = 0; o < hTOoContainer->web.size(); o++) {
					float tmp = 0;
					for (int i = 0; i < hTOoContainer->web.at(o)->gradiant.size(); i++) { //this is set up for batch training
						tmp += hTOoContainer->web.at(o)->gradiant.at(i);
					}
					hTOoContainer->web.at(o)->weight += learningRate * tmp;
				}
				for (int h = 0; h < hTOhContainer.size(); h++) {
					for (int o = 0; o < hTOhContainer.at(h)->web.size(); o++) {
						float tmp = 0;
						for (int i = 0; i < hTOhContainer.at(h)->web.at(o)->gradiant.size(); i++) {
							tmp += hTOhContainer.at(h)->web.at(o)->gradiant.at(i);
						}
						hTOhContainer.at(h)->web.at(o)->weight += learningRate * tmp;
					}
				}

				for (int o = 0; o < iTOhContainer->web.size(); o++) {
					float tmp = 0;
					for (int i = 0; i < iTOhContainer->web.at(o)->gradiant.size(); i++) {
						tmp += iTOhContainer->web.at(o)->gradiant.at(i);
					}
					iTOhContainer->web.at(o)->weight += learningRate * tmp;
				}
				clearGradiants();
				//cost = std::vector<float>(); //reset cost for when we loop
				float F = getError();
				//cost = std::vector<float>(); //reset cost for when we loop
				std::cout << "";
			}

			std::cout << "";
		}//end of itter
		float G = getError();
		std::cout << "";
	}

	void NeuralNetwork::genCost(int outputPos) //this is the individual error function
	{
		cost.push_back(target.at(outputPos) - score.at(outputPos));
	}

	float NeuralNetwork::genError()
	{
		float tmp = 0;
		float hldr = 0;
		for (int x = 0; x < cost.size(); x++) {
			tmp = cost.at(x);
			tmp = pow(tmp, 2);
			tmp = 0.5 * tmp;
			hldr += tmp;
		}
		return hldr;
	}

	float NeuralNetwork::getError()
	{
		//now we have finished the itter we need to check how we are doing
		float test = outputContainer->nodeList.at(0)->valPostActivator;
		std::vector<float>fpData;
		std::vector<float>Outs;
		cost = std::vector<float>();
		//for the size of the learning data set compile errors for each output neuron based on learning data inputs and expected outputs generating a cost value
		for (int td = 0; td <= learningSet.expectedInputData.size() - 1; td++) {
			fpData = std::vector<float>();
			for (int ts = 0; ts <= learningSet.expectedInputData.at(td).size() - 1; ts++) {
				if (inputContainer->nodeList.at(ts + 1)->type != BIAS) {
					//for were gona fprop for each possible testcase so we need to change the inputs
					inputContainer->nodeList.at(ts + 1)->valPreActivator = learningSet.expectedInputData.at(td).at(ts);
					inputContainer->nodeList.at(ts + 1)->valPostActivator = learningSet.expectedInputData.at(td).at(ts);
					fpData.push_back(learningSet.expectedInputData.at(td).at(ts));

				}
			}//this is nested because we want to get costs for each output neuron and each possible case for the data sets
			 //in an xor problem it would be 1output * 4answers = 4costs
			compareResult(); //This trys the find each target for each output neuron given the inputs given to the network


			float a = target.at(0);
			
			Fprop(fpData); //This stimulates the brain generating an a set of outputs, it also recordes the error by comparing output neruons score vs target
			Outs.push_back(outputContainer->nodeList.at(0)->valPostActivator);
			for (int x = 0; x < outputContainer->nodeList.size(); x++) {
				//target - calculated final output
				genCost(x);
				std::cout << cost.at(x) << std::endl;
			}
			//now we need to generate an error value that takes into account all the previous cost data, i though i was supposed to use the mean square error but idk where that would fit in
		} //end of learning set
		return genError();
	}

	float NeuralNetwork::sigmoidFunc(float val)
	{
		float expVal;
		float finalVal;

		expVal = exp((double)-val);
		finalVal = 1 / (1 + expVal);
		std::cout << "'F(" << val << ") = " << finalVal << std::endl;
		return finalVal;
	}

	float NeuralNetwork::linearFunc(float val)
	{
		std::cout << "'F(" << val << ") = " << val << std::endl;
		return val;
	}

	float NeuralNetwork::tanhFunc(float val)
	{
		float expVal;

		expVal = exp((2*val)-1) / exp((2 * val) + 1);
		std::cout << "'F(" << val << ") = " << expVal << std::endl;

		return expVal;
	}

	float NeuralNetwork::recLineFunc(float val)
	{
		std::cout << "'F(" << val << ") = " << val << std::endl;
		return recLineFunc(val);
	}

	float NeuralNetwork::leakyRecLineFunc(float val)
	{
		float leak = 1 * (val < 0) * (1 * val) + 1 * (val >= 0) * (val);
		std::cout << "'F(" << val << ") = " << leak << std::endl;
		return leak;
	}

	float NeuralNetwork::sigmoidPrime(float val)
	{
		float f = 1 / (1 + exp((double)-val));
		//float d1 = f * (1 - f);
		float d = 1 + exp((double)-val);
		float fd = exp((double)-val) / (pow(d, 2));
		//float df = exp
		
		//std::cout << "'F(" << val << ") = " << d1 << std::endl;

		return fd;
	}

	float NeuralNetwork::fakeSigmoidPrime(float val)
	{
		return val * (1 - val);
	}

	float NeuralNetwork::linearPrime(float val)
	{
		return 0.0f;
	}

	float NeuralNetwork::tanhPrime(float val)
	{
		return 0.0f;
	}

	float NeuralNetwork::recLinePrime(float val)
	{
		return 0.0f;
	}

	float NeuralNetwork::leakyRecLinePrime(float val)
	{
		return 0.0f;
	}

	void NeuralNetwork::pruneRandomSynapse()
	{
		//pick a random hidden layer
		int rangeMin = 0;
		int rangeMax = 2 + hTOhContainer.size() - 1;
		int layerPos = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));

		//pick a random neuron
		rangeMax = hiddenContainer.at(layerPos)->nodeList.size() - 1;
		int neuronPos = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - 1)));
		//pick a random side between left hand or right hand
		rangeMax = 1;
		int side = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - 0)));
		int synapsePos;
		if (side == 0) {//left hand side
			//pick a synapse to be erased
			rangeMax = hiddenContainer.at(layerPos)->nodeList.at(neuronPos)->axonalConnections.size();
			synapsePos = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - 1)));

			hiddenContainer.at(layerPos)->nodeList.at(neuronPos)->axonalConnections.at(synapsePos)->cell1->axonalNeurons.erase(hiddenContainer.at(layerPos)->nodeList.at(neuronPos)->axonalConnections.at(synapsePos)->cell1->axonalNeurons.begin() + neuronPos);

			//delete synapse connecting the two
			hiddenContainer.at(layerPos)->nodeList.at(neuronPos)->dendriticConnections.erase(hiddenContainer.at(layerPos)->nodeList.at(neuronPos)->dendriticConnections.begin() + synapsePos);
		}
		else if (side == 1) {//right hand side

		}


		//create a random gen chance that picks between all potential synapses and prunes one
//		int rangeMin = 0;
	//	int rangeMax = iTOhContainer->web.size();
		std::vector<int>rangeMemory;
		rangeMemory.push_back(rangeMax);
		for (int x = 0; x < hTOhContainer.size(); x++) {
			rangeMax += hTOhContainer.at(x)->web.size();
			rangeMemory.push_back(hTOhContainer.at(x)->web.size());
		}
		rangeMax += hTOoContainer->web.size();
		rangeMemory.push_back(hTOoContainer->web.size());
		
		int r = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
		int accountedFor = 0;
		for (int x = 0; x < rangeMemory.size(); x++) {
			if (r <= accountedFor + rangeMemory.at(x)) {
				accountedFor += rangeMemory.at(x);
				if (x == 0) {
					for (int i = 0; i < iTOhContainer->web.at(r)->cell1->axonalConnections.size(); i++) {
						if (iTOhContainer->web.at(r) == iTOhContainer->web.at(r)->cell1->axonalConnections.at(i)) {
							delete iTOhContainer->web.at(r)->cell1->axonalConnections.at(i);
						}
					}
					for (int i = 0; i < iTOhContainer->web.at(r)->cell1->dendriticConnections.size(); i++) {
						if (iTOhContainer->web.at(r) == iTOhContainer->web.at(r)->cell1->dendriticConnections.at(i)) {
							delete iTOhContainer->web.at(r)->cell1->dendriticConnections.at(i);
						}
						
					}
					for (int i = 0; i < iTOhContainer->web.at(r)->cell2->axonalConnections.size(); i++) {
						if (iTOhContainer->web.at(r) == iTOhContainer->web.at(r)->cell2->axonalConnections.at(i)) {
							delete iTOhContainer->web.at(r)->cell2->axonalConnections.at(i);
						}
						
					}
					for (int i = 0; i < iTOhContainer->web.at(r)->cell2->dendriticConnections.size(); i++) {
						if (iTOhContainer->web.at(r) == iTOhContainer->web.at(r)->cell2->dendriticConnections.at(i)) {
							delete iTOhContainer->web.at(r)->cell2->dendriticConnections.at(i);
						}
						
					}
					delete iTOhContainer->web.at(r);
				}
				else if (x <= hTOhContainer.size() && x > 0) {
					for (int i = 0; i < hTOhContainer.at(x)->web.at(r - accountedFor)->cell1->axonalConnections.size(); i++) {
						if (hTOhContainer.at(x)->web.at(r - accountedFor) == hTOhContainer.at(x)->web.at(r - accountedFor)->cell1->axonalConnections.at(i)) {
							delete hTOhContainer.at(x)->web.at(r - accountedFor)->cell1->axonalConnections.at(i);
						}
					}
					for (int i = 0; i < hTOhContainer.at(x)->web.at(r - accountedFor)->cell1->dendriticConnections.size(); i++) {
						if (hTOhContainer.at(x)->web.at(r - accountedFor) == hTOhContainer.at(x)->web.at(r - accountedFor)->cell1->dendriticConnections.at(i)) {
							delete hTOhContainer.at(x)->web.at(r - accountedFor)->cell1->dendriticConnections.at(i);
						}

					}
					for (int i = 0; i < hTOhContainer.at(x)->web.at(r - accountedFor)->cell2->axonalConnections.size(); i++) {
						if (hTOhContainer.at(x)->web.at(r - accountedFor) == hTOhContainer.at(x)->web.at(r - accountedFor)->cell2->axonalConnections.at(i)) {
							delete hTOhContainer.at(x)->web.at(r - accountedFor)->cell2->axonalConnections.at(i);
						}

					}
					for (int i = 0; i < hTOhContainer.at(x)->web.at(r - accountedFor)->cell2->dendriticConnections.size(); i++) {
						if (hTOhContainer.at(x)->web.at(r - accountedFor) == hTOhContainer.at(x)->web.at(r - accountedFor)->cell2->dendriticConnections.at(i)) {
							delete hTOhContainer.at(x)->web.at(r - accountedFor)->cell2->dendriticConnections.at(i);
						}

					}
					delete hTOhContainer.at(x)->web.at(r - accountedFor);
				}
				else if (x > hTOhContainer.size()) {
					for (int i = 0; i < hTOoContainer->web.at(r - accountedFor)->cell1->axonalConnections.size(); i++) {
						if (hTOoContainer->web.at(r - accountedFor) == hTOoContainer->web.at(r - accountedFor)->cell1->axonalConnections.at(i)) {
							delete hTOoContainer->web.at(r - accountedFor)->cell1->axonalConnections.at(i);
						}
					}
					for (int i = 0; i < hTOoContainer->web.at(r - accountedFor)->cell1->dendriticConnections.size(); i++) {
						if (hTOoContainer->web.at(r - accountedFor) == hTOoContainer->web.at(r - accountedFor)->cell1->dendriticConnections.at(i)) {
							delete hTOoContainer->web.at(r - accountedFor)->cell1->dendriticConnections.at(i);
						}

					}
					for (int i = 0; i < hTOoContainer->web.at(r - accountedFor)->cell2->axonalConnections.size(); i++) {
						if (hTOoContainer->web.at(r - accountedFor) == hTOoContainer->web.at(r - accountedFor)->cell2->axonalConnections.at(i)) {
							delete hTOoContainer->web.at(r - accountedFor)->cell2->axonalConnections.at(i);
						}

					}
					for (int i = 0; i < hTOoContainer->web.at(r - accountedFor)->cell2->dendriticConnections.size(); i++) {
						if (hTOoContainer->web.at(r - accountedFor) == hTOoContainer->web.at(r - accountedFor)->cell2->dendriticConnections.at(i)) {
							delete hTOoContainer->web.at(r - accountedFor)->cell2->dendriticConnections.at(i);
						}

					}
					delete hTOoContainer->web.at(r - accountedFor);
				}
			}
		}
	}

	void NeuralNetwork::pruneRandomNeuron()
	{
		int rangeMin = 0;
		int rangeMax = this->hiddenLayerTotal;
		//randomly select a neuron layer that is not the input layer or output layer
		int r = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
		rangeMax = hiddenContainer.at(r)->nodeList.size() -1;
		//now randomly select a non bias neruon in the layer to be removed
		int rr;
		if (rangeMax - 1 == 0) {
			rr = 1;
		}
		else {
			rr = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - 1))); //bias is always node 0

		}
		//before we erase any neuron info we need to destroy its synapses to the left and right
		for (int i = hiddenContainer.at(r)->nodeList.at(rr)->axonalConnections.size()-1; i < 0; i--) {
			hiddenContainer.at(r)->nodeList.at(rr)->axonalConnections.erase(hiddenContainer.at(r)->nodeList.at(rr)->axonalConnections.begin() + i);
		}
		for (int i = hiddenContainer.at(r)->nodeList.at(rr)->dendriticConnections.size()-1; i < 0; i--) {
			hiddenContainer.at(r)->nodeList.at(rr)->dendriticConnections.erase(hiddenContainer.at(r)->nodeList.at(rr)->dendriticConnections.begin() + i);
		}
		hiddenContainer.at(r)->nodeList.erase(hiddenContainer.at(r)->nodeList.begin()+rr);
		hiddenContainer.at(r)->CleanTheLayer();
		iTOhContainer->packGroup1();
		iTOhContainer->packGroup2();
		iTOhContainer->packGroupTotal();
		iTOhContainer->packWeb();
		for (int x = 0; x < hTOhContainer.size(); x++) {
			hTOhContainer.at(x)->packGroup1();
			hTOhContainer.at(x)->packGroup2();
			hTOhContainer.at(x)->packGroupTotal();
			hTOhContainer.at(x)->packWeb();
		}
		hTOoContainer->packGroup1();
		hTOoContainer->packGroup2();
		hTOoContainer->packGroupTotal();
		//create method to clear the data for a neurons dendrites and axons
		hTOoContainer->packWeb();
		
		this->hiddenContainer;
		std::cout << "";
	}

	void NeuralNetwork::addRandomSynapse()
	{
		//randomly select the starting hTOh layer to generate the synapse on
		int rangeMin = 0;
		int rangeMax = hiddenContainer.size() - 1; //first we need to find a neuron to add a synapse to so we need to select a possible layer the neuron lives on
		int r = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));

		rangeMax = hiddenContainer.at(r)->nodeList.size() - 1; //now we need to find the starting neuron to add a synapse to
		int n = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));

		while (hiddenContainer.at(r)->nodeList.at(n)->type == BIAS) { //we do not want to fuck with bias neurons so we need to prevent that option for arrising by re-rolling n when a bias neuron is selected
			n = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
		}

		//now that we have our starting neuron we need to decide if we are going to add a synapse forwards or backwards
		rangeMax = 1;
		int b = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));

		bool checkedLeft = false;
		bool checkedRight = false;

		bool gate = true;
		while (gate == true) {
			//if b == 0 then try to add a synapse on the left hand side else try add the synapse on the right hand side
			if (b == 0) { //with this case we are going to try to add a synapse on the left hand side
						  //we need to check if there are any possible connections for this neuron to make
				std::vector<Vec2>possibleConnectionList = std::vector<Vec2>(); //just because these connections are possible does not mean they are useful
				std::vector<Vec2>impossibleConnectionList = std::vector<Vec2>();
				std::vector<Vec2>usefulConnectionList = std::vector<Vec2>();

				if (r == 0) { //if the hidden container is the first slot then we need to check the possible input neurons
					for (int x = 0; x < inputContainer->nodeList.size(); x++) {
						int tmpSX = inputContainer->nodeList.at(x)->spriteXspot;
						int tmpSY = inputContainer->nodeList.at(x)->spriteYspot;
						possibleConnectionList.push_back(Vec2(tmpSX, tmpSY));
					}
				}
				else { //if the hidden container is not the first slot then we dont need to worry about input neurons and because this is the left hand side we dont care about output neurons
					for (int x = 0; x < hiddenContainer.at(r - 1)->nodeList.size(); x++) {
						int tmpSX = hiddenContainer.at(r - 1)->nodeList.at(x)->spriteXspot;
						int tmpSY = hiddenContainer.at(r - 1)->nodeList.at(x)->spriteYspot;
						possibleConnectionList.push_back(Vec2(tmpSX, tmpSY));
					}
				}

				//for each dendritic connection on the selected neuron we need to extract that neurons position info and add it to the impossible connection list
				for (int x = 0; x < hiddenContainer.at(r)->nodeList.at(n)->dendriticNeurons.size(); x++) {
					int tmpSX = hiddenContainer.at(r)->nodeList.at(n)->dendriticNeurons.at(x)->spriteXspot;
					int tmpSY = hiddenContainer.at(r)->nodeList.at(n)->dendriticNeurons.at(x)->spriteYspot;
					impossibleConnectionList.push_back(Vec2(tmpSX, tmpSY));
				}

				//Now we need to check the impossibleConnectionList and when identical values are not found in the possible connection list we need to add that to the usefulConnectionList
				bool checker = false;
				for (int x = 0; x < possibleConnectionList.size(); x++) {
					for (int y = 0; y < impossibleConnectionList.size(); y++) {
						if (possibleConnectionList.at(x).x == impossibleConnectionList.at(y).x && possibleConnectionList.at(x).y == impossibleConnectionList.at(y).y) {
							checker = true;
						}
					}

					if (checker != true && hiddenContainer.at(r)->nodeList.at(n)->type != BIAS) {
						usefulConnectionList.push_back(possibleConnectionList.at(x));
					}
					checker = false;
				}

				//now that we have a populated usefulConnectionList connection list we need to pick one
				if (usefulConnectionList.size() > 0) {
					rangeMax = usefulConnectionList.size() - 1;
					int g = 0;
					
					if (rangeMax != 0) {
					g = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
					}
					
					if (r == 0) { //when dealing with input neurons
						hiddenContainer.at(r)->nodeList.at(n)->dendriticNeurons.push_back(inputContainer->nodeList.at(usefulConnectionList.at(g).y));
						float s = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
						Synapse* syn = new Synapse(iTOhContainer, s, hiddenContainer.at(r)->nodeList.at(n), inputContainer->nodeList.at(usefulConnectionList.at(g).y));
						hiddenContainer.at(r)->nodeList.at(n)->dendriticConnections.push_back(syn);
						inputContainer->nodeList.at(usefulConnectionList.at(g).y)->axonalConnections.push_back(syn);
						inputContainer->nodeList.at(usefulConnectionList.at(g).y)->axonalNeurons.push_back(hiddenContainer.at(r)->nodeList.at(n));
						iTOhContainer->web.push_back(syn);
						gate = false;
					}
					else { //when dealing with hidden neurons
						hiddenContainer.at(r)->nodeList.at(n)->dendriticNeurons.push_back(hiddenContainer.at(r - 1)->nodeList.at(usefulConnectionList.at(g).y));
						float s = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
						Synapse* syn = new Synapse(hTOhContainer.at(r - 1), s, hiddenContainer.at(r)->nodeList.at(n), hiddenContainer.at(r - 1)->nodeList.at(usefulConnectionList.at(g).y));
						hiddenContainer.at(r)->nodeList.at(n)->dendriticConnections.push_back(syn);
						hiddenContainer.at(r - 1)->nodeList.at(usefulConnectionList.at(g).y)->axonalConnections.push_back(syn);
						hiddenContainer.at(r - 1)->nodeList.at(usefulConnectionList.at(g).y)->axonalNeurons.push_back(hiddenContainer.at(r)->nodeList.at(n));
						hTOhContainer.at(r - 1)->web.push_back(syn);
						gate = false;
					}
				}
				else {//if usefulConnectionList is not populated that means there are no possible connections to add with respect to the starting neuron
					if (hiddenContainer.size() - 1 > r) {
						if (hiddenContainer.at(r)->nodeList.size() - 1 > n) {
							n++; //check the next neuron in the list
							//break;
						}
						else {
							n = 0;
							r++; //check the next hidden container in the list
						}
					}
					else {
						checkedLeft = true;
						//r = 0;
						if (checkedRight == true) {
							addRandomNeuron();
							break;
						}
						b = 1; //engage the right hand rule
					}
				}

			} //end of left hand rule

			//if b == 1 then try to add a synapse on the right hand side else try add the synapse on the left hand side
			else if (b == 1) { //with this case we are going to try to add a synapse on the right hand side
						  //we need to check if there are any possible connections for this neuron to make
				std::vector<Vec2>possibleConnectionList = std::vector<Vec2>(); //just because these connections are possible does not mean they are useful
				std::vector<Vec2>impossibleConnectionList = std::vector<Vec2>();
				std::vector<Vec2>usefulConnectionList = std::vector<Vec2>();

				if (r == hiddenContainer.size() - 1) { //if the hidden container is the last slot then we need to check the possible output neurons
					for (int x = 0; x < outputContainer->nodeList.size(); x++) {
						int tmpSX = outputContainer->nodeList.at(x)->spriteXspot;
						int tmpSY = outputContainer->nodeList.at(x)->spriteYspot;
						possibleConnectionList.push_back(Vec2(tmpSX, tmpSY));
					}
				}
				else { //if the hidden container is not the last slot then we dont need to worry about output neurons.
					for (int x = 0; x < hiddenContainer.at(r + 1)->nodeList.size(); x++) {
						int tmpSX = hiddenContainer.at(r + 1)->nodeList.at(x)->spriteXspot;
						int tmpSY = hiddenContainer.at(r + 1)->nodeList.at(x)->spriteYspot;
						possibleConnectionList.push_back(Vec2(tmpSX, tmpSY));
					}
				}

				//for each dendritic connection on the selected neuron we need to extract that neurons position info and add it to the impossible connection list
				for (int x = 0; x < hiddenContainer.at(r)->nodeList.at(n)->axonalNeurons.size(); x++) {
					int tmpSX = hiddenContainer.at(r)->nodeList.at(n)->axonalNeurons.at(x)->spriteXspot;
					int tmpSY = hiddenContainer.at(r)->nodeList.at(n)->axonalNeurons.at(x)->spriteYspot;
					impossibleConnectionList.push_back(Vec2(tmpSX, tmpSY));
				}

				//Now we need to check the impossibleConnectionList and when identical values are not found in the possible connection list we need to add that to the usefulConnectionList
				bool checker = false;
				for (int x = 0; x < possibleConnectionList.size(); x++) {
					for (int y = 0; y < impossibleConnectionList.size(); y++) {
						if (possibleConnectionList.at(x).x == impossibleConnectionList.at(y).x && possibleConnectionList.at(x).y == impossibleConnectionList.at(y).y) {
							checker = true;
						}
					}
					if (checker != true && hiddenContainer.at(r)->nodeList.at(n)->type != BIAS) {
						usefulConnectionList.push_back(possibleConnectionList.at(x));
					}
					checker = false;
				}

				//now that we have a populated usefulConnectionList connection list we need to pick one
				if (usefulConnectionList.size() > 0) {
					rangeMax = usefulConnectionList.size() - 1;
					int g = 0;
				
					if (rangeMax != 0) {
						g = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
					}
					
					if (r == hiddenContainer.size() - 1) { //when dealing with output neurons
						hiddenContainer.at(r)->nodeList.at(n)->axonalNeurons.push_back(outputContainer->nodeList.at(usefulConnectionList.at(g).y));
						float s = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
						Synapse* syn = new Synapse(hTOoContainer, s, hiddenContainer.at(r)->nodeList.at(n), outputContainer->nodeList.at(usefulConnectionList.at(g).y));
						hiddenContainer.at(r)->nodeList.at(n)->axonalConnections.push_back(syn);
						outputContainer->nodeList.at(usefulConnectionList.at(g).y)->dendriticConnections.push_back(syn);
						outputContainer->nodeList.at(usefulConnectionList.at(g).y)->dendriticNeurons.push_back(hiddenContainer.at(r)->nodeList.at(n));
						iTOhContainer->web.push_back(syn);
						gate = false;
					}
					else { //when dealing with hidden neurons
						hiddenContainer.at(r)->nodeList.at(n)->axonalNeurons.push_back(hiddenContainer.at(r + 1)->nodeList.at(usefulConnectionList.at(g).y));
						float s = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
						Synapse* syn = new Synapse(hTOhContainer.at(r + 1), s, hiddenContainer.at(r)->nodeList.at(n), hiddenContainer.at(r + 1)->nodeList.at(usefulConnectionList.at(g).y));
						hiddenContainer.at(r)->nodeList.at(n)->axonalConnections.push_back(syn);
						hiddenContainer.at(r + 1)->nodeList.at(usefulConnectionList.at(g).y)->dendriticConnections.push_back(syn);
						hiddenContainer.at(r + 1)->nodeList.at(usefulConnectionList.at(g).y)->dendriticNeurons.push_back(hiddenContainer.at(r)->nodeList.at(n));
						hTOhContainer.at(r + 1)->web.push_back(syn);
						gate = false;
					}
				}
				else {//if usefulConnectionList is not populated that means there are no possible connections to add with respect to the starting neuron
					if (hiddenContainer.size() - 1 > r) {
						if (hiddenContainer.at(r)->nodeList.size() - 1 > n) {
							n++; //check the next neuron in the list
								 //break;
						}
						else {
							n = 0;
							r++; //check the next hidden container in the list
						}
					}
					else {
						checkedRight = true;
						//r = 0;
						if (checkedLeft == true) {
							addRandomNeuron();
							break;
						}
						b = 0; //engage the left hand rule
					}
				}
				//after the right hand rule its important that if it fails we generate a new neuron
			} //end of right hand rule
		}// end of gate check
	}//end of method

	void NeuralNetwork::addRandomNeuron() //add functionality so it randomly generates a function to represent problems with
	{
		//generate a random layer position to add to the network
		int rangeMin = 0;
		//int rangeMax = hiddenContainer.size() -1;
		int rangeMax = hiddenContainer.size();
		int r = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
		
		//r = rangeMax;
		if (r != rangeMax) {
			int f = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4 - 0))); //max = FuncTypes size -1
			FuncTypes ft = returnFType(f);
			hiddenContainer.at(r)->GenerateNeuron(hiddenContainer.at(r)->nodeList.size()-1,ft);
			hiddenContainer.at(r)->newNumberOfNodes(hiddenContainer.at(r)->numberOfNodes + 1);
		}

		if (r == 0) {
			//random generate a random neuron position to wire to thats not a bias neuron
			rangeMax = inputContainer->nodeList.size();
			int p = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			while (inputContainer->nodeList.at(p)->type == NodeTypes::BIAS) {
				p = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			}
			//random generate a random neuron position to wire to thats not a bias neuron
			rangeMax = hiddenContainer.at(r + 1)->nodeList.size();
			int q = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			while (hiddenContainer.at(r + 1)->nodeList.at(q)->type == NodeTypes::BIAS) {
				q = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			}

			//set up input wireing
			float t = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
			iTOhContainer->web.push_back(new Synapse(iTOhContainer, t, inputContainer->nodeList.at(p), hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)));
			inputContainer->nodeList.at(p)->axonalConnections.push_back(iTOhContainer->web.at(iTOhContainer->web.size() - 1));
			inputContainer->nodeList.at(p)->axonalNeurons.push_back(hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticConnections.push_back(iTOhContainer->web.at(iTOhContainer->web.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticNeurons.push_back(inputContainer->nodeList.at(p));

			t = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
			//set up hidden wireing
			hTOhContainer.at(r)->web.push_back(new Synapse(hTOhContainer.at(r), t, hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1), hiddenContainer.at(r + 1)->nodeList.at(q)));
			hiddenContainer.at(r + 1)->nodeList.at(q)->dendriticConnections.push_back(hTOhContainer.at(r)->web.at(hTOhContainer.at(r)->web.size() - 1));
			hiddenContainer.at(r + 1)->nodeList.at(q)->dendriticNeurons.push_back(hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->axonalConnections.push_back(hTOhContainer.at(r)->web.at(hTOhContainer.at(r)->web.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->axonalNeurons.push_back(hiddenContainer.at(r + 1)->nodeList.at(q));

			for (int x = 0; x < inputContainer->nodeList.size(); x++) {
				if (inputContainer->nodeList.at(x)->type == NodeTypes::BIAS) {
					//set up bias wireing
					iTOhContainer->web.push_back(new Synapse(iTOhContainer, t, inputContainer->nodeList.at(x), hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)));
					inputContainer->nodeList.at(x)->axonalConnections.push_back(iTOhContainer->web.at(iTOhContainer->web.size() - 1));
					inputContainer->nodeList.at(x)->axonalNeurons.push_back(hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1));
					hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticConnections.push_back(iTOhContainer->web.at(iTOhContainer->web.size() - 1));
					hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticNeurons.push_back(inputContainer->nodeList.at(x));
					break;

				}
			}
		}
		else if (r < hiddenContainer.size() -1 && r > 0) {
			//random generate a random neuron position to wire to thats not a bias neuron
			rangeMax = hiddenContainer.at(r)->nodeList.size();
			int p = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			while (hiddenContainer.at(r)->nodeList.at(p)->type == NodeTypes::BIAS) {
				p = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			}
			//random generate a random neuron position to wire to thats not a bias neuron
			rangeMax = hiddenContainer.at(r + 1)->nodeList.size();
			int q = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			while (hiddenContainer.at(r + 1)->nodeList.at(q)->type == NodeTypes::BIAS) {
				q = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			}

			//set up left hand wireing
			float t = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
			hTOhContainer.at(r)->web.push_back(new Synapse(hTOhContainer.at(r), t, hiddenContainer.at(r)->nodeList.at(p), hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)));
			hiddenContainer.at(r - 1)->nodeList.at(p)->axonalConnections.push_back(hTOhContainer.at(r)->web.at(hTOhContainer.at(r)->web.size() - 1));
			hiddenContainer.at(r - 1)->nodeList.at(p)->axonalNeurons.push_back(hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticConnections.push_back(hTOhContainer.at(r)->web.at(hTOhContainer.at(r)->web.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticNeurons.push_back(hiddenContainer.at(r - 1)->nodeList.at(p));

			t = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
			//set up right hand wireing
			hTOhContainer.at(r)->web.push_back(new Synapse(hTOhContainer.at(r), t, hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1), hiddenContainer.at(r + 1)->nodeList.at(q)));
			hiddenContainer.at(r + 1)->nodeList.at(q)->dendriticConnections.push_back(hTOhContainer.at(r)->web.at(hTOhContainer.at(r)->web.size() - 1));
			hiddenContainer.at(r + 1)->nodeList.at(q)->dendriticNeurons.push_back(hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->axonalConnections.push_back(hTOhContainer.at(r)->web.at(hTOhContainer.at(r)->web.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->axonalNeurons.push_back(hiddenContainer.at(r + 1)->nodeList.at(q));

			for (int x = 0; x < hiddenContainer.at(r - 1)->nodeList.size(); x++) {
				if (hiddenContainer.at(r - 1)->nodeList.at(x)->type == NodeTypes::BIAS) {
					//set up bias wireing
					hTOhContainer.at(r)->web.push_back(new Synapse(hTOhContainer.at(r), t, hiddenContainer.at(r - 1)->nodeList.at(x), hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)));
					hiddenContainer.at(r - 1)->nodeList.at(x)->axonalConnections.push_back(hTOhContainer.at(r)->web.at(hTOhContainer.at(r)->web.size() - 1));
					hiddenContainer.at(r - 1)->nodeList.at(x)->axonalNeurons.push_back(hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1));
					hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticConnections.push_back(hTOhContainer.at(r)->web.at(hTOhContainer.at(r)->web.size() - 1));
					hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticNeurons.push_back(hiddenContainer.at(r - 1)->nodeList.at(x));
					break;

				}
			}
		}
		else if (r == hiddenContainer.size() -1) {
			//random generate a random neuron position to wire to thats not a bias neuron
			rangeMax = hiddenContainer.at(r - 1)->nodeList.size();
			int p = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			while (hiddenContainer.at(r - 1)->nodeList.at(p)->type == NodeTypes::BIAS) {
				p = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			}
			//random generate a random neuron position to wire to thats not a bias neuron
			rangeMax = outputContainer->nodeList.size();
			int q = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			while (outputContainer->nodeList.at(q)->type == NodeTypes::BIAS) {
				q = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			}

			//set up left hand wireing
			float t = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
			hTOhContainer.at(r-1)->web.push_back(new Synapse(hTOhContainer.at(r-1), t, hiddenContainer.at(r)->nodeList.at(p), hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)));
			hiddenContainer.at(r - 1)->nodeList.at(p)->axonalConnections.push_back(hTOhContainer.at(r-1)->web.at(hTOhContainer.at(r-1)->web.size() - 1));
			hiddenContainer.at(r - 1)->nodeList.at(p)->axonalNeurons.push_back(hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticConnections.push_back(hTOhContainer.at(r-1)->web.at(hTOhContainer.at(r-1)->web.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticNeurons.push_back(hiddenContainer.at(r - 1)->nodeList.at(p));

			t = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
			//set up right hand wireing
			hTOhContainer.at(r - 1)->web.push_back(new Synapse(hTOhContainer.at(r - 1), t, hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r) -> nodeList.size() - 1), outputContainer->nodeList.at(q)));
			outputContainer->nodeList.at(q)->dendriticConnections.push_back(hTOhContainer.at(r - 1)->web.at(hTOhContainer.at(r - 1)->web.size() - 1));
			outputContainer->nodeList.at(q)->dendriticNeurons.push_back(hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->axonalConnections.push_back(hTOhContainer.at(r-1)->web.at(hTOhContainer.at(r-1)->web.size() - 1));
			hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->axonalNeurons.push_back(outputContainer->nodeList.at(q));

			for (int x = 0; x < hiddenContainer.at(r - 1)->nodeList.size(); x++) {
				if (hiddenContainer.at(r - 1)->nodeList.at(x)->type == NodeTypes::BIAS) {
					//set up bias wireing
					hTOhContainer.at(r - 1)->web.push_back(new Synapse(hTOhContainer.at(r - 1), t, hiddenContainer.at(r)->nodeList.at(x), hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)));
					hiddenContainer.at(r - 1)->nodeList.at(x)->axonalConnections.push_back(hTOhContainer.at(r - 1)->web.at(hTOhContainer.at(r - 1)->web.size() - 1));
					hiddenContainer.at(r - 1)->nodeList.at(x)->axonalNeurons.push_back(hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1));
					hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticConnections.push_back(hTOhContainer.at(r - 1)->web.at(hTOhContainer.at(r - 1)->web.size() - 1));
					hiddenContainer.at(r)->nodeList.at(hiddenContainer.at(r)->nodeList.size() - 1)->dendriticNeurons.push_back(hiddenContainer.at(r - 1)->nodeList.at(x));
					break;
				}
			}
		}
		else if (r == hiddenContainer.size()) { //this is going to be diffrent than the others fundamentally because this is going to deal with creating a new layer, that means ill need to reweb all synapses of the previous layer
			//erase connections between the last hidden layer before the new one is injected
			for (int x = 0; x < hiddenContainer.at(hiddenContainer.size() - 1)->nodeList.size(); x++) {
				hiddenContainer.at(hiddenContainer.size() - 1)->nodeList.at(x)->axonalConnections.erase(hiddenContainer.at(hiddenContainer.size() - 1)->nodeList.at(x)->axonalConnections.begin(), hiddenContainer.at(hiddenContainer.size() - 1)->nodeList.at(x)->axonalConnections.end());
				hiddenContainer.at(hiddenContainer.size() - 1)->nodeList.at(x)->axonalNeurons.erase(hiddenContainer.at(hiddenContainer.size() - 1)->nodeList.at(x)->axonalNeurons.begin(), hiddenContainer.at(hiddenContainer.size() - 1)->nodeList.at(x)->axonalNeurons.end());
			}
			//erase neurons between the output layer before the new one is injected
			for (int x = 0; x < outputContainer->nodeList.size(); x++) {
				outputContainer->nodeList.at(x)->dendriticConnections.erase(outputContainer->nodeList.at(x)->dendriticConnections.begin(), outputContainer->nodeList.at(x)->dendriticConnections.end());
				outputContainer->nodeList.at(x)->dendriticNeurons.erase(outputContainer->nodeList.at(x)->dendriticNeurons.begin(), outputContainer->nodeList.at(x)->dendriticNeurons.end());
			}
			//erase neurons in the neuron group1 for the hidden to output layer
			for (int x = 0; x < hTOoContainer->neuronGroup1.size(); x++) {
				hTOoContainer->neuronGroup1.erase(hTOoContainer->neuronGroup1.begin(), hTOoContainer->neuronGroup1.end());
			}
			//erase the synaptic connections in the hidden to output layer
			for (int x = 0; x < hTOoContainer->web.size(); x++) {
				hTOoContainer->web.erase(hTOoContainer->web.begin(), hTOoContainer->web.end());
			}
		//	//neurongroup1 and web
			//hiddenContainer.at(hiddenContainer.size())->nodeList.size();
			int f = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4 - 0))); //max = FuncTypes size -1
			FuncTypes ft = returnFType(f);
			hiddenContainer.push_back(new NodeLayer(this, HIDDEN, 0,std::vector<std::vector<FuncTypes>>(), outputContainer->spritePos));
			outputContainer->spritePos++;
			int k = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4 - 0))); //max = FuncTypes size -1
			FuncTypes kt = returnFType(k);
			hiddenContainer.at(r)->GenerateNeuron(hiddenContainer.at(r)->nodeList.size(),kt);
			hiddenContainer.at(r)->newNumberOfNodes(hiddenContainer.at(r)->numberOfNodes + 1);
			//for (int y = 0; y < hiddenContainer.at(r)->nodeList.size(); y++) {
			//i may need to generate postValues but i may not
			//	hiddenContainer.at(r)->nodeList.at(y)->
			//}

		//	//i need to create a new hidden to hidden synapse layer and load it
			hTOhContainer.push_back(new SynapseLayer(this, NetTypes::HIDDENtoHIDDEN, hiddenContainer.at(hiddenContainer.size()-1),hiddenContainer.at(hiddenContainer.size()),1,0, true)); //this line for some reason causes a new synapse created between the secondlast hTOh synapse layer between its own neuron and synapse
			//note i may need to make the hiddenContainer.at(hiddenContainer.size()-2 and the normal hiddenContainer.at(hiddenContainer.size()-1

			//now i need to link all the synapses from the second last hidden contianer to the newly made last hidden container
			for (int x = 0; x < hiddenContainer.at(hiddenContainer.size() - 2)->nodeList.size(); x++) {
				//hiddenContainer.at(hiddenContainer.size() - 2)->nodeList.at(x)->axonalConnections.push_back()
			}
			//now i need to link all the synapses from the newly made hidden container to the output container
			hTOoContainer->layerGroup1 = hTOhContainer.at(hTOhContainer.size() - 1)->layerGroup1;
			//hTOoContainer->neuronGroup1 = hTOhContainer.at(hTOhContainer.size() - 1)->neuronGroup2;
			hTOoContainer->neuronGroup1 = hiddenContainer.at(hiddenContainer.size() -1)->nodeList;
			hTOoContainer->packWeb();

			//setting up the output neurons dendritic connections
			for (int x = 0; x < outputContainer->nodeList.size(); x++) {
				outputContainer->nodeList.at(x)->spriteXspot++;
				for (int y = 0; y < hiddenContainer.at(hiddenContainer.size() - 1)->nodeList.size(); y++) {
					outputContainer->nodeList.at(x)->dendriticNeurons.push_back(hiddenContainer.at(hiddenContainer.size() - 1)->nodeList.at(y));
				}
				for (int y = 0; y < hTOoContainer->web.size(); y++) {
					outputContainer->nodeList.at(x)->dendriticConnections.push_back(hTOoContainer->web.at(y));
				}
			}
		}
	}

	void NeuralNetwork::switchRandomNeuronFunc(int enumVal)
	{
		int rangeMax = this->hiddenContainer.size() -1;
		int rangeMin = 0;
		int p = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
		rangeMax = this->hiddenContainer.at(p)->nodeList.size() - 1;
		int q = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
		//rangeMax = 4; //total number of supported functions
		//int z = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
		hiddenContainer.at(p)->nodeList.at(q)->setFucType(returnFType(enumVal));

	}

	void NeuralNetwork::sortG1()
	{
		hiddenLayersSortedG1++;
	}
	
	void NeuralNetwork::sortG2()
	{
		hiddenLayersSortedG2++;
	}
	
	int NeuralNetwork::getG1()
	{
		return hiddenLayersSortedG1;
	}
	
	int NeuralNetwork::getG2()
	{
		return hiddenLayersSortedG2;
	}

	//void NeuralNetwork::setupSprites()
	//{
	//	//we are adding the neuron sprites to a holder than injecting that holder into a new holder-holder
	//	//add the inputs from the neural network to a sprite list at pos 0
	//	std::vector<Sprite*>tmpSpriteList = std::vector<Sprite*>();
	//	for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->inputContainer->numberOfNodes + 1; x++) {
	//		tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
	//	}
	//	nnNeuronSprites.push_back(tmpSpriteList);

	//	//add the hiddenNeurons from the neural network to a sprite list at pos 1 to hiddenLayer Size
	//	for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.size(); x++) {
	//		tmpSpriteList = std::vector<Sprite*>();
	//		for (int y = 0; y < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(x)->numberOfNodes + 1; y++) {
	//			tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
	//		}
	//		nnNeuronSprites.push_back(tmpSpriteList);
	//	}

	//	//add the Outputs from the neural network to a sprite list at hiddenLayer.size() to ++1;
	//	tmpSpriteList = std::vector<Sprite*>();
	//	for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->outputContainer->numberOfNodes; x++) {
	//		tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
	//	}
	//	nnNeuronSprites.push_back(tmpSpriteList);

	//	//set up the neurons to have an offset based on relative positions, the ones in the same group are stack ontop of eachother, the diffrent groups are placed beside eachother
	//	float tmpXoffset = 0;
	//	for (int x = 0; x < nnNeuronSprites.size(); x++) {
	//		float tmpYoffset = 0;
	//		for (int y = 0; y < nnNeuronSprites.at(x).size(); y++) {
	//			nnNeuronSprites.at(x).at(y)->translate(glm::vec3(tmpXoffset, tmpYoffset, 0));
	//			tmpYoffset += 0.4;
	//		}
	//		tmpXoffset += 0.4;
	//	}
	//}

	//void NeuralNetwork::setupShaderInfo(Shader * shInfo, GLfloat verts[], GLfloat colors[])
	//{
	//	shaderInfo = shInfo;
	//	for (int x = 0; x < verts; x++) {

	//	}
	//	vertInfo = verts;
	//	colorData = colors;
	//}
	
	void NeuralNetwork::compareResult()
	{
		//get the input the NN received
		std::vector<float> givenInput;
		for (int x = 0; x < inputContainer->nodeList.size(); x++) {
			if (inputContainer->nodeList.at(x)->type != BIAS) {
				givenInput.push_back(this->inputContainer->nodeList.at(x)->valPreActivator);
			}
		}

		//now we need to find where in the list the above pattern occures
		int holder;
		for (int x = 0; x < learningSet.expectedInputData.size(); x++) {
			if (givenInput == learningSet.expectedInputData.at(x)) {
				//here the holder variable gives us access to to the position where the givenInput matches one of the values in expectedInputData this inturn can be used to find what output should corrispond
				holder = x;
			}
		}

		//set the target to be empty
		target = std::vector<float>();
		//now we loop for all the output neurons
		for (int x = 0; x < outputContainer->nodeList.size(); x++) {
			//now we pushback new targets gained from taking the HOLDER positional value from the inputs and useing that on the Outputdataset to find the data for what each output should be defined in the dictionary 
			target.push_back(learningSet.expectedOutputData.at(holder).at(x));
		}
	}
	
	void NeuralNetwork::genMSEinput()
	{
		//because we are generating outputs for each set of training data then mean square erring it into one ERROR value to back propogate, at a point it wants an input value to back propogate wtih and because the outputs were compiled into a MSE i think the inputs that created them should also be MSE'd
		int MSEinput;
		for (int i = 0; i < this->learningSet.expectedInputData.size(); i++) {
			for (int x = 0; x < learningSet.expectedInputData.at(i).size(); x++) {

			}
		}
	}

	void NeuralNetwork::clearGradiants()
	{
		for (int o = 0; o < outputContainer->nodeList.size(); o++) {
			outputContainer->nodeList.at(o)->partialDeriviative = std::vector<float>();
		}
		for (int h = 0; h < hiddenContainer.size(); h++) {
			for (int o = 0; o < hiddenContainer.at(h)->nodeList.size(); o++) {
				hiddenContainer.at(h)->nodeList.at(o)->partialDeriviative = std::vector<float>();
			}
		}
		for (int o = 0; o < inputContainer->nodeList.size(); o++) {
			inputContainer->nodeList.at(o)->partialDeriviative = std::vector<float>();
		}

		for (int o = 0; o < hTOoContainer->web.size(); o++) {

			hTOoContainer->web.at(o)->gradiant = std::vector<float>();
		}
		for (int h = 0; h < hTOhContainer.size(); h++) {
			for (int o = 0; o < hTOhContainer.at(h)->web.size(); o++) {
				hTOhContainer.at(h)->web.at(o)->gradiant = std::vector<float>();
			}
		}
		for (int o = 0; o < iTOhContainer->web.size(); o++) {
			iTOhContainer->web.at(o)->gradiant = std::vector<float>();
		}
	}
	
	FuncTypes NeuralNetwork::returnFType(int enumVal)
	{
		return FuncTypes(enumVal);
	}
	
	void NeuralNetwork::setUpBiasVals()
	{
		inputContainer->nodeList.at(0)->setPostActivatorVal(1);

		for (int x = 0; x < this->hiddenContainer.size(); x++) {
			hiddenContainer.at(x)->nodeList.at(0)->setPostActivatorVal(1);
		}
	}
}