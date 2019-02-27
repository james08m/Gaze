// Gaze.cpp : This file contains the 'main' function. Program execution begins and ends there.
// all .cpp files must

#include "pch.h"
#include "Listener.h"
#include <iostream>

using namespace std;

int main()
{
	// Start logger and listener
	Logger logger("test.log");
	Listener listener(&logger);
	
	logger.LoadMapFromFile();

	cout << logger.GetLog() << endl;

	// Start listening
	listener.Start();

	cout << "EXITING!" << endl;

	logger.SaveMapToFile();

	//Utilities::HideConsole();
	return 0;
}