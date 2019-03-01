// Gaze.cpp : This file contains the 'main' function. Program execution begins and ends there.
// all .cpp files must

#include "pch.h"
#include "Listener.h"
#include <iostream>

using namespace std;

int main()
{
	// Start logger and listener
	Logger logger;
	Listener listener(&logger);

	cout << Utilities::GetCurrentDate() << endl;
	cout << Utilities::GetTime() << endl;
	cout << Utilities::GetActiveWindow() << endl;
	cout << Utilities::GetProgramFilePath() << endl;
	cout << Utilities::GetSystemDir() << endl;
	
	// If available load log from file and display it to screen 
	if(logger.LoadMapFromFile());
		cout << logger.GetLog() << endl;

	// Start listening
	listener.Start();

	// If F1 pressed
	cout << "EXITING!" << endl;

	// Save log to file
	logger.SaveMapToFile();

	return 0;
}