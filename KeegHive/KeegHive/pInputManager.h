#pragma once
//#include <GLFW/glfw3.h>
#include "iostream"
#include <vector>
//#include "pEnums.h"
#include "pInputHandler.h"
#include "enums.h"

//here is a key
struct keyStruct
{
	keyName name; //whats the name of this key
	double pressTime; //how long has this been pressed for
	bool currentlyDown; //is this pressed or realeaced
	bool keyHeld; //has this been pressed for atleast two blips
	bool pThisFrame; //has this keys press been responded to

					 //default constructor
	keyStruct()
	{
		name = KEY_UNKNOWN;
		pressTime = 0;
		currentlyDown = false;
		keyHeld = false;
		pThisFrame = false;
	}

	//advanced consructor
	keyStruct(double lastPressed, bool UpOrDown, bool boolHeld, bool pressedThisFrame, keyName kname)
	{
		pressTime = lastPressed; //how long has this been pressed for
		currentlyDown = UpOrDown; //is this pressed or realeaced
		keyHeld = boolHeld; //has this been pressed for atleast two blips
		name = kname; //whats the name of this key
		pThisFrame = pressedThisFrame; //has this keys press been responded to
	}
};

struct clickStruct
{
	clickName name;
	double pressTime;
	bool upOrDown;
	bool clickHeld;
	bool cThisFrame;

	clickStruct()
	{
		name = UNKNOWNMOUSE;
		pressTime = 0;
		upOrDown = false;
		clickHeld = false;
		cThisFrame = false;
	}

	clickStruct(double timePressed, bool currentlyDown, bool boolHeld, bool clickedThisFrame, clickName cName)
	{
		name = cName;
		pressTime = timePressed;
		upOrDown = currentlyDown;
		clickHeld = boolHeld;
		cThisFrame = clickedThisFrame;
	}
};


struct btnStruct
{
	buttonName name;
	bool commandHeld;
	double timeHeld;
	bool pThisFrame;

	btnStruct()
	{
		name = BTN_UNKNOWN;
		commandHeld = false;
		timeHeld = 0;
		pThisFrame = false;
	}

	btnStruct(double timeHld, bool curDown, buttonName bName, bool pressedThisFrame)
	{
		name = bName;
		commandHeld = curDown;
		timeHeld = timeHld;
		pThisFrame = pressedThisFrame;
	}
};

struct axisStruct
{
	axisName name;
	bool isAlive;
	float pressureVal;

	axisStruct()
	{
		name = AXIS_UNKNOWN;
		isAlive = false;
		pressureVal = NULL;
	}
	axisStruct(float pressure, bool amAlive, axisName aName)
	{
		name = aName;
		isAlive = amAlive;
		pressureVal = pressure;
	}
};

class pInputManager
{
private:
	//singleton accessor + private con/destructor
	static pInputManager* _instance;
	pInputManager(GLFWwindow *w);
	~pInputManager();

public:
	void Initialize(GLFWwindow* window, pInputHandler* inputHandler);
	//objects used to store or access information
	static pInputManager* instance(GLFWwindow* w);
	std::vector<keyStruct> keyRegistry;
	std::vector<clickStruct> clickRegistry;
	std::vector<btnStruct> btnRegistry = std::vector<btnStruct>();
	std::vector<axisStruct> axisRegistry = std::vector<axisStruct>();

	//keyboard methods
	static void error_callback(int error, const char* description);

	//keyboard methods that are advanced / todo with the keyRegistry
	static void advancedKey_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	void keyStruct_Register(double pressTime, bool keyLastPressed, bool iChecked, keyName sName, pInputManager* pInstance, int state);
	void inputUpdate(double deltaTime); //this is used in all the keyboard, mouse and controller button / axis handling functions
	bool hasKeyBeenChecked(keyName name);
	bool hasKeyBeenRepeated(keyName name);
	bool hasKeyBeenPressed(keyName name);

	//for somereason this is missing methods, deal with this later
	static void advancedClick_callback(GLFWwindow *window, int button, int action, int mods);
	void clickStruct_Register(double pressTime, bool currentlyDown, bool boolHeld, bool clickedThisFrame, clickName cName, pInputManager* pInstance, int state);
	bool hasClickBeenChecked(clickName name);
	bool hasClickBeenRepeated(clickName name);
	bool hasClickBeenPressed(clickName name);

	//mouse methods
	static void cursorPositionCallback(double xPosition, double yPosition);
	static void cursorEnterCallback(int enteredScreen);
	static void scrollCallback(double xOffset, double yOffset);
	static void creCursor(GLFWwindow *window, GLFWimage img, int xHot, int yHot);

	//controller methods
	static void presentCheck(int present);
	static void axisTest(const float *axis, GLFWwindow * window);
	static void massPressureCheck(const float *axis, GLFWwindow * window);
	static void buttonControlls(const unsigned char *buttons, GLFWwindow * window);
	static void getControllerName(const char *name, int num);
	static void massButtonCheck(const unsigned char *buttons, GLFWwindow * window);
	void btnStruct_Register(double timeHld, bool curDown, buttonName bName, const unsigned char * buttons, pInputManager* pInstance);
	static buttonName getButtonsPressed(const unsigned char *buttons);
	static buttonName getButtonByArrayVal(const unsigned char *buttons, int btnVal);
	static axisName getAxisInput(const float *axis);
	static float getPressureUsed(const float *axis, axisName aName);
	void axisStruct_Register(pInputManager* pInstance);
	bool hasBtnBeenPressed(buttonName bName);
	bool hasBtnBeenChecked(buttonName bName);
	float returnPressure(axisName aName);

	//time methods
	static void timeSenceInit(double time);
	static void modTime(double time, double mod);

	//Clipboard method
	static void paste(const char *text);
	static void setText(char txt[], GLFWwindow *window);
};