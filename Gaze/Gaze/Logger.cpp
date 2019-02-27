#include "pch.h"
#include "Logger.h"


// Insert(string, string) : Insert into map the key stroke on the window
void Logger::Insert(string window_name, string key_input)
{
	this->_Log[window_name] += key_input;
	cout << window_name << " : " << this->_Log[window_name] << endl;
}

// Insert(string, int) : Insert into map the key stroke on the window
void Logger::Insert(string window_name, int key_input)
{
	this->_Log[window_name] += key_input;
	cout << window_name << " : " << this->_Log[window_name] << endl;
}


// Add(string, int) : Add key stroke and the window name to Logger
void Logger::Add(string window_name, int key_stroke)
{
	// Check if key stroke is mapped if not map_key == "" 
	string map_key = _Keys.Map[key_stroke];

	// If key is not mapped
	if (map_key == "")
	{
		if(key_stroke == key_stroke == 190 || key_stroke == 110)
		{
			this->Insert(window_name, "."); // Not working
		}
		else
		{
			this->Insert(window_name, key_stroke);
		}
	}
	else
	{		
		this->Insert(window_name, map_key);
	}
}

// GetLog(string) : Return the key log for a specific window
string Logger::GetLog(string window_name) 
{
	return this->_Log.find(window_name)->second;
}

// GetLog(string) : Return all the key log for all window
string Logger::GetLog()
{
	string log = "";

	// Go through all the log
	for (map<string, string>::iterator iter = _Log.begin(); iter != _Log.end(); ++iter)
	{
		log += iter->first + " > " + iter->second;
	}

	return log;
}

// SaveMapToFile(string) : Save Map content to file
void Logger::SaveMapToFile(string path)
{
	// Initiate file stream and map iterator
	ofstream file(path);
	map<string, string>::iterator iter;

	// Go through all map log and write it to file
	for (iter = _Log.begin(); iter != _Log.end(); ++iter)
	{
		file << iter->first << endl;
		file << iter->second << endl;
	}

	// Close file
	file.close();
}

// LoadMapFromFile(string) : Load file content to map
bool Logger::LoadMapFromFile(string path)
{
	ifstream file(path);

	// Make sure file exist
	if (!file)
		return false; // Unable to open file
	else
	{
		string window_line;
		string log_line;

		while (getline(file, window_line))
		{
			getline(file, log_line);
			this->_Log[window_line] = log_line;
		}

		return true;
	}
}