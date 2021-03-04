#include "pcpch.h"

#include <PencilEngine/log.h>

#include <GLFW/glfw3.h>
#include "windowsWindow.h"

#include <PencilEngine/events/applicationEvent.h>
#include <PencilEngine/events/mouseEvent.h>
#include <PencilEngine/events/keyEvent.h>

namespace pencil
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char *description)
	{
		PC_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window *Window::create(const WindowProps &props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps &props)
	{
		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{

	}

	void WindowsWindow::init(const WindowProps &props)
	{
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		PC_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();

			PC_CORE_ASSERT(success, "Unable to inisialize GLFW");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow(props.width, props.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

		// Set GLFW window callback functions
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height)
		{
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
			WindowResizeEvent event(width, height);
			data.width = width;
			data.height = height;
			data.eventCallback(event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window)
		{
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods)
		{
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOff, double yOff)
		{
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float) xOff, (float) yOff);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double x, double y)
		{
			WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float) x, (float) y);
			data.eventCallback(event);
		});
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = enabled;
	}

	bool WindowsWindow::isVSync() const
	{
		return m_data.VSync;
	}
}
