#include "Core/Application.h"

int main()
{
	Application* app = new Application(WindowProps("NES Emulator"));
	app->Run();

	delete app;
}