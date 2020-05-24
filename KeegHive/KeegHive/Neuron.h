#pragma once
#include "NodeLayer.h"
#include <vector>
namespace GANnet {
	class Neuron{
		friend class Synapse;
		public:
			Neuron(NodeLayer* attachedLayer, NodeTypes nodeType, FuncTypes funcType, float nodeValue, int xPos, int yPos);
			Neuron(NodeLayer* attachedLayer, NodeTypes nodeType, FuncTypes funcType, int xPos, int yPos);
			Neuron(NodeLayer* attachedLayer, NodeTypes nodeType, int xPos, int yPos);
			Neuron(NodeLayer* attachedLayer, NodeTypes nodeType, float nodeValue, int xPos, int yPos);
			~Neuron();
			enum NodeTypes type;
			enum FuncTypes functionType;
			NodeLayer* parent;
			float valPreActivator;
			float valPostActivator;
			std::vector<float> partialDeriviative;
			std::vector<Synapse*>axonalConnections; //transmitter relationships
			std::vector<Synapse*>dendriticConnections; //receiver relationships
			std::vector<Neuron*>axonalNeurons; //transmitter relationships
			std::vector<Neuron*>dendriticNeurons; //receiver relationships

			void modPreActivatorVal(float valPosOrNeg);
			void modPostActivatorVal(float valPosOrNeg);
			void setPreActivatorVal(float preActiveVal);
			void setPostActivatorVal(float postActiveVal);
			void setPreOrPostToRand(valModType mType, int rangeMin, int rangeMax);
			float getPreVal();
			float getPostVal();
			float getPartialDeriviative(int pos);
			
			NodeTypes getType();
			void changeType(NodeTypes nType);
			void vRandomise(valModType mType, int rangeMin, int rangeMax);
			std::vector<Synapse*>getAxonalConnections();
			std::vector<Synapse*>getDendriticConnections();
			std::vector<Neuron*>getAxonalNeurons();
			std::vector<Neuron*>getDendriticNeurons(); 

			int spriteXspot;
			int spriteYspot;

			FuncTypes getFType();
			void setFucType(FuncTypes ft);
	private:
		float randomise(int rangeMin, int rangeMax);
		//void vRandomise(valModType mType, int rangeMin, int rangeMax);
	};
}