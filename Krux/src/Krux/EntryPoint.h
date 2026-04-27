#pragma once

#include "Application.h"
#include "Log.h"

extern Krux::Application* Krux::Create();

int main() {
	Krux::Log::Init();

	Krux::Application* app = Krux::Create();
	app->Run();
	delete app;
}