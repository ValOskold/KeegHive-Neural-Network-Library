#include "stdafx.h"
#include "Synapse.h"

namespace GANnet {

	Synapse::Synapse(SynapseLayer* sl, float val, Neuron* n1, Neuron* n2)
	{
		std::cout << "Synapse Constructor Entered" << std::endl;
		parent = sl;
		weight = val;
		cell1 = n1;
		cell2 = n2;
		std::cout << "Synapse Constructor Exited" << std::endl;
	}


	Synapse::~Synapse()
	{
		std::cout << "Synapse Destructor Entered and Exited" << std::endl;
	}

	void Synapse::modWeight(float posOrNegVal)//add or subtract
	{
		weight += posOrNegVal;
		std::cout << "Synapse weight val is being altered by #" << posOrNegVal << " it is now #" << weight << std::endl;
	}

	void Synapse::changeWeight(float val)//alter the value freely
	{
		std::cout << "Synapse weight val is being set to #" << val << ", it is now #" << weight << std::endl;
		weight = val;
	}

	float Synapse::getWeight()
	{
		return weight;
	}

	Neuron * Synapse::getCell1()
	{
		std::cout << "Synapse fetching Neuron 1" << std::endl;
		return cell1;
	}

	void Synapse::setCell1(Neuron* targetCell)
	{
		std::cout << "Synapse Neuron 1 has been changed to a new target" << std::endl;
		cell1 = targetCell;
	}

	Neuron * Synapse::getCell2()
	{
		std::cout << "Synapse fetching Neuron 2" << std::endl;
		return cell2;
	}

	void Synapse::setCell2(Neuron* targetCell)
	{
		std::cout << "Synapse Neuron 2 has been changed to a new target" << std::endl;
		cell2 = targetCell;
	}
	float Synapse::getGradiant(int pos)
	{
		return gradiant.at(pos);
	}
}