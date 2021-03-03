#pragma once

#include "core.h"

namespace pencil
{
	class PENCIL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// To be defined in client
	Application *createApplication();
}
