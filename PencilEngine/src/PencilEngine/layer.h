#pragma once

#include <PencilEngine/core.h>
#include <PencilEngine/events/event.h>

namespace pencil
{
	class PENCIL_API Layer
	{
	public:
		Layer(const std::string &name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event &event) {}

		inline const std::string getName() const { return m_debugName; }

	protected:
		std::string m_debugName;
	};
}
