#pragma once
#include "tinyxml2.h"
using namespace tinyxml2;
namespace GANnet {

	class neuralnetFileReader
	{
	public:
		neuralnetFileReader();
		~neuralnetFileReader();

		void loadNeuron(XMLDocument doc);
		void loadNeuronLayer(XMLDocument doc);
		void loadSynapse(XMLDocument doc);
		void loadSynapseLayer(XMLDocument doc);
		void loadNeuralNet(XMLDocument doc);
		void loadEmulsionFeild(XMLDocument doc);

		void saveEmulsionFeild();
		void saveNeuralNet( );
		void saveSynapseLayer( );
		void saveSynapse( );
		void saveNeuronLayer( );
		void saveNeuron( );
	};
};
