#pragma once
#include <random>
#include <iostream>
#include <vector>
#include <list>
//#include "EmulsionFeild.h"
#include "Vector.h"
using namespace MATH;
namespace GANnet {
	class LearningAITestbed
	{
	public:
		friend class EmulsionFeild;
		LearningAITestbed(int numOfEMFs);
		~LearningAITestbed();
		int eFeildsTotal;
		std::vector<EmulsionFeild*>eFeilds;
		std::vector<EmulsionFeild*>getFeild();
		void loadFeild(EmulsionFeild* ef);
		void addFeild(std::vector<EmulsionFeild*> modData);
	};
}//end of namespace