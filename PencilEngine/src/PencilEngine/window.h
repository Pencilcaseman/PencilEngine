#pragma once

#include <pcpch.h>

#include <PencilEngine/core.h>
#include <PencilEngine/events/event.h>

namespace pencil
{
	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string &winTitle = "PencilEngine",
					unsigned int winWidth = 1280,
					unsigned int winHeight = 720)
			: title(winTitle), width(winWidth), height(winHeight)
		{}
	};

	// Interface representing a desktop system based window
	class PENCIL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event &)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// Attributes
		virtual void setEventCallback(const EventCallbackFn &callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Window *create(const WindowProps &props = WindowProps());
	};
}
