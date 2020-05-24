#include "stdafx.h"
#include "LearningAITestbed.h"

namespace GANnet {

	LearningAITestbed::LearningAITestbed(int numOfEMFs)
	{
		std::cout << "TestBed Constructor Started" << std::endl;
		eFeildsTotal = numOfEMFs;
		for (int x = 0; x < eFeildsTotal; x++) {
			loadFeild(new EmulsionFeild(this, numOfEMFs));
		}
		std::cout << "TestBed Constructed Ended" << std::endl;
	}

	LearningAITestbed::~LearningAITestbed()
	{
		std::cout << "end of TestBed destructor" << std::endl;
	}


	void LearningAITestbed::loadFeild(EmulsionFeild * ef)
	{
		eFeilds.push_back(ef);
		std::cout << "attaching EmulsionFeild to World" << std::endl;
	}

	std::vector<EmulsionFeild*> LearningAITestbed::getFeild()
	{
		std::cout << "fetching EmulsionFeild" << std::endl;
		return eFeilds;
	}

	void LearningAITestbed::addFeild(std::vector<EmulsionFeild*> modData)
	{
		for (int x = 0; x < modData.size(); x++) {
			eFeilds.push_back(modData.at(x));
		}
	}
}