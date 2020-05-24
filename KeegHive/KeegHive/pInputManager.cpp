#include "stdafx.h"
#include "pInputManager.h"
#include <stdio.h>

//singleton
pInputManager* pInputManager::_instance = 0;
void pInputManager::Initialize(GLFWwindow * window, pInputHandler * inputHandler)
{
}

pInputManager* pInputManager::instance(GLFWwindow* w)
{
	//Create a new instance if none exists
	if (_instance == 0)
	{
		_instance = new pInputManager(w);
	}
	return _instance;
}

//constructor
pInputManager::pInputManager(GLFWwindow *w)
{
	keyRegistry = std::vector<keyStruct>();
}

//destructor
pInputManager::~pInputManager()
{
	delete _instance;
}

//set error callback
void pInputManager::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description); //prints the error with description
}

//keyboard methods begin here

//here is the method that uses the KeyStructure
void pInputManager::advancedKey_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	//track time
	double time = glfwGetTime();
	//create instance due to it being a static method
	pInputManager* tempContainer = pInputManager::instance(window);
	//call the key registering function
	tempContainer->keyStruct_Register(time, true, true, static_cast<keyName>(key), tempContainer, action);
}

//this method is called by advancedKey_callback it is not static
void pInputManager::keyStruct_Register(double pressTime, bool keyLastPressed, bool iChecked, keyName sName, pInputManager* pInstance, int state)
{
	keyStruct fKey; //create a empty keyStructure
					//loop through the registered keys
	for (int x = 0; x < keyRegistry.size(); ++x)
	{
		//check if the keys at x == the key value
		if (keyRegistry.at(x).name == static_cast<keyName>(sName))
		{
			//check key state and update the values of the key pressed
			if (state == GLFW_PRESS)
			{
				//std::cout << static_cast<keyName>(sName) << " IS PRESSED" << std::endl;
				keyRegistry.at(x).currentlyDown = true; //if im pressed i must be down
				keyRegistry.at(x).pThisFrame = true; //if i got pressed i must be delt with
			}
			//else if (state == GLFW_REPEAT) //not required
			//{
			//	std::cout << static_cast<keyName>(sName) << " IS HELD" << std::endl;
			//	keyRegistry.at(x).currentlyDown = true;
			//	keyRegistry.at(x).keyHeld = true;

			//}
			else if (state == GLFW_RELEASE)
			{
				//std::cout << static_cast<keyName>(sName) << " IS RELEASED" << std::endl;
				keyRegistry.at(x).currentlyDown = false;//if im released i must be up
				keyRegistry.at(x).keyHeld = false;//no way im held if im not touched
				keyRegistry.at(x).pThisFrame = false;//im not down i dont need to be delt with
				keyRegistry.at(x).pressTime = 0;//reset to 0

			}
			//if this if executes then return because were dont want to create a new key
			return;
		}
	}
	//register a key if one is pressed but not registered
	if (fKey.name == KEY_UNKNOWN)
	{
		//register the keys if its pressed but not registered
		if (state == GLFW_PRESS)
		{
			fKey = keyStruct(0, true, false, true, static_cast<keyName>(sName));//create real key
																				//std::cout << "IM Created as PRESSED" << std::endl;
			pInstance->keyRegistry.push_back(fKey);//push key to keyRegistry
		}
		else if (state == GLFW_RELEASE)
		{
			fKey = keyStruct(0, false, false, false, static_cast<keyName>(sName));//create real key
																				  //std::cout << "IM Created as RELEASED" << std::endl;
			pInstance->keyRegistry.push_back(fKey);//push key to keyRegistry
		}

	}
}

//here is the update method for the InputManager
void pInputManager::inputUpdate(double deltaTime)
{
	//loop through the register of keys
	for (int i = 0; i < keyRegistry.size(); i++)
	{
		keyStruct tempKey = keyRegistry[i]; //accessor not the actual object

											//keyName kn = keyRegistry[i].name;
											//bool pressedState = hasKeyBeenPressed(kn);
											//std::cout << keyRegistry[i].name << " Has the 'up or down' value set to : " << pressedState << std::endl;

											//if a looped key is found to be down, update their time held and call the hasKeyBeenChecked method
		if (tempKey.currentlyDown == true)
		{
			keyName kn = keyRegistry[i].name;
			bool checkedState = hasKeyBeenChecked(kn); //even if your not checking the bool returned, we still want this active so it can set a value within the register
													   //std::cout << keyRegistry[i].name << " Has the 'checked this frame' value set to : " << checkedState << std::endl;
													   //bool heldState = hasKeyBeenRepeated(kn);
													   //std::cout << keyRegistry[i].name << " Has the 'is held' value set to : " << heldState << std::endl;
			keyRegistry[i].pressTime += deltaTime; //trying to set it from the registry does work
												   //tempKey.pressTime += deltaTime; //trying to set it from the accessor does not work
												   //std::cout << keyRegistry[i].name << " Has been pressed for : " << keyRegistry[i].pressTime << " blips!" << std::endl;
		}
	}

	//loop through the register of clicks
	for (int i = 0; i < clickRegistry.size(); i++)
	{
		clickStruct tempClick = clickRegistry[i]; //accessor not the actual object

												  //clickName cn = clickRegistry[i].name;
												  //bool pressedState = hasClickBeenPressed(cn);
												  //std::cout << clickRegistry[i].name << " Has the 'up or down' value set to : " << pressedState << std::endl;

												  //if a looped key is found to be down, update their time held and call the hasClickBeenChecked method
		if (tempClick.upOrDown == true)
		{
			clickName cn = clickRegistry[i].name;
			bool checkedState = hasClickBeenChecked(cn); //even if your not checking the bool returned, we still want this active so it can set a value within the register
														 //std::cout << clickRegistry[i].name << " Has the 'checked this frame' value set to : " << checkedState << std::endl;
														 //bool heldState = hasClickBeenRepeated(cn);
														 //std::cout << clickRegistry[i].name << " Has the 'is held' value set to : " << heldState << std::endl;
			clickRegistry[i].pressTime += deltaTime; //trying to set it from the registry does work
													 //tempClick.pressTime += deltaTime; //trying to set it from the accessor does not work
													 //std::cout << clickRegistry[i].name << " Has been pressed for : " << clickRegistry[i].pressTime << " blips!" << std::endl;
		}
	}

	//loop through the register of buttons
	for (int i = 0; i < btnRegistry.size(); i++)
	{
		btnStruct tempAction = btnRegistry[i]; //accessor not the actual object

											   //std::cout << tempAction.name << std::endl;
											   //std::cout << tempAction.commandHeld << std::endl;
											   //std::cout << tempAction.pThisFrame << std::endl;
											   //std::cout << tempAction.timeHeld << std::endl;

		if (tempAction.commandHeld == true && tempAction.name != buttonName::BTN_UNKNOWN) //check to see if the button is being held
		{
			buttonName cn = btnRegistry[i].name;			bool checkedState = hasBtnBeenChecked(cn);

			btnRegistry[i].timeHeld += deltaTime; //add to the time held
												  //std::cout << cn << " Has been pressed for : " << btnRegistry[i].timeHeld << " blips!" << std::endl;
		}
	}

	//loop through the register of axis
	//std::vector<axisStruct> tempStruct = axisRegistry;
	//std::cout << "test" << std::endl;
	//for (int i = 0; i < axisRegistry.size(); i++)
	//{
	//axisStruct tempAction = axisRegistry[i]; //accessor not the actual object
	//if (axisRegistry[i].isAlive = true)
	//{
	//axisRegistry[i].pressureVal = returnPressure(axisRegistry[i].name);
	//}
	//}
}

//test to see if a key has been delt with
bool pInputManager::hasKeyBeenChecked(keyName name)
{
	//loop through the register
	for (int i = 0; i < keyRegistry.size(); i++)
	{
		if (keyRegistry[i].name == name) //if the name is what we want
		{
			if (keyRegistry[i].pThisFrame == true) //if the key has not been delt with
			{
				keyRegistry[i].pThisFrame = false; //deal with key
				return true; //return true if key has been delt with
			}
		}
	}
	return false; //if no key has been delt with return false
}

//check to see if a key is held for more than one calculation
bool pInputManager::hasKeyBeenRepeated(keyName name)
{
	for (int i = 0; i < keyRegistry.size(); i++) //loop the registry
	{
		if (keyRegistry[i].name == name) //check for wanted key
		{
			if (keyRegistry[i].currentlyDown == true && keyRegistry[i].pThisFrame == false) //if its down and yet has not been managed
			{
				keyRegistry[i].keyHeld = true;//alter value
				return true;//if this ran then its clearly heald
			}
		}
	}
	return false;//if this did not run then its clearly not being held
}

//return true if a key is down and false if the key is up
bool pInputManager::hasKeyBeenPressed(keyName name)
{
	for (int i = 0; i < keyRegistry.size(); i++)//loop registry
	{
		if (keyRegistry[i].name == name) //check for keys name
		{
			if (keyRegistry[i].currentlyDown == true)
			{
				return true; //if the key is down return true
			}
			else
			{
				return false; //if they key is not down return false
			}
		}
	}
	return false;//if this never hit then return false
}
//keyboard methods end

//advanced mouse methods
void pInputManager::advancedClick_callback(GLFWwindow * window, int button, int action, int mods)
{
	//track time
	double time = glfwGetTime();
	//create instance due to it being a static method
	pInputManager* tempContainer = pInputManager::instance(window);
	//call the key registering function
	tempContainer->clickStruct_Register(time, true, true, true, static_cast<clickName>(button), tempContainer, action);
}

void pInputManager::clickStruct_Register(double pressTime, bool currentlyDown, bool boolHeld, bool clickedThisFrame, clickName cName, pInputManager * pInstance, int state)
{
	clickStruct fClick; //create a empty clickStructure
						//loop through the registered clickes
	for (int x = 0; x < clickRegistry.size(); ++x)
	{
		//check if the keys at x == the key value
		if (clickRegistry.at(x).name == static_cast<clickName>(cName))
		{
			//check key state and update the values of the key pressed
			if (state == GLFW_PRESS)
			{
				//std::cout << static_cast<clickName>(cName) << " Is PRESSED" << std::endl;
				clickRegistry.at(x).upOrDown = true; //if im clicked i must be down
				clickRegistry.at(x).cThisFrame = true; //if i got clicked i must be delt with
			}
			//else if (state == GLFW_REPEAT) //not required
			//{
			//std::cout << static_cast<clickName>(cName) << " IS HELD" << std::endl;
			//clickRegistry.at(x).upOrDown = true;
			//clickRegistry.at(x).clickHeld = true;

			//}
			else if (state == GLFW_RELEASE)
			{
				//std::cout << static_cast<clickName>(cName) << " IS RELEASED" << std::endl;
				clickRegistry.at(x).upOrDown = false;//if im released i must be up
				clickRegistry.at(x).clickHeld = false;//no way im held if im not touched
				clickRegistry.at(x).cThisFrame = false;//im not down i dont need to be delt with
				clickRegistry.at(x).pressTime = 0;//reset to 0

			}
			//if this if executes then return because were dont want to create a new key
			return;
		}
	}
	//register a key if one is pressed but not registered
	if (fClick.name == KEY_UNKNOWN)
	{
		//register the keys if its pressed but not registered
		if (state == GLFW_PRESS)
		{
			fClick = clickStruct(0, true, false, true, static_cast<clickName>(cName));//create real clickValue
																					  //std::cout << "IM Created as PRESSED" << std::endl;
			pInstance->clickRegistry.push_back(fClick);//push key to clickRegistry
		}
		else if (state == GLFW_RELEASE)
		{
			fClick = clickStruct(0, false, false, false, static_cast<clickName>(cName));//create real clickValue
																						//std::cout << "IM Created as RELEASED" << std::endl;
			pInstance->clickRegistry.push_back(fClick);//push key to clickRegistry
		}

	}
}

bool pInputManager::hasClickBeenChecked(clickName name)
{
	//loop through the register
	for (int i = 0; i < clickRegistry.size(); i++)
	{
		if (clickRegistry[i].name == name) //if the name is what we want
		{
			if (clickRegistry[i].cThisFrame == true) //if the click has not been delt with
			{
				clickRegistry[i].cThisFrame = false; //deal with the click
				return true; //return true if the click has been delt with
			}
		}
	}
	return false; //if no click has been delt with return false
}

bool pInputManager::hasClickBeenRepeated(clickName name)
{
	for (int i = 0; i < clickRegistry.size(); i++) //loop the registry
	{
		if (clickRegistry[i].name == name) //check for the wanted click
		{
			if (clickRegistry[i].upOrDown == true && clickRegistry[i].cThisFrame == false) //if its down and yet has not been managed
			{
				clickRegistry[i].clickHeld = true;//alter value
				return true;//if this ran then its clearly heald
			}
		}
	}
	return false;//if this did not run then its clearly not being held
}

bool pInputManager::hasClickBeenPressed(clickName name)
{
	for (int i = 0; i < clickRegistry.size(); i++)//loop registry
	{
		if (clickRegistry[i].name == name) //check for clicks name
		{
			if (clickRegistry[i].upOrDown == true)
			{
				return true; //if the click is down return true
			}
			else
			{
				return false; //if they click is not down return false
			}
		}
	}
	return false;//if this never hit then return false
}

//mouse methods start
//prints the users mouse position
void pInputManager::cursorPositionCallback(double xPosition, double yPosition)
{
	std::cout << xPosition << " : " << yPosition << std::endl;
}

//print a tell if the mouse enters or leaves the screen
void pInputManager::cursorEnterCallback(int enteredScreen)
{
	if (enteredScreen)
	{
		std::cout << "Within Window" << std::endl;
	}
	else
	{
		std::cout << "Out of Window" << std::endl;
	}
}

//a callback that alerts the user how much they are scrolling by
void pInputManager::scrollCallback(double xOffset, double yOffset)
{
	std::cout << "Offsets = " << xOffset << " : " << yOffset << std::endl;
}

//a custrom cursor function
void pInputManager::creCursor(GLFWwindow *window, GLFWimage img, int xHot, int yHot)
{
	GLFWcursor *cursor = glfwCreateCursor(&img, xHot, yHot);
	glfwSetCursor(window, cursor);
}

//returns 0 if no controllers plugged in and return a non 0 value if one or more is
void pInputManager::presentCheck(int present)
{
	std::cout << "Controller status = " << present << std::endl;
}

//this method shows us what controller axis are being moved about
void pInputManager::axisTest(const float * axis, GLFWwindow * window)
{
	std::cout << "Left Stick X Axis" << axis[0] << std::endl;
	std::cout << "Left Stick Y Axis" << axis[1] << std::endl;
	std::cout << "Right Stick X Axis" << axis[2] << std::endl;
	std::cout << "Right Stick Y Axis" << axis[3] << std::endl;
	std::cout << "Left Trigger L2 Push" << axis[4] << std::endl;
	std::cout << "Right Trigger R2 Push" << axis[5] << std::endl;
	//pInputManager* tempContainer = pInputManager::instance(window);
	//tempContainer->axisStruct_Register(getPressureUsed(axis, getAxisInput(axis)), tempContainer->getAxisInput(axis), axis, tempContainer);

	//	std::cout << "!" << std::endl;
}

void pInputManager::massPressureCheck(const float * axis, GLFWwindow * window)
{
	pInputManager* tempContainer = pInputManager::instance(window);
	for (int x = 0; tempContainer->axisRegistry.size() > x; x++)
	{
		if (tempContainer->axisRegistry.at(x).name == axisName::LS_X)
		{
			tempContainer->axisRegistry.at(x).pressureVal = axis[0];
		}
		if (tempContainer->axisRegistry.at(x).name == axisName::LS_Y)
		{
			tempContainer->axisRegistry.at(x).pressureVal = axis[1];
		}
		if (tempContainer->axisRegistry.at(x).name == axisName::RS_X)
		{
			tempContainer->axisRegistry.at(x).pressureVal = axis[2];
		}
		if (tempContainer->axisRegistry.at(x).name == axisName::RS_Y)
		{
			tempContainer->axisRegistry.at(x).pressureVal = axis[3];
		}
		if (tempContainer->axisRegistry.at(x).name == axisName::L2)
		{
			tempContainer->axisRegistry.at(x).pressureVal = axis[4];
		}
		if (tempContainer->axisRegistry.at(x).name == axisName::R2)
		{
			tempContainer->axisRegistry.at(x).pressureVal = axis[5];
		}
	}
}

//controll the controllers buttons
void pInputManager::buttonControlls(const unsigned char * buttons, GLFWwindow * window)
{
	double time = glfwGetTime();
	pInputManager* tempContainer = pInputManager::instance(window);
	tempContainer->btnStruct_Register(time, true, tempContainer->getButtonsPressed(buttons), buttons, tempContainer);
}

//display a relavant name of the controller
void pInputManager::getControllerName(const char * name, int num)
{
	std::cout << "Controller " << num << " is named : " << name << std::endl;
}

void pInputManager::massButtonCheck(const unsigned char * buttons, GLFWwindow * window)
{
	pInputManager* tempContainer = pInputManager::instance(window);
	for (int x = 0; tempContainer->btnRegistry.size() > x; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			if (buttons[y] == GLFW_PRESS)
			{
				buttonName tempName = getButtonByArrayVal(buttons, y);
				tempContainer->btnStruct_Register(tempContainer->btnRegistry.at(x).timeHeld, true, tempName, buttons, tempContainer);
			}
			else if (buttons[y] != GLFW_PRESS)
			{
				buttonName tempName = getButtonByArrayVal(buttons, y);
				tempContainer->btnStruct_Register(tempContainer->btnRegistry.at(x).timeHeld, false, tempName, buttons, tempContainer);
			}
		}
	}
}

void pInputManager::btnStruct_Register(double timeHld, bool curDown, buttonName bName, const unsigned char * buttons, pInputManager * pInstance)
{
	btnStruct sBTN; //create a empty btnStructure
					//loop through the registered buttons
	for (int x = 0; x < btnRegistry.size(); ++x)
	{
		if (btnRegistry.at(x).name == bName)
		{
			if (curDown)
			{
				btnRegistry.at(x).commandHeld = true;
			}
			else if (!curDown)
			{
				btnRegistry.at(x).commandHeld = false; //if this btn is not held then set false
				btnRegistry.at(x).timeHeld = 0; //if im not being pressed update timer to 0
				btnRegistry.at(x).pThisFrame = false;
			}
			return;
		}
	}
	if (sBTN.name == buttonName::BTN_UNKNOWN)
	{
		if (curDown)
		{
			sBTN = btnStruct(0, true, static_cast<buttonName>(bName), true);//create real button
																			//std::cout << "IM Created as PRESSED" << std::endl;
			pInstance->btnRegistry.push_back(sBTN);//push button to buttonRegistry
		}
		if (!curDown)
		{
			sBTN = btnStruct(0, false, static_cast<buttonName>(bName), false);//create real button
																			  //std::cout << "IM Created as RELEASED" << std::endl;
			pInstance->btnRegistry.push_back(sBTN);//push button to buttonRegistry
		}
	}
}

buttonName pInputManager::getButtonsPressed(const unsigned char * buttons)
{
	if (GLFW_PRESS == buttons[0])
	{
		return buttonName::BTN_A;
	}

	else if (GLFW_PRESS == buttons[1])
	{
		return buttonName::BTN_B;
	}
	else if (GLFW_PRESS == buttons[2])
	{
		return buttonName::BTN_X;
	}

	else if (GLFW_PRESS == buttons[3])
	{
		return buttonName::BTN_Y;
	}

	else if (GLFW_PRESS == buttons[4])
	{
		return buttonName::BTN_LB;
	}

	else if (GLFW_PRESS == buttons[5])
	{
		return buttonName::BTN_RB;
	}

	else if (GLFW_PRESS == buttons[6])
	{
		return buttonName::BTN_BACK;
	}

	else if (GLFW_PRESS == buttons[7])
	{
		return buttonName::BTN_START;
	}

	else if (GLFW_PRESS == buttons[8])
	{
		return buttonName::BTN_LTSD;
	}

	else if (GLFW_PRESS == buttons[9])
	{
		return buttonName::BTN_RTSD;
	}

	else if (GLFW_PRESS == buttons[10])
	{
		return buttonName::BTN_UP;
	}

	else if (GLFW_PRESS == buttons[11])
	{
		return buttonName::BTN_RIGHT;
	}

	else if (GLFW_PRESS == buttons[12])
	{
		return buttonName::BTN_DOWN;
	}

	else if (GLFW_PRESS == buttons[13])
	{
		return buttonName::BTN_LEFT;
	}
	else
	{
		return buttonName::BTN_UNKNOWN;
	}
}

buttonName pInputManager::getButtonByArrayVal(const unsigned char *buttons, int btnVal)
{
	if (btnVal == 0)
	{
		return buttonName::BTN_A;
	}
	else if (btnVal == 1)
	{
		return buttonName::BTN_B;
	}
	else if (btnVal == 2)
	{
		return buttonName::BTN_X;
	}

	else if (btnVal == 3)
	{
		return buttonName::BTN_Y;
	}

	else if (btnVal == 4)
	{
		return buttonName::BTN_LB;
	}

	else if (btnVal == 5)
	{
		return buttonName::BTN_RB;
	}

	else if (btnVal == 6)
	{
		return buttonName::BTN_BACK;
	}

	else if (btnVal == 7)
	{
		return buttonName::BTN_START;
	}

	else if (btnVal == 8)
	{
		return buttonName::BTN_LTSD;
	}

	else if (btnVal == 9)
	{
		return buttonName::BTN_RTSD;
	}

	else if (btnVal == 10)
	{
		return buttonName::BTN_UP;
	}

	else if (btnVal == 11)
	{
		return buttonName::BTN_RIGHT;
	}

	else if (btnVal == 12)
	{
		return buttonName::BTN_DOWN;
	}

	else if (btnVal == 13)
	{
		return buttonName::BTN_LEFT;
	}
	else
	{
		return buttonName::BTN_UNKNOWN;
	}
}

axisName pInputManager::getAxisInput(const float * axis)
{
	if (GLFW_PRESS == axis[0])
	{
		return axisName::LS_X;
	}
	else if (GLFW_PRESS == axis[1])
	{
		return axisName::LS_Y;
	}
	else if (GLFW_PRESS == axis[2])
	{
		return axisName::RS_X;
	}
	else if (GLFW_PRESS == axis[3])
	{
		return axisName::RS_Y;
	}
	else if (GLFW_PRESS == axis[4])
	{
		return axisName::L2;
	}
	else if (GLFW_PRESS == axis[5])
	{
		return axisName::R2;
	}
	return axisName::AXIS_UNKNOWN;
}

float pInputManager::getPressureUsed(const float * axis, axisName aName)
{
	if (aName == axisName::LS_X)
	{
		return axis[0];
	}
	else if (aName == axisName::LS_Y)
	{
		return axis[1];
	}
	else if (aName == axisName::RS_X)
	{
		return axis[2];
	}
	else if (aName == axisName::RS_Y)
	{
		return axis[3];
	}
	else if (aName == axisName::L2)
	{
		return axis[4];
	}
	else if (aName == axisName::R2)
	{
		return axis[5];
	}
	else if (aName == axisName::AXIS_UNKNOWN)
	{
		return 0.0f;
	}
}

void pInputManager::axisStruct_Register(pInputManager * pInstance)
{
	std::vector<axisStruct> tempRegistry = pInstance->axisRegistry;

	axisStruct sAxis; //create a empty axisStructure
					  //loop through the registered ax'i

	if (axisRegistry.size() == NULL)
	{
		//first time set up
		sAxis = axisStruct(0, false, axisName::AXIS_UNKNOWN);
		std::cout << "IM Created as DEAD" << std::endl;
		pInstance->axisRegistry.push_back(sAxis);//push button to buttonRegistry

		sAxis = axisStruct(0, false, axisName::LS_X);
		std::cout << "IM Created as DEAD" << std::endl;
		pInstance->axisRegistry.push_back(sAxis);//push button to buttonRegistry

		sAxis = axisStruct(0, false, axisName::LS_Y);
		std::cout << "IM Created as DEAD" << std::endl;
		pInstance->axisRegistry.push_back(sAxis);//push button to buttonRegistry

		sAxis = axisStruct(0, false, axisName::RS_X);
		std::cout << "IM Created as DEAD" << std::endl;
		pInstance->axisRegistry.push_back(sAxis);//push button to buttonRegistry

		sAxis = axisStruct(0, false, axisName::RS_Y);
		std::cout << "IM Created as DEAD" << std::endl;
		pInstance->axisRegistry.push_back(sAxis);//push button to buttonRegistry

		sAxis = axisStruct(0, false, axisName::L2);
		std::cout << "IM Created as DEAD" << std::endl;
		pInstance->axisRegistry.push_back(sAxis);//push button to buttonRegistry

		sAxis = axisStruct(0, false, axisName::R2);
		std::cout << "IM Created as DEAD" << std::endl;
		pInstance->axisRegistry.push_back(sAxis);//push button to buttonRegistry

												 //if this triggers leave this method
		return;
	}
}

bool pInputManager::hasBtnBeenPressed(buttonName bName)
{
	//loop through the register
	for (int i = 0; i < btnRegistry.size(); i++)
	{
		if (btnRegistry[i].name == bName) //if the name is what we want
		{
			if (btnRegistry[i].commandHeld == true) //if the command is held
			{
				return true;
			}
			else
			{
				btnRegistry[i].timeHeld = 0;
				return false; //if they key is not down return false
			}
		}
	}
	return false; //if no key has been delt with return false
}

bool pInputManager::hasBtnBeenChecked(buttonName bName)
{
	//loop through the register
	for (int i = 0; i < btnRegistry.size(); i++)
	{
		if (btnRegistry[i].name == bName) //if the name is what we want
		{
			if (btnRegistry[i].pThisFrame == true) //if the key has not been delt with
			{
				btnRegistry[i].pThisFrame = false; //deal with key
				return true; //return true if key has been delt with
			}
		}
	}
	return false; //if no key has been delt with return false
}

float pInputManager::returnPressure(axisName aName)
{
	//loop through the register
	for (int i = 0; i < axisRegistry.size(); i++)
	{
		if (axisRegistry[i].name == aName) //if the name is what we want
		{
			return axisRegistry[i].pressureVal;
		}
	}
	return 0.0f;
}

//total time elapsed
void pInputManager::timeSenceInit(double time)
{
	std::cout << time << std::endl;
}

//set add to the current time
void pInputManager::modTime(double time, double mod)
{
	double varTime = time + mod;
	glfwSetTime(varTime);
}

//print what is in your cliptray
void pInputManager::paste(const char * text)
{
	std::cout << text << std::endl;
}

//set the clip of the clipboardtray to a character array
void pInputManager::setText(char txt[], GLFWwindow *window)
{
	glfwSetClipboardString(window, txt);
}