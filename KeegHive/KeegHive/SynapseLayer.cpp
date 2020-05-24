#include "stdafx.h"
#include "SynapseLayer.h"
namespace GANnet {

	SynapseLayer::SynapseLayer(NeuralNetwork* nw, NetTypes netType, NodeLayer* lhand, NodeLayer* rhand, float maxVal, float minVal, bool autoFill)
	{
		std::cout << "SynapseLayer Constructor Entered"<< std::endl;
		parent = nw;
		type = netType;

		boundsMin = 0;
		boundsMax = 1;
		autoFillVal = autoFill;

		layerGroup1 = lhand; //maybe make this -1
		layerGroup2 = rhand;


		packGroup1();
		packGroup2();
		packGroupTotal();
		packWeb();

		std::cout << "SynapseLayer Constructor Exited" << std::endl;
	}

	SynapseLayer::SynapseLayer(NeuralNetwork * nw, NetTypes netType, bool autoFill)
	{
		boundsMin = 0; 
		boundsMax = 1;
		for (int x = 0; x < parent->inputContainer->nodeList.size(); x++) {
			//not sure if i should check and stop bias neurons from getting added and deal with them in a specialised way later
			neuronGroup1.push_back(parent->inputContainer->nodeList.at(x));
		}
		for (int x = 0; x < parent->hiddenContainer.size(); x++) {
			for (int y = 0; y < parent->hiddenContainer.at(x)->nodeList.size(); y++) {
				//not sure if i should check and stop bias neurons from getting added and deal with them in a specialised way later
				neuronGroup1.push_back(parent->hiddenContainer.at(x)->nodeList.at(y));
			}
		}

		for (int x = 0; x < parent->hiddenContainer.size(); x++) {
			for (int y = 0; y < parent->hiddenContainer.at(x)->nodeList.size(); y++) {
				//not sure if i should check and stop bias neurons from getting added and deal with them in a specialised way later
				neuronGroup2.push_back(parent->hiddenContainer.at(x)->nodeList.at(y));
			}
		}
		for (int y = 0; y < parent->hiddenContainer.at(0)->nodeList.size(); y++) {
			//not sure if i should check and stop bias neurons from getting added and deal with them in a specialised way later
			neuronGroup2.push_back(parent->outputContainer->nodeList.at(y));
		}
		packWeb();
	}


	SynapseLayer::~SynapseLayer()
	{
		std::cout << "SynapseLayer destructor Entered and Exited" << std::endl;
	}
	
	void SynapseLayer::packGroup1()
	{
		neuronGroup1 = std::vector<Neuron*>();
		if (type == NetTypes::INPUTtoHIDDEN) {
			std::cout << "The packing for a SynapseLayer's group 1 has begun" << std::endl;
				for (int y = 0; y < layerGroup1->nodeList.size(); y++)
				{
					std::cout << "a SynapseLayer's neuronGroup1, is being populated with data from its corrisponding nodegroup, nodegroup x =" << 0 << ", y =" << y << std::endl;
					neuronGroup1.push_back(layerGroup1->nodeList.at(y));
				}
			std::cout << "The packing for a SynapseLayer's group 1 has ended" << std::endl;
		}
		else if (type == NetTypes::HIDDENtoHIDDEN) { //here
			std::cout << "The packing for a SynapseLayer's group 1 has begun" << std::endl;
			for (int y = 0; y < layerGroup1->nodeList.size(); y++)
			{
				std::cout << "a SynapseLayer's neuronGroup1, is being populated with data from its corrisponding nodegroup, nodegroup x =" << parent->getG1() << ", y =" << y << std::endl;
				neuronGroup1.push_back(layerGroup1->nodeList.at(y));
			}
			std::cout << "The packing for a SynapseLayer's group 1 has ended" << std::endl;
			parent->sortG1();
		}
		else if (type == NetTypes::HIDDENtoOUTPUT) {
			std::cout << "The packing for a SynapseLayer's group 1 has begun" << std::endl;
			//int pos = layerGroup1.size() -1; //added -1 to bugcheck
				for (int y = 0; y < layerGroup1->nodeList.size(); y++)
				{
					//std::cout << "a SynapseLayer's neuronGroup1, is being populated with data from its corrisponding nodegroup, nodegroup x =" << pos << ", y =" << y << std::endl;
					neuronGroup1.push_back(layerGroup1->nodeList.at(y));
				}
			std::cout << "The packing for a SynapseLayer's group 1 has ended" << std::endl;
		}
	}

	void SynapseLayer::packGroup2()	{
		neuronGroup2 = std::vector<Neuron*>();
		if (type == NetTypes::INPUTtoHIDDEN) {
			std::cout << "The packing for a SynapseLayer's group 2 has begun" << std::endl;
				for (int y = 0; y < layerGroup2->nodeList.size(); y++)
				{
					if (layerGroup2->nodeList.at(y)->type != BIAS) {
						std::cout << "a SynapseLayer's neuronGroup2, is being populated with data from its corrisponding nodegroup, nodegroup x =" << 0 << ", y =" << y << std::endl;
						neuronGroup2.push_back(layerGroup2->nodeList.at(y));
					}
				}
			std::cout << "The packing for a SynapseLayer's group 2 has ended" << std::endl;
		}
		else if (type == NetTypes::HIDDENtoHIDDEN) { //here
			std::cout << "The packing for a SynapseLayer's group 2 has begun" << std::endl;
			for (int y = 0; y < layerGroup2->nodeList.size(); y++)
			{
				if (layerGroup2->nodeList.at(y)->type != BIAS){
					std::cout << "a SynapseLayer's neuronGroup2, is being populated with data from its corrisponding nodegroup, nodegroup x =" << parent->getG2()+1 << ", y =" << y << std::endl;
					neuronGroup2.push_back(layerGroup2->nodeList.at(y));
				}
			}
			std::cout << "The packing for a SynapseLayer's group 2 has ended" << std::endl;
			parent->sortG2();
		}
		else if (type == NetTypes::HIDDENtoOUTPUT) {
			std::cout << "The packing for a SynapseLayer's group 2 has begun" << std::endl;

				for (int y = 0; y < layerGroup2->nodeList.size(); y++)
				{
					//if (layerGroup2.at(parent->getG2() + 1)->nodeList.at(y)->type != BIAS) {
						//std::cout << "a SynapseLayer's neuronGroup2, is being populated with data from its corrisponding nodegroup, nodegroup x =" << x << ", y =" << y << std::endl;
						neuronGroup2.push_back(layerGroup2->nodeList.at(y));
					//}
			
			}
			std::cout << "The packing for a SynapseLayer's group 2 has ended" << std::endl;
		}
	}
	void SynapseLayer::packGroupTotal()
	{
		neuronGroupsCombind = std::vector<Neuron*>();
		std::cout << "The packing of a mass group between the two neuro groups Begins" << std::endl;
		std::cout << "Expect a "<< neuronGroup1.size() + neuronGroup2.size() << " sized sequence" << std::endl;
		for (int x = 0; x < neuronGroup1.size(); x++)
		{
			std::cout << "a SynapseLayer's neuronGroupTotal, is being populated with data from neuronGroup1 #=" << x << " of #" << neuronGroup1.size() << std::endl;
			neuronGroupsCombind.push_back(neuronGroup1.at(x));
		}
		for (int x = 0; x < neuronGroup2.size(); x++)
		{
			std::cout << "a SynapseLayer's neuronGroupTotal, is being populated with data from neuronGroup2 #=" << x << " of #" << neuronGroup1.size() << std::endl;
			neuronGroupsCombind.push_back(neuronGroup2.at(x));
		}
		std::cout << "The packing of a mass group between the two neuro groups Ends" << std::endl;
	}

	void SynapseLayer::packWeb()
	{
		std::cout << "The packing of a SynapseLayers Web is commencing" << std::endl;
		std::cout << "Expect a " << neuronGroup1.size() + neuronGroup2.size() << " sized sequence" << std::endl;
		web = std::vector<Synapse*>();
		if (autoFillVal == true) {
		for (int x = 0; x < neuronGroup1.size(); x++) {
			for (int y = 0; y < neuronGroup2.size(); y++) {
					std::cout << "a Synapse is being created and pushed into a SynapseLayers web" << std::endl;
					Synapse* Syn = new Synapse(this, randomise(boundsMin, boundsMax), neuronGroup1.at(x), neuronGroup2.at(y));
					web.push_back(Syn);
					neuronGroup1.at(x)->axonalConnections.push_back(Syn);
					neuronGroup2.at(y)->dendriticConnections.push_back(Syn);
					neuronGroup1.at(x)->axonalNeurons.push_back(neuronGroup2.at(y));
					neuronGroup2.at(y)->dendriticNeurons.push_back(neuronGroup1.at(x));
				}
			}
		}
		else if (autoFillVal == false) {
			for (int x = 0; x < neuronGroup1.size(); x++) {
				for (int y = 0; y < neuronGroup2.size(); y++) {
					float tempVal = 0.0f;
					std::cout << "Please input the starting weight for the synapse between neuron " << neuronGroup1.at(x) << " and " << neuronGroup2.at(y) << " In english it node group 1 at " << x << " and node group 2 at " << y << std::endl;
					std::cin >> tempVal;
					std::cout << "a Synapse is being created and pushed into a SynapseLayers web" << std::endl;
					Synapse* Syn = new Synapse(this, tempVal, neuronGroup1.at(x), neuronGroup2.at(y));
					web.push_back(Syn);
					neuronGroup1.at(x)->axonalConnections.push_back(Syn);
					neuronGroup2.at(y)->dendriticConnections.push_back(Syn);
					neuronGroup1.at(x)->axonalNeurons.push_back(neuronGroup2.at(y));
					neuronGroup2.at(y)->dendriticNeurons.push_back(neuronGroup1.at(x));
				}
			}
		}

		std::cout << "The packing of a SynapseLayers Web is ending" << std::endl;
	}

	void SynapseLayer::setBoundsMin(float val)
	{
		boundsMin = val;
		std::cout << "SynapseLayers minimum bounds has been set to #" << boundsMin << std::endl;
	}

	void SynapseLayer::modBoundsMin(float val)
	{
		boundsMin += val;
		std::cout << "SynapseLayers minimum bounds has been modifyed by #" << boundsMin << std::endl;
	}

	float SynapseLayer::getBoundsMin()
	{
		std::cout << "SynapseLayers minimum bounds are being returned"<< std::endl;
		return boundsMin;
	}

	void SynapseLayer::setBoundsMax(float val)
	{
		std::cout << "SynapseLayers maximum bounds has been set to #" << boundsMax << std::endl;
		boundsMax = val;
	}

	void SynapseLayer::modBoundsMax(float val)
	{
		boundsMax += val;
		std::cout << "SynapseLayers maximum bounds has been modifyed by #" << boundsMax << std::endl;
	}

	float SynapseLayer::getBoundsMax()
	{
		std::cout << "fetching a SynapseLayers maximum bounds" << std::endl;
		return boundsMax;
	}

	void SynapseLayer::setBounds(float max, float min)
	{
		boundsMax = max;
		boundsMin = min;
		std::cout << "In one fel swoop a SynapseLayers Max bounds has been set to #" << boundsMax << " and Min bounds has been set to #" << boundsMin << std::endl;
	}

	void SynapseLayer::modBounds(float max, float min)
	{
		boundsMax += max;
		boundsMin += min;
		std::cout << "In one fel swoop a SynapseLayers Max bounds has been modded by #" << boundsMax << " and Min bounds has been modded by #" << boundsMin << std::endl;
	}

	float SynapseLayer::randomise(int rangeMin, int rangeMax)
	{
		float r = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
		std::cout << "the SynapseLayer Randomise function has been called and has generated value #" << r << "from range #" << rangeMin << " to #" << rangeMax << ", also a float is being returned" << std::endl;
		return r;
	}

	void SynapseLayer::resetSynapses()
	{
	}

	std::vector<NodeLayer*>  SynapseLayer::CleanANodeLayer(std::vector<NodeLayer*> nodeLayerBank)
	{
		for (int x = 0; x < nodeLayerBank.size(); x++)
		{
			if (nodeLayerBank[x] == nullptr) {
				nodeLayerBank.erase(nodeLayerBank.begin() + x);
				x--;
			}
			else {

			}
			std::cout << "Layers Clean" << std::endl;
			return nodeLayerBank;
		}
	}

	std::vector<Neuron*> SynapseLayer::CleanANeuron(std::vector<Neuron*> neuronBank)
	{
		for (int x = 0; x < neuronBank.size(); x++)
		{
			if (neuronBank[x] == nullptr) {
				neuronBank.erase(neuronBank.begin() + x);
				x--;
			}
			else {

			}
			std::cout << "Layers Clean" << std::endl;
		}
		return neuronBank;
	}	
}