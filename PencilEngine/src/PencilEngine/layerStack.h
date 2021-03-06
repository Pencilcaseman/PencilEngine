#pragma once

#include <PencilEngine/core.h>
#include "layer.h"

namespace pencil
{
	class PENCIL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer *layer);
		void pushOverlay(Layer *layer);
		void popLayer(Layer *layer);
		void popOverlay(Layer *layer);

		std::vector<Layer *>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer *>::iterator end() { return m_layers.end(); }

	private:
		std::vector<Layer *> m_layers;
		std::vector<Layer *>::iterator m_layerInsert;
	};
}
