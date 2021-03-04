#include <pencil.h>

class ExampleLayer : public pencil::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void onUpdate() override
	{
		PC_INFO("ExampleLayer::update");
	}

	void onEvent(pencil::Event &event) override
	{
		PC_TRACE("{0}", event);
	}
};

class Sandbox : public pencil::Application
{
public:
	Sandbox()
	{
		pushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

pencil::Application *pencil::createApplication()
{
	return new Sandbox();
}
