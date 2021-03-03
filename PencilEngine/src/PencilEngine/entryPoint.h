#pragma once

#ifdef PC_PLATFORM_WINDOWS

extern pencil::Application *pencil::createApplication();

int main(int argc, char **argv)
{
	printf("Pencil Engine\n");
	auto app = pencil::createApplication();
	app->run();
	delete app;

	return 0;
}

#endif
