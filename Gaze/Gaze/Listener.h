#pragma once

#include "Logger.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Listener
{
	bool Listening;
	Logger* Log;
	Clock Timer;

public:
	// Listener(Logger*) : Class cunstructor
	Listener(Logger* logger);

	// Start() : Start listening
	void Start();

	// Stop() : Stop listening
	void Stop();

	// IsListening() : Return Listener status (Listening attribut)
	bool IsListening() const;

private:
	// Run() : Listener main loop
	void Run();

};