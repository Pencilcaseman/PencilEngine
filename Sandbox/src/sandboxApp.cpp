#include <pencil.h>

class Sandbox : public pencil::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}


};

pencil::Application *pencil::createApplication()
{
	return new Sandbox();
}
