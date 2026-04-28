#pragma once

#include "Application.h"
#include "Log.h"

extern Krux::Application* Krux::CreateApplication();

int main() {
	Krux::Log::Init();

	Krux::Application* app = Krux::CreateApplication();
	app->Run();
	delete app;
}