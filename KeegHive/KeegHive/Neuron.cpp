#include "stdafx.h"
#include "Neuron.h"

namespace GANnet {

	Neuron::Neuron(NodeLayer* attachedLayer, NodeTypes nodeType, FuncTypes funcType, float nodeValue, int xPos, int yPos)
	{
		std::cout << "Neuron Constructor Entered" << std::endl;
		parent = attachedLayer;
		type = nodeType;
		valPreActivator = nodeValue;
		functionType = funcType;
		spriteXspot = xPos;
		spriteYspot = yPos;
		std::cout << "Neuron Constructor Exited" << std::endl;
	}

	Neuron::Neuron(NodeLayer * attachedLayer, NodeTypes nodeType, FuncTypes funcType, int xPos, int yPos)
	{
		std::cout << "Neuron Constructor Entered" << std::endl;
		parent = attachedLayer;
		type = nodeType;
		functionType = funcType;
		spriteXspot = xPos;
		spriteYspot = yPos;
		std::cout << "Neuron Constructor Exited" << std::endl;
	}

	Neuron::Neuron(NodeLayer * attachedLayer, NodeTypes nodeType, int xPos, int yPos)
	{
		std::cout << "Neuron Constructor Entered" << std::endl;
		parent = attachedLayer;
		type = nodeType;
		spriteXspot = xPos;
		spriteYspot = yPos;
		std::cout << "Neuron Constructor Exited" << std::endl;
	}

	Neuron::Neuron(NodeLayer * attachedLayer, NodeTypes nodeType, float nodeValue, int xPos, int yPos)
	{
		std::cout << "Neuron Constructor Entered" << std::endl;
		parent = attachedLayer;
		type = nodeType;
		valPreActivator = nodeValue;
		spriteXspot = xPos;
		spriteYspot = yPos;
		std::cout << "Neuron Constructor Exited" << std::endl;
	}

	void Neuron::modPreActivatorVal(float valPosOrNeg)
	{
		valPreActivator += valPosOrNeg;
		std::cout << "Neuron PreActivatorVal has been modifyed by #" << valPosOrNeg << std::endl;
	}

	void Neuron::modPostActivatorVal(float valPosOrNeg)
	{
		valPostActivator += valPosOrNeg;
		std::cout << "Neuron PostActivatorVal has been modifyed by #" << valPosOrNeg << std::endl;
	}

	void Neuron::setPreActivatorVal(float preActiveVal)
	{
		valPreActivator = preActiveVal;
		std::cout << "Neuron PreActivatorVal has been set to #" << preActiveVal << std::endl;
	}

	void Neuron::setPostActivatorVal(float postActiveVal)
	{
		valPostActivator = postActiveVal;
		std::cout << "Neuron PostActivatorVal has been set to #" << postActiveVal << std::endl;
	}

	NodeTypes Neuron::getType()
	{
		return type;
	}

	void Neuron::changeType(NodeTypes nType)
	{
		type = nType;
		std::cout << "a Neuron has had its type transMuted to type " << nType << std::endl;
	}

	FuncTypes Neuron::getFType()
	{
		return functionType;
	}

	void Neuron::setFucType(FuncTypes ft)
	{
		functionType = ft;
	}

	float Neuron::randomise(int rangeMin, int rangeMax)
	{
		float r = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
		std::cout << "the Neuron Randomise function has been called and has generated value #" << r << "from range #" << rangeMin << " to #" << rangeMax << ", also a float is being returned" << std::endl;
		return r;
	}

	void Neuron::vRandomise(valModType mType, int rangeMin, int rangeMax)
	{
		if (mType == valModType::PREACTIVATION) {
			valPreActivator = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			std::cout << "the Neuron Randomise function has been called, has generated and set a value for a Neurons PreActivation Float #" << valPreActivator << "from range #" << rangeMin << " to #" << rangeMax << std::endl;
		}
		else if (mType == valModType::POSTACTIVATION) {
			valPostActivator = rangeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (rangeMax - rangeMin)));
			std::cout << "the Neuron Randomise function has been called, has generated and set a value for a Neurons PostActivation Float #" << valPostActivator << "from range #" << rangeMin << " to #" << rangeMax << std::endl;
		}
	}

	std::vector<Synapse*> Neuron::getAxonalConnections()
	{
		return axonalConnections;
	}

	std::vector<Synapse*> Neuron::getDendriticConnections()
	{
		return dendriticConnections;
	}

	std::vector<Neuron*> Neuron::getAxonalNeurons()
	{
		return axonalNeurons;
	}

	std::vector<Neuron*> Neuron::getDendriticNeurons()
	{
		return dendriticNeurons;
	}

	void Neuron::setPreOrPostToRand(valModType mType, int rangeMin, int rangeMax)
	{
		if (mType == valModType::PREACTIVATION) {
				valPreActivator = std::rand() % rangeMax + rangeMin;
				std::cout << "the Neuron Randomise function has been called, has generated and set a value for a Neurons PreActivation Float #" << valPreActivator << "from range #" << rangeMin << " to #" << rangeMax << std::endl;
		}
		else if (mType == valModType::POSTACTIVATION) {

				valPostActivator = std::rand() % rangeMax + rangeMin;
				std::cout << "the Neuron Randomise function has been called, has generated and set a value for a Neurons PostActivation Float #" << valPostActivator << "from range #" << rangeMin << " to #" << rangeMax << std::endl;
		}
	}

	float Neuron::getPreVal()
	{
		return valPreActivator;
	}

	float Neuron::getPostVal()
	{
		return valPostActivator;
	}

	float Neuron::getPartialDeriviative(int pos)
	{
		return partialDeriviative.at(pos);
	}

	Neuron::~Neuron()
	{
		std::cout << "Neuron Destructor Entered and Exited" << std::endl;
	}
}