#include <pcpch.h>
#include <PencilEngine/application.h>

#include <PencilEngine/log.h>

#include <glad/glad.h>

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace pencil
{

	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	Application::~Application()
	{
	}

	void Application::pushLayer(Layer *layer)
	{
		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer *layer)
	{
		m_layerStack.pushOverlay(layer);
	}

	void Application::onEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::run()
	{
		while (m_running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer *layer : m_layerStack)
				layer->onUpdate();

			m_window->onUpdate();
		}
	}
	
	bool Application::onWindowClose(WindowCloseEvent &e)
	{
		m_running = false;

		return true;
	}
}
