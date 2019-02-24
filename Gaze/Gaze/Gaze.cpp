// Gaze.cpp : This file contains the 'main' function. Program execution begins and ends there.
// all .cpp files must

#include "pch.h"
#include "Utilities.h"
#include <iostream>

using namespace std;

int main()
{
	cout << Utilities::GetMachineName() << endl;
	cout << Utilities::GetUsername() << endl;
    cout << Utilities::GetProgramFilePath() << endl;
	cout << Utilities::GetSystemDir() << endl;
	//tool.HideConsole();

	return 0;
}