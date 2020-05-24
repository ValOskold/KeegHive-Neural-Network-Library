#pragma once
namespace GANnet{
	class Synapse
	{
		public:
		Synapse(SynapseLayer* sl, float val, Neuron* n1, Neuron* n2);
		~Synapse();
		SynapseLayer* parent;
		float weight;
		std::vector<float> gradiant;
		float tGradiant = 0;
		Neuron* cell1;
		Neuron* cell2;

		void modWeight(float posOrNegVal);
		void changeWeight(float val);
		float getWeight();
		Neuron* getCell1();
		void setCell1(Neuron* targetCell);
		Neuron* getCell2();
		void setCell2(Neuron* targetCell);
		float getGradiant(int pos);
	};
}