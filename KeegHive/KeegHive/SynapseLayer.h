#pragma once
namespace GANnet {

	class SynapseLayer
	{
		friend class Synapse;
	public:
		SynapseLayer(NeuralNetwork* nw, NetTypes netType, NodeLayer* lhand, NodeLayer* rhand, float maxVal, float minVal, bool autoFill);
		SynapseLayer(NeuralNetwork* nw, NetTypes netType, bool autoFill);
		~SynapseLayer();
		float boundsMin; float boundsMax;
		NeuralNetwork* parent;
		NetTypes type;
		//groups of neurons with layertypes built in
		NodeLayer* layerGroup1;
		NodeLayer* layerGroup2;

		//extracted neurons from the groups, we can use these for the mathstuff
		std::vector<Neuron*> neuronGroup1;
		std::vector<Neuron*> neuronGroup2;
		std::vector<Neuron*> neuronGroupsCombind;
		
		//vector of synapes
		std::vector<Synapse*> web;

		void packGroup1();
		void packGroup2();
		void packGroupTotal();
		void packWeb();

		void setBoundsMin(float val);//change value to #
		void modBoundsMin(float val);//add or subtract
		float getBoundsMin();//return value of #
		
		void setBoundsMax(float val);//change value to #
		void modBoundsMax(float val);//add or subtract
		float getBoundsMax();//return value of #
		
		void setBounds(float max, float min); //change value to #
		void modBounds(float max, float min); //add or subtract

		float randomise(int rangeMin, int rangeMax);

		void resetSynapses();

		std::vector<Neuron*> CleanANeuron(std::vector<Neuron*> neuronBank);
		std::vector<NodeLayer*> CleanANodeLayer(std::vector<NodeLayer*> nodeLayerBank);

	private:
		bool autoFillVal;
	};
}