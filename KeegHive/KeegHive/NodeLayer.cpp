#include "stdafx.h"
#include "NodeLayer.h"

namespace GANnet {

	NodeLayer::NodeLayer(NeuralNetwork * nw, NodeTypes nodeType, int numberOfNeurons, std::vector<float> vals, std::vector<std::vector<FuncTypes>> functionStruct, int sPos)
	{
		std::cout << "NodeLayer Constructor Entered " << std::endl;
		parent = nw;
		type = nodeType;
		//functionType = fType;
		numberOfNodes = numberOfNeurons;
		autoValue = true;
		nodeList.resize(numberOfNeurons);
		spritePos = sPos;
		autoFed = true;
		randMin = 0;
		randMax = 1;
		//nFunc = fType;

		int yPosValue = 0;
		//if (type != NodeTypes::OUTPUT) {
		//	//GenerateNeuron(yPosValue, biasFuncType);
		//	//FeedInputNeuron(yPosValue, biasFuncType, 1);
		//	GenerateBiasNeuron(yPosValue);
		//	yPosValue++;
		//}


		for (int y = 0; y < functionStruct.size(); y++) {
			for (int j = 0; j < functionStruct.at(y).size(); j++) {
				//FeedInputNeuron(yPosValue, functionStruct.at(j).at(0), vals.at(y));
				FeedInputNeuron(yPosValue, functionStruct.at(j).at(0), 0);
				yPosValue++;
			}
		}

		CleanTheLayer();
		std::cout << "NodeLayer Constructor Exited " << std::endl;
	}

	NodeLayer::NodeLayer(NeuralNetwork * nw, NodeTypes nodeType, int numberOfNeurons, std::vector<std::vector<FuncTypes>> functionStruct, int sPos)
	{
		std::cout << "NodeLayer Constructor Entered " << std::endl;
		parent = nw;
		type = nodeType;
		//functionType = fType;
		numberOfNodes = numberOfNeurons;
		autoValue = true;
		nodeList.resize(numberOfNeurons);
		spritePos = sPos;
		autoFed = true;
		randMin = 0;
		randMax = 1;
		//nFunc = fType;

		int yPosValue = 0;
		if (type != NodeTypes::OUTPUT) {
		//	//GenerateNeuron(yPosValue, biasFuncType);
			GenerateBiasNeuron(yPosValue);
			yPosValue++;
		}

		for (int y = 0; y < functionStruct.size(); y++) {
			for (int j = 0; j < functionStruct.at(y).size(); j++) {
				GenerateBlankNeuron(yPosValue, functionStruct.at(y).at(j));
				yPosValue++;
			}
		}

		CleanTheLayer();
		std::cout << "NodeLayer Constructor Exited " << std::endl;
	}
	
	NodeLayer::~NodeLayer()
	{
		std::cout << "NodeLayer Destructor Entered and Exited " << std::endl;
	}

	NodeTypes NodeLayer::getLayerType(NodeLayer* nl)
	{
		std::cout << "NodeLayer is trying to fetch a NodeType to test the LayerType of an object " << std::endl;
		return nl->type;
	}

	void NodeLayer::setLayerType(NodeLayer* nl, NodeTypes ntype)
	{
		nl->type = ntype;
		std::cout << "NodeLayer has set the LayerType of an object = " << nl->type << std::endl;
	}

	bool NodeLayer::getAutoCompleteType(NodeLayer* nl)
	{
		return nl->autoValue;
		std::cout << "NodeLayer is trying to fetch if it is a AUTO or MANUAL fill object " << std::endl;
	}

	void NodeLayer::setAutoCompleteType(NodeLayer * nl, bool aComplete)
	{
		nl->autoValue = aComplete;
		std::cout << "NodeLayer has set the AUTO / MANUAL bool of itself to = " << nl->autoValue << std::endl;
	}

	void NodeLayer::alterNumOfNeuronsByVal(NodeLayer * nl, int posOrNegVal)
	{
		nl->numberOfNodes = +posOrNegVal;
		nodeList.resize(nl->numberOfNodes);
		CleanTheLayer();
	}

	void NodeLayer::alterNodeList(NodeLayer * nl, Neuron * cell, bool remove)
	{
		if (remove != true) {
			std::cout << "an Alteration is being made to a NodeLayer adding a neuron" << std::endl;
			nl->nodeList.push_back(cell);
		}
		else {
			for (int x = 0; x < nl->nodeList.size(); x++) {
				if (nl->nodeList.at(x) == cell) {
					nl->nodeList.erase(nl->nodeList.begin() + 1);
					std::cout << "an Alteration is being made to a NodeLayer deleting a neuron in position " << x << std::endl;
				}
			}
		}
	}

	void NodeLayer::CleanTheLayer()
	{
		for (int x = 0; x < nodeList.size(); x++)
		{
			if (nodeList[x] == nullptr) {
				nodeList.erase(nodeList.begin() + x);
				x--;
			}
			else {

			}
			std::cout << "Layers Clean" << std::endl;

		}
	}

	void NodeLayer::ModNeurons(valModType mType)
	{
		if (mType == valModType::PREACTIVATION)
		{
			std::cout << "Time to add in the values for each Neuron!";
			for (int x = 0; x < nodeList.size(); x++) {
				float holder = 0;
				std::cout << "We are on node #" << x << " of #" << nodeList.size() << std::endl;
				std::cin >> holder;
				nodeList.at(x)->modPreActivatorVal(holder);
			}
		}
		else if (mType == valModType::POSTACTIVATION)
		{
			for (int x = 0; x < nodeList.size(); x++) {
				float holder = 0;
				std::cout << "We are on node #" << x << " of #" << nodeList.size() << std::endl;
				std::cin >> holder;
				nodeList.at(x)->modPostActivatorVal(holder);
			}
		}
	}

	void NodeLayer::SetNeuronVal(valModType mType)
	{
		if (mType == valModType::PREACTIVATION)
		{
			std::cout << "Time to plug in the values for each Neuron!";
			for (int x = 0; x < nodeList.size(); x++) {
				float holder = 0;
				std::cout << "We are on node #" << x << " of #" << nodeList.size() << std::endl;
				std::cin >> holder;
				nodeList.at(x)->setPreActivatorVal(holder);
			}
		}
		else if (mType == valModType::POSTACTIVATION)
		{
			for (int x = 0; x < nodeList.size(); x++) {
				float holder = 0;
				std::cout << "We are on node #" << x << " of #" << nodeList.size() << std::endl;
				std::cin >> holder;
				nodeList.at(x)->setPostActivatorVal(holder);
			}
		}
	}

	void NodeLayer::GenNeuronVal(valModType mType, int rangeMin, int rangeMax)
	{
		if (mType == valModType::PREACTIVATION)
		{
			std::cout << "Time to plug in the values for each Neuron!";
			for (int x = 0; x < nodeList.size(); x++) {
				std::cout << "We are on node #" << x << " of #" << nodeList.size() << std::endl;
				//nodeList.at(x)->setPreActivatorVal(nodeList.at(x)->vRandomise(mType, rangeMin, rangeMax));
				nodeList.at(x)->vRandomise(mType, rangeMin, rangeMax);
			}
		}
		std::cout << "Debugging" << std::endl;
	}
	void NodeLayer::newNumberOfNodes(int newVal)
	{
		numberOfNodes = newVal;
	}
	float NodeLayer::randomise(int rangeMin, int rangeMax)
	{
		float r = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
		std::cout << "the NodeLayers Randomise function has been called and has generated value #" << r << "from range #" << rangeMin << " to #" << rangeMax << ", also a float is being returned" << std::endl;
		return r;
	}
	
	void NodeLayer::GenerateNeuron(int yPosVal, FuncTypes ft)
	{
		//my vars got abit screwed up for naming conventions autoValue = true  means the the content is randomly generated, if autoValue = false it means the content is manually input
		if (autoValue == true) {
			alterNodeList(this, new Neuron(this, type, ft, randomise(randMin, randMax), this->spritePos, yPosVal), false);

			if ((type != NodeTypes::OUTPUT) && (yPosVal == 0)) {
				alterNodeList(this, new Neuron(this, NodeTypes::BIAS, 1, spritePos, yPosVal), false);
			}
		}
		else if (autoValue == false && type != NodeTypes::BIAS) {
			float tempF = 0.0f;
			std::cout << "Enter value for the Neuron";
			std::cin >> tempF;
			alterNodeList(this, new Neuron(this, type, ft, tempF, this->spritePos, yPosVal), false);

			if ((type != NodeTypes::OUTPUT) && (yPosVal == 0)) {
				alterNodeList(this, new Neuron(this, NodeTypes::BIAS, ft, 1, spritePos, yPosVal), false);
			}
		}
		else if (autoValue == false && type == NodeTypes::BIAS) {
				alterNodeList(this, new Neuron(this, type, ft, 1, this->spritePos, yPosVal), false);

			if ((type != NodeTypes::OUTPUT) && (yPosVal == 0)) {
				alterNodeList(this, new Neuron(this, NodeTypes::BIAS, ft, 1, spritePos, yPosVal), false);
			}
		}
	}
	void NodeLayer::FeedInputNeuron(int yPosVal, FuncTypes ft, float vals)
	{
		//my vars got abit screwed up for naming conventions autoValue = true  means the the content is randomly generated, if autoValue = false it means the content is manually input
		if (autoValue == true) {
			

			if ((type != NodeTypes::OUTPUT) && (yPosVal == 0)) {
				alterNodeList(this, new Neuron(this, NodeTypes::BIAS, ft, 1, spritePos, yPosVal), false);
			}
			else {
				alterNodeList(this, new Neuron(this, type, ft, vals, this->spritePos, yPosVal), false);
			}
		}
		else if (autoValue == false && type == NodeTypes::BIAS) {
			alterNodeList(this, new Neuron(this, type, ft, 1, this->spritePos, yPosVal), false);

			if ((type != NodeTypes::OUTPUT) && (yPosVal == 0)) {
				alterNodeList(this, new Neuron(this, NodeTypes::BIAS, ft, 1, spritePos, yPosVal), false);
			}
		}

	}
	void GANnet::NodeLayer::GenerateBlankNeuron(int yPosVal, FuncTypes ft)
	{
		//my vars got abit screwed up for naming conventions autoValue = true  means the the content is randomly generated, if autoValue = false it means the content is manually input
		if (autoValue == true) {


			if ((type != NodeTypes::OUTPUT) && (yPosVal == 0)) {
				alterNodeList(this, new Neuron(this, NodeTypes::BIAS, 1, spritePos, yPosVal), false);
			}
			else {
				alterNodeList(this, new Neuron(this, type, ft, this->spritePos, yPosVal), false);
			}
		}
		else if (autoValue == false && type == NodeTypes::BIAS) {
			alterNodeList(this, new Neuron(this, type, ft, this->spritePos, yPosVal), false);

			if ((type != NodeTypes::OUTPUT) && (yPosVal == 0)) {
				alterNodeList(this, new Neuron(this, NodeTypes::BIAS, 1, spritePos, yPosVal), false);
			}
		}
	}
	void GANnet::NodeLayer::GenerateBiasNeuron(int yPosVal) {
		if ((type != NodeTypes::OUTPUT) && (yPosVal == 0)) {
			alterNodeList(this, new Neuron(this, NodeTypes::BIAS, 1, spritePos, yPosVal), false);
		}
	}
}