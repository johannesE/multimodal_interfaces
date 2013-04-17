#include "PhidgetManager.h"
#include <stdio.h>		
#include <phidget21.h>	
#include <stdlib.h> 


//Declare an InterfaceKit handle
CPhidgetInterfaceKitHandle ifKit = 0;

int SensorChangeTrigger = 10;


PhidgetManager::PhidgetManager()
{
}


PhidgetManager::~PhidgetManager(void)
{
	close();
}



int CCONV AttachHandler(CPhidgetHandle IFK, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName(IFK, &name);
	CPhidget_getSerialNumber(IFK, &serialNo);

	printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int CCONV DetachHandler(CPhidgetHandle IFK, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (IFK, &name);
	CPhidget_getSerialNumber(IFK, &serialNo);

	printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int CCONV ErrorHandler(CPhidgetHandle IFK, void *userptr, int ErrorCode, const char *unknown)
{
	printf("Error handled. %d - %s", ErrorCode, unknown);
	return 0;
}

//callback that will run if an input changes.
//Index - Index of the input that generated the event, State - boolean (0 or 1) representing the input state (on or off)
int CCONV InputChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int State)
{
	printf("Digital Input: %d > State: %d\n", Index, State);
	
	return 0;
}

//callback that will run if an output changes.
//Index - Index of the output that generated the event, State - boolean (0 or 1) representing the output state (on or off)
int CCONV OutputChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int State)
{
	printf("Digital Output: %d > State: %d\n", Index, State);
	return 0;
}


//TODO: un callback pour chaque Phidget, comme ça c'est plus rapide et ça n'interfère pas
//--------------------------------------------------------------------------------------


//callback that will run if the sensor value changes by more than the OnSensorChange trigger.
//Index - Index of the sensor that generated the event, Value - the sensor read value
int CCONV SensorChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int Value)
{
	//printf("Sensor: %d > Value: %d\n", Index, Value);
	switch(Index)
	{
		case 0:
			 //SuperBall::update_aX(Value, 500, 10000.0f, 50.0f);
			 SuperBall::update_vX(Value);
			 break;
		case 1:
			 //SuperBall::update_aY(Value, 500, 10000.0f, 50.0f);
			 SuperBall::update_vY(Value);
			 break;
		case 2:
			 SuperBall::updateRadius(Value);
			 break;
		 
	}
	return 0;
}

int CCONV SensorChangeHandlerPhidget0(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int Value)
{

	//printf("Sensor: %d > Value: %d\n", Index, Value);

	SuperBall::update_vX(Value);
	return 0;
}

int CCONV SensorChangeHandlerPhidget1(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int Value)
{
	//printf("Sensor: %d > Value: %d\n", Index, Value);


	SuperBall::update_vY(Value);
	return 0;
}

int CCONV SensorChangeHandlerPhidget2(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int Value)
{
	//printf("Sensor: %d > Value: %d\n", Index, Value);
	SuperBall::updateRadius(Value);
	return 0;
}

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
//Will also display the number of inputs, outputs, and analog inputs on the interface kit as well as the state of the ratiometric flag
//and the current analog sensor sensitivity.
int display_properties(CPhidgetInterfaceKitHandle phid)
{
	int serialNo, version, numInputs, numOutputs, numSensors, triggerVal, ratiometric, i;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetInterfaceKit_getInputCount(phid, &numInputs);
	CPhidgetInterfaceKit_getOutputCount(phid, &numOutputs);
	CPhidgetInterfaceKit_getSensorCount(phid, &numSensors);
	CPhidgetInterfaceKit_getRatiometric(phid, &ratiometric);

	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
	printf("# Digital Inputs: %d\n# Digital Outputs: %d\n", numInputs, numOutputs);
	printf("# Sensors: %d\n", numSensors);
	printf("Ratiometric: %d\n", ratiometric);

	for(i = 0; i < numSensors; i++)
	{
		CPhidgetInterfaceKit_getSensorChangeTrigger (phid, i, &triggerVal);

		printf("Sensor#: %d > Sensitivity Trigger: %d\n", i, triggerVal);
	}

	return 0;
}

void PhidgetManager::close()
{
	CPhidget_close((CPhidgetHandle)ifKit);
	CPhidget_delete((CPhidgetHandle)ifKit);
}


void PhidgetManager::start()
{
	int result, numSensors, i;
	const char *err;


	//create the InterfaceKit object
	CPhidgetInterfaceKit_create(&ifKit);

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)ifKit, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)ifKit, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)ifKit, ErrorHandler, NULL);

	//Registers a callback that will run if an input changes.
	//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetInterfaceKit_set_OnInputChange_Handler (ifKit, InputChangeHandler, NULL);

	//Registers a callback that will run if the sensor value changes by more than the OnSensorChange trig-ger.
	//Requires the handle for the IntefaceKit, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetInterfaceKit_set_OnSensorChange_Handler (ifKit, SensorChangeHandler, NULL);

	//Registers a callback that will run if an output changes.
	//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetInterfaceKit_set_OnOutputChange_Handler (ifKit, OutputChangeHandler, NULL);

	//open the interfacekit for device connections
	CPhidget_open((CPhidgetHandle)ifKit, -1);

	//get the program to wait for an interface kit device to be attached
	printf("Waiting for the Phidgets interface kit to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)ifKit, 6000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("\nProblem waiting for attachment: %s\n", err);

		printf("\nMove the SuperBall with the the keys a,d,w,s.\n\n");
		printf("Press enter to continue\n");
		getchar();
		//exit(0);
		close();
		return;
	}

	//Display the properties of the attached interface kit device
	display_properties(ifKit);

	//read interface kit event data
	printf("Reading.....\n");

	//keep displaying interface kit data until user input is read
	//printf("Press any key to go to next step\n");
	//getchar();

	printf("Modifying sensor sensitivity triggers....\n");

	//get the number of sensors available
	CPhidgetInterfaceKit_getSensorCount(ifKit, &numSensors);

	//Change the sensitivity trigger of the sensors
	for(i = 0; i < numSensors; i++)
	{
		CPhidgetInterfaceKit_setSensorChangeTrigger(ifKit, i, SensorChangeTrigger);  //we'll just use 10 for fun
	}

	CPhidgetInterfaceKit_setSensorChangeTrigger(ifKit, 0, SensorChangeTrigger);
	CPhidgetInterfaceKit_setSensorChangeTrigger(ifKit, 1, SensorChangeTrigger);

	//read interface kit event data
	printf("Reading.....\n");

	//keep displaying interface kit data until user input is read
	//printf("Press any key to go to next step\n");
	//getchar();

	//printf("Toggling Ratiometric....\n");

	//CPhidgetInterfaceKit_setRatiometric(ifKit, 0);

	//read interface kit event data
	//printf("Reading.....\n");

	//keep displaying interface kit data until user input is read
	//printf("Press any key to continue\n");
	//getchar();
}

