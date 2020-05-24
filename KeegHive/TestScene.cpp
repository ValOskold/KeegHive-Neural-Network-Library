#include "stdafx.h"
#include "TestScene.h"
//#include "GLError.h"
#pragma once
#include "..\deps\include\vgl.h"
#include "..\deps\include\glm\glm\glm.hpp"
#include "..\deps\include\glm\glm\matrix.hpp"

const GLuint NumVertices = 4;
const GLuint NumVertices2 = 2;

//Shader* testShader = new Shader("triangles.vert", "triangles.frag");

const GLfloat vertices[] = {
	-0.15, 0.15, 0.0,
	0.15, 0.15, 0.0,
	0.15, -0.15, 0.0,
	-0.15, -0.15, 0.0
};

const GLfloat colorData[] = {
	1,0,0, // color for vertices
	0,1,0,
	0,0,1,
	1,1,1
};

TestScene::TestScene()
{

}

TestScene::~TestScene()
{
	for (int i = 0; i < neuronSpriteList.size() - 1; i++) {
		delete neuronSpriteList.at(i);
	}
	for (int i = 0; i < synapseSpriteList.size() - 1; i++) {
		delete synapseSpriteList.at(i);
	}
	emFeild->~EmulsionFeild();
	delete emFeild;
	delete world;
}

void TestScene::giveEngineReference(wonwonEngine * engine)
{
	this->engine = engine;
}

void TestScene::onStart()
{
	srand(time(NULL));
	std::cout << "world timer started" << std::endl;
	
	//engine->renderer->addCamera(engine->windowWidth, engine->windowHeight, 60.0f, 256.0f, 0.0500000000075f);
	//NeuralNetwork::learningDataSet dataSet;
	//dataSet.expectedInputData = expectedInput;
	//dataSet.expectedOutputData = expectedOutput;

	world = new LearningAITestbed(numberOfFeilds); //create world
	world->eFeilds.at(0) = new EmulsionFeild(world, hiddenLayers, inputNeuronList, hiddenNeuronList, outputNeuronList, iLayerFuncTypes, hLayerFuncTypes, oLayerFuncTypes, lRate, cycleTotal, acceptableErrorRate, expectedInput, expectedOutput);

	////we are adding the neuron sprites to a holder than injecting that holder into a new holder-holder
	////add the inputs from the neural network to a sprite list at pos 0
	//std::vector<Sprite*>tmpSpriteList = std::vector<Sprite*>();
	//for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->inputContainer->numberOfNodes + 1; x++) {
	//	tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
	//}
	//nnNeuronSprites.push_back(tmpSpriteList);

	////add the hiddenNeurons from the neural network to a sprite list at pos 1 to hiddenLayer Size
	//for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.size(); x++) {
	//	tmpSpriteList = std::vector<Sprite*>();
	//	for (int y = 0; y < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(x)->numberOfNodes + 1; y++) {
	//		tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
	//	}
	//	nnNeuronSprites.push_back(tmpSpriteList);
	//}

	////add the Outputs from the neural network to a sprite list at hiddenLayer.size() to ++1;
	//tmpSpriteList = std::vector<Sprite*>();
	//for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->outputContainer->numberOfNodes; x++) {
	//	tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
	//}
	//nnNeuronSprites.push_back(tmpSpriteList);

	////set up the neurons to have an offset based on relative positions, the ones in the same group are stack ontop of eachother, the diffrent groups are placed beside eachother
	//float tmpXoffset = 0;
	//for (int x = 0; x < nnNeuronSprites.size(); x++) {
	//	float tmpYoffset = 0;
	//	for (int y = 0; y < nnNeuronSprites.at(x).size(); y++) {
	//		nnNeuronSprites.at(x).at(y)->translate(glm::vec3(tmpXoffset, tmpYoffset, 0));
	//		tmpYoffset += 0.4;
	//	}
	//	tmpXoffset += 0.4;
	//}
	////In this chunk of code we are injecting into a vector<vec4> the data for the positional information of where the starting neurons are contained is and where the ending neurons are contained
	////Later we can use that to find the sprites in the corisponding container position which helps us find the center of the two neurons we can then draw a line between them
	////This does the first lines comment for the input to hidden layers
	//std::vector<Vec4>synPosList = std::vector<Vec4>();
	//for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.size(); x++) {
	//	Vec4 tmpV4 = Vec4(0.0, 0.0, 0.0, 0.0);
	//	for (int y = 0; y < world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.at(x)->axonalConnections.size(); y++) {
	//		tmpV4.w = world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.at(x)->spriteXspot;
	//		tmpV4.x = world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.at(x)->spriteYspot;
	//		tmpV4.y = world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.at(x)->axonalConnections.at(y)->cell2->spriteXspot;
	//		tmpV4.z = world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.at(x)->axonalConnections.at(y)->cell2->spriteYspot;
	//		synPosList.push_back(tmpV4);
	//	}
	//}
	////This does the first lines comment for the hidden layers and what they are synaptically connected to so the hidden to hidden layers and the hidden to output layer.
	//synapseSpriteLayers.push_back(synPosList);
	//for (int w = 0; w < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.size(); w++) {
	//	synPosList = std::vector<Vec4>();
	//	for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.size(); x++) {
	//		Vec4 tmpV4 = Vec4(0.0, 0.0, 0.0, 0.0);
	//		for (int y = 0; y < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.at(x)->axonalConnections.size(); y++) {
	//			tmpV4.w = world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.at(x)->spriteXspot;
	//			tmpV4.x = world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.at(x)->spriteYspot;
	//			tmpV4.y = world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.at(x)->axonalConnections.at(y)->cell2->spriteXspot;
	//			tmpV4.z = world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.at(x)->axonalConnections.at(y)->cell2->spriteYspot;
	//			synPosList.push_back(tmpV4);
	//		}
	//	}
	//	synapseSpriteLayers.push_back(synPosList);
	//}
	////Here we take the container positional data from the synapseSpriteLayers object and get the translation matrix from the nnNeuronSprites object this allows us to get the center position between the neurons 
	//for (int x = 0; x < synapseSpriteLayers.size(); x++){
	//	tmpSpriteList = std::vector<Sprite*>();
	//	for (int y = 0; y < synapseSpriteLayers.at(x).size(); y++) {
	//		glm::mat4 tmpMat4Pos1 = nnNeuronSprites.at(synapseSpriteLayers.at(x).at(y).w).at(synapseSpriteLayers.at(x).at(y).x)->getTranslationMatrix();
	//		glm::mat4 tmpMat4Pos2 = nnNeuronSprites.at(synapseSpriteLayers.at(x).at(y).y).at(synapseSpriteLayers.at(x).at(y).z)->getTranslationMatrix();
	//		
	//		const GLfloat vertices2[] = { tmpMat4Pos1[3][0], tmpMat4Pos1[3][1], 0.0f, tmpMat4Pos2[3][0],tmpMat4Pos2[3][1], 0.0f }; //closer than 1

	//		tmpSpriteList.push_back(new Sprite(vertices2, colorData, NumVertices2, testShader, GL_LINES)); //why are all the lines drawing down?
	//		std::cout << "";
	//	}
	//	nnSynapseSprites.push_back(tmpSpriteList);
	//}

	engine->renderer->loadNewCamera("CustomCam1");
	engine->renderer->getCameraAtPos(0)->setViewMatrix(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	engine->renderer->getCameraAtPos(0)->setProjectionMatrix(-1.0f, 1.0f, -1.0f, 1.0f, 0.2f, 10.0f);
	}

	void TestScene::onPreRender()
	{
		Shader* testShader = new Shader("triangles.vert", "triangles.frag");
		//we are adding the neuron sprites to a holder than injecting that holder into a new holder-holder
		//add the inputs from the neural network to a sprite list at pos 0
		std::vector<Sprite*>tmpSpriteList = std::vector<Sprite*>();
		for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->inputContainer->numberOfNodes + 1; x++) {
			tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
		}
		nnNeuronSprites.push_back(tmpSpriteList);

		//add the hiddenNeurons from the neural network to a sprite list at pos 1 to hiddenLayer Size
		for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.size(); x++) {
			tmpSpriteList = std::vector<Sprite*>();
			for (int y = 0; y < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(x)->numberOfNodes + 1; y++) {
				tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
			}
			nnNeuronSprites.push_back(tmpSpriteList);
		}

		//add the Outputs from the neural network to a sprite list at hiddenLayer.size() to ++1;
		tmpSpriteList = std::vector<Sprite*>();
		for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->outputContainer->numberOfNodes; x++) {
			tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
		}
		nnNeuronSprites.push_back(tmpSpriteList);

		//set up the neurons to have an offset based on relative positions, the ones in the same group are stack ontop of eachother, the diffrent groups are placed beside eachother
		float tmpXoffset = 0;
		for (int x = 0; x < nnNeuronSprites.size(); x++) {
			float tmpYoffset = 0;
			for (int y = 0; y < nnNeuronSprites.at(x).size(); y++) {
				nnNeuronSprites.at(x).at(y)->translate(glm::vec3(tmpXoffset, tmpYoffset, 0));
				tmpYoffset += 0.4;
			}
			tmpXoffset += 0.4;
		}
		//In this chunk of code we are injecting into a vector<vec4> the data for the positional information of where the starting neurons are contained is and where the ending neurons are contained
		//Later we can use that to find the sprites in the corisponding container position which helps us find the center of the two neurons we can then draw a line between them
		//This does the first lines comment for the input to hidden layers
		std::vector<Vec4>synPosList = std::vector<Vec4>();
		for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.size(); x++) {
			Vec4 tmpV4 = Vec4(0.0, 0.0, 0.0, 0.0);
			for (int y = 0; y < world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.at(x)->axonalConnections.size(); y++) {
				tmpV4.w = world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.at(x)->spriteXspot;
				tmpV4.x = world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.at(x)->spriteYspot;
				tmpV4.y = world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.at(x)->axonalConnections.at(y)->cell2->spriteXspot;
				tmpV4.z = world->eFeilds.at(0)->mindPool.at(0)->inputContainer->nodeList.at(x)->axonalConnections.at(y)->cell2->spriteYspot;
				synPosList.push_back(tmpV4);
			}
		}
		//This does the first lines comment for the hidden layers and what they are synaptically connected to so the hidden to hidden layers and the hidden to output layer.
		synapseSpriteLayers.push_back(synPosList);
		for (int w = 0; w < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.size(); w++) {
			synPosList = std::vector<Vec4>();
			for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.size(); x++) {
				Vec4 tmpV4 = Vec4(0.0, 0.0, 0.0, 0.0);
				for (int y = 0; y < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.at(x)->axonalConnections.size(); y++) {
					tmpV4.w = world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.at(x)->spriteXspot;
					tmpV4.x = world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.at(x)->spriteYspot;
					tmpV4.y = world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.at(x)->axonalConnections.at(y)->cell2->spriteXspot;
					tmpV4.z = world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(w)->nodeList.at(x)->axonalConnections.at(y)->cell2->spriteYspot;
					synPosList.push_back(tmpV4);
				}
			}
			synapseSpriteLayers.push_back(synPosList);
		}
		//Here we take the container positional data from the synapseSpriteLayers object and get the translation matrix from the nnNeuronSprites object this allows us to get the center position between the neurons 
		for (int x = 0; x < synapseSpriteLayers.size(); x++){
			tmpSpriteList = std::vector<Sprite*>();
			for (int y = 0; y < synapseSpriteLayers.at(x).size(); y++) {
				glm::mat4 tmpMat4Pos1 = nnNeuronSprites.at(synapseSpriteLayers.at(x).at(y).w).at(synapseSpriteLayers.at(x).at(y).x)->getTranslationMatrix();
				glm::mat4 tmpMat4Pos2 = nnNeuronSprites.at(synapseSpriteLayers.at(x).at(y).y).at(synapseSpriteLayers.at(x).at(y).z)->getTranslationMatrix();
				
				const GLfloat vertices2[] = { tmpMat4Pos1[3][0], tmpMat4Pos1[3][1], 0.0f, tmpMat4Pos2[3][0],tmpMat4Pos2[3][1], 0.0f }; //closer than 1

				tmpSpriteList.push_back(new Sprite(vertices2, colorData, NumVertices2, testShader, GL_LINES)); //why are all the lines drawing down?
				std::cout << "";
			}
			nnSynapseSprites.push_back(tmpSpriteList);
		}
		engine->renderer->loadNewCamera("CustomCam1");
		engine->renderer->getCameraAtPos(0)->setViewMatrix(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		engine->renderer->getCameraAtPos(0)->setProjectionMatrix(-1.0f, 1.0f, -1.0f, 1.0f, 0.2f, 10.0f);
	}

	void TestScene::onRender()
	{
		Shader* testShader = new Shader("triangles.vert", "triangles.frag");
		//we are adding the neuron sprites to a holder than injecting that holder into a new holder-holder
		//add the inputs from the neural network to a sprite list at pos 0
		std::vector<Sprite*>tmpSpriteList = std::vector<Sprite*>();
		for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->inputContainer->numberOfNodes + 1; x++) {
			tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
		}
		nnNeuronSprites.push_back(tmpSpriteList);

		//add the hiddenNeurons from the neural network to a sprite list at pos 1 to hiddenLayer Size
		for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.size(); x++) {
			tmpSpriteList = std::vector<Sprite*>();
			for (int y = 0; y < world->eFeilds.at(0)->mindPool.at(0)->hiddenContainer.at(x)->numberOfNodes + 1; y++) {
				tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
			}
			nnNeuronSprites.push_back(tmpSpriteList);
		}

		//add the Outputs from the neural network to a sprite list at hiddenLayer.size() to ++1;
		tmpSpriteList = std::vector<Sprite*>();
		for (int x = 0; x < world->eFeilds.at(0)->mindPool.at(0)->outputContainer->numberOfNodes; x++) {
			tmpSpriteList.push_back(new Sprite(vertices, colorData, NumVertices, testShader, GL_QUADS));
		}
		nnNeuronSprites.push_back(tmpSpriteList);

		//set up the neurons to have an offset based on relative positions, the ones in the same group are stack ontop of eachother, the diffrent groups are placed beside eachother
		float tmpXoffset = 0;
		for (int x = 0; x < nnNeuronSprites.size(); x++) {
			float tmpYoffset = 0;
			for (int y = 0; y < nnNeuronSprites.at(x).size(); y++) {
				nnNeuronSprites.at(x).at(y)->translate(glm::vec3(tmpXoffset, tmpYoffset, 0));
				tmpYoffset += 0.4;
			}
			tmpXoffset += 0.4;
		}
	
	}

	void TestScene::onPostRender()
	{
		nnNeuronSprites = std::vector<std::vector<Sprite*>>();
		nnSynapseSprites = std::vector<std::vector<Sprite*>>();
	}

	void TestScene::onUpdate(GLdouble deltaTime)
	{
		glfwSwapBuffers(engine->window);

		if (engine->inputManager->hasKeyBeenPressed(KEY_1) == true) {
			world->eFeilds.at(0)->mindPool.at(0)->addRandomNeuron();
		}
		if (engine->inputManager->hasKeyBeenPressed(KEY_2) == true) {
			world->eFeilds.at(0)->mindPool.at(0)->addRandomSynapse();
		}
		if (engine->inputManager->hasKeyBeenPressed(KEY_3) == true) {
			world->eFeilds.at(0)->mindPool.at(0)->pruneRandomNeuron();
		}
		if (engine->inputManager->hasKeyBeenPressed(KEY_4) == true) {
			world->eFeilds.at(0)->mindPool.at(0)->pruneRandomSynapse();
		}

		if (engine->inputManager->hasKeyBeenRepeated(KEY_A) == true) {
			for (int i = 0; i < nnNeuronSprites.size(); i++) {
				for (int z = 0; z < nnNeuronSprites.at(i).size(); z++) {
					nnNeuronSprites.at(i).at(z)->translate(glm::vec3(-0.01, 0, 0));
				}
			}
			for (int i = 0; i < nnSynapseSprites.size(); i++) {
				for (int z = 0; z < nnSynapseSprites.at(i).size(); z++) {
					nnSynapseSprites.at(i).at(z)->translate(glm::vec3(-0.01, 0, 0));
				}
			}
		}

		if (engine->inputManager->hasKeyBeenRepeated(KEY_W) == true) {
			for (int i = 0; i < nnNeuronSprites.size(); i++) {
				for (int z = 0; z < nnNeuronSprites.at(i).size(); z++) {
					nnNeuronSprites.at(i).at(z)->translate(glm::vec3(0, 0.01, 0));
				}
			}
			
			for (int i = 0; i < nnSynapseSprites.size(); i++) {
				for (int z = 0; z < nnSynapseSprites.at(i).size(); z++) {
					nnSynapseSprites.at(i).at(z)->translate(glm::vec3(0, 0.01, 0));
				}
			}
		}
		
		if (engine->inputManager->hasKeyBeenRepeated(KEY_D) == true) {
			for (int i = 0; i < nnNeuronSprites.size(); i++) {
				for (int z = 0; z < nnNeuronSprites.at(i).size(); z++) {
					nnNeuronSprites.at(i).at(z)->translate(glm::vec3(0.01, 0, 0));
				}
			}
			for (int i = 0; i < nnSynapseSprites.size(); i++) {
				for (int z = 0; z < nnSynapseSprites.at(i).size(); z++) {
					nnSynapseSprites.at(i).at(z)->translate(glm::vec3(0.01, 0, 0));
				}
			}
		}
		
		if (engine->inputManager->hasKeyBeenRepeated(KEY_S) == true) {
			for (int i = 0; i < nnNeuronSprites.size(); i++) {
				for (int z = 0; z < nnNeuronSprites.at(i).size(); z++) {
					nnNeuronSprites.at(i).at(z)->translate(glm::vec3(0, -0.01, 0));
				}
			}
			for (int i = 0; i < nnSynapseSprites.size(); i++) {
				for (int z = 0; z < nnSynapseSprites.at(i).size(); z++) {
					nnSynapseSprites.at(i).at(z)->translate(glm::vec3(0, -0.01, 0));
				}
			}
		}
	}

	void TestScene::onPostUpdate()
	{
	}

	void TestScene::onEnd()
	{
	}