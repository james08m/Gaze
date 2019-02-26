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
	// Listener() : Class cunstructor
	Listener();

	// Start() : Start listening
	void Start();

	// Stop() : Stop listening
	void Stop();

private:
	// Run() : Listener main loop
	void Run();

};