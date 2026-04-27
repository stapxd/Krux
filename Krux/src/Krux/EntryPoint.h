#pragma once

#include "Application.h"

extern Krux::Application* Krux::Create();

int main() {
	Krux::Application* app = Krux::Create();
	app->Run();
	delete app;
}