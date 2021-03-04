#include <PencilEngine/application.h>
#include <PencilEngine/log.h>
#include <PencilEngine/Events/applicationEvent.h>

namespace pencil
{

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		WindowResizeEvent e(123, 456);
		if (e.isInCategory(EventCategoryApplication))
		{
		PC_TRACE(e);
		}
		else if (e.isInCategory(EventCategoryInput))
		{
			PC_TRACE(e);
		}

		while (true)
		{}
	}
}
