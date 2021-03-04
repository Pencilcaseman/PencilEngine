#pragma once

#include <pcpch.h>

#include <PencilEngine/core.h>
#include <PencilEngine/layerStack.h>
#include <PencilEngine/events/event.h>
#include <PencilEngine/events/applicationEvent.h>
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

		void pushLayer(Layer *layer);
		void pushOverlay(Layer *layer);
	private:
		bool onWindowClose(WindowCloseEvent &e);

		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layerStack;
	};

	// To be defined in client
	Application *createApplication();
}
