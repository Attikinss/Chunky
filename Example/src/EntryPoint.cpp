#include "Application.h"

int main()
{
	Application app;
	app.Initialise();
	app.Run();
	app.Shutdown();

	return 0;
}