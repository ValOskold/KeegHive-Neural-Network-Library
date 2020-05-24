#include "stdafx.h"
#include "neuralnetFileReader.h"

namespace GANnet {
	neuralnetFileReader::neuralnetFileReader()
	{
		tinyxml2::XMLDocument doc;
		doc.SaveFile("nnMASTERFILE.xml");
	}


	neuralnetFileReader::~neuralnetFileReader()
	{
	}
};
