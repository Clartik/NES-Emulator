#include "Emulator/Emulator.h"

#include <iostream>

int main()
{
	Emulator* app = new Emulator;
	app->Run();
	std::cin.get();
	delete app;
}