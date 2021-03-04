#pragma once

#include <pcpch.h>
#include <PencilEngine/window.h>
#include <GLFW/glfw3.h>

namespace pencil
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps &props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }

		// Attributes
		inline void setEventCallback(const EventCallbackFn &callback) override { m_data.eventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

	private:
		virtual void init(const WindowProps &props);
		virtual void shutdown();

	private:
		GLFWwindow *m_window;
		
		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool VSync;

			EventCallbackFn eventCallback;
		};

		WindowData m_data;
	};
}
