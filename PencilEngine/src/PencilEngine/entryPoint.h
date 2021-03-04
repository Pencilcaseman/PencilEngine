#pragma once

#include <pcpch.h>

#ifdef PC_PLATFORM_WINDOWS

extern pencil::Application *pencil::createApplication();

int main(int argc, char **argv)
{
	pencil::Log::init();
	PC_CORE_WARN("Initialized Log!");
	PC_INFO("Hello! Var={0}", 123);

	auto app = pencil::createApplication();
	app->run();
	delete app;

	return 0;
}

#endif
