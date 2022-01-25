#include "Application.h"

int main()
{
	Application app;
	app.Initialise();
	
	// Here for completeness but doesn't do
	// anything due of whileloop in Application
	app.Shutdown();

	return 0;
}