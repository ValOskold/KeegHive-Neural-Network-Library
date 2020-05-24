#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
namespace GANnet {
	class NodeLayer
	{
	public:
		friend class Neuron;
		friend class NeuralNetwork;
		//NodeLayer(NeuralNetwork* nw, NodeTypes nodeType, int numberOfNeurons, bool autocomplete, float rangeMin, float rangeMax, std::vector<std::vector<FuncTypes>> functionStruct, int sPos);
		NodeLayer(NeuralNetwork* nw, NodeTypes nodeType, int numberOfNeurons, std::vector<float>vals, std::vector<std::vector<FuncTypes>> functionStruct, int sPos);
		NodeLayer(NeuralNetwork* nw, NodeTypes nodeType, int numberOfNeurons, std::vector<std::vector<FuncTypes>> functionStruct, int sPos);
		~NodeLayer();
		NeuralNetwork* parent;
		NodeTypes type;
		//FuncTypes functionType;
		int numberOfNodes;
		std::vector<Neuron*>nodeList;
		float randMax; float randMin;
		int spritePos;

		NodeTypes getLayerType(NodeLayer* nl);
		void setLayerType(NodeLayer* nl, NodeTypes ntype);

		//FuncTypes getFuncType(FuncTypes* nl);
		//void setFuncType(NodeLayer* nl, FuncTypes ftype);

		bool getAutoCompleteType(NodeLayer* nl);
		void setAutoCompleteType(NodeLayer* nl, bool aComplete);

		void alterNumOfNeuronsByVal(NodeLayer* nl, int posOrNegVal);
		void alterNodeList(NodeLayer* nl, Neuron* cell, bool remove);
		void ModNeurons(valModType mType);
		void SetNeuronVal(valModType mType);
		void GenNeuronVal(valModType mType, int rangeMin, int rangeMax);

		void newNumberOfNodes(int newVal);

	private:
		float randomise(int rangeMin, int rangeMax);
		bool autoValue;
		void CleanTheLayer();
		void GenerateNeuron(int yPosVal, FuncTypes ft);
		bool autoFed;
		void FeedInputNeuron(int yPosVal, FuncTypes ft, float vals);
		void GenerateBlankNeuron(int yPosVal, FuncTypes ft);
		void GenerateBiasNeuron(int yPosVal);
	};
};