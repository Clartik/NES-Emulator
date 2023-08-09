#include "Emulator/Emulator.h"

int main()
{
	Emulator* app = new Emulator;
	app->Run();
	delete app;

	while (1);
}