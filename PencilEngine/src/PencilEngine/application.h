#pragma once

#include <pcpch.h>

#include <PencilEngine/core.h>
#include <PencilEngine/events/event.h>
#include <PencilEngine/events/applicationEvent.h>
#include <PencilEngine/events/keyEvent.h>
#include <PencilEngine/events/mouseEvent.h>
#include <PencilEngine/window.h>

namespace pencil
{
	class PENCIL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event &e);
	private:
		bool onWindowClose(WindowCloseEvent &e);

		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};

	// To be defined in client
	Application *createApplication();
}
