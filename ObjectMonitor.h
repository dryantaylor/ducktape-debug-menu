#pragma once
#include "Window.h"
#include <cstdint>
#include <deque>
#include "../ComponentDataWrapper.h"

namespace duckTape {
	class objectMonitor : public Window {
	public:

		objectMonitor(debugMenu* menu, std::string select);
		void logic() override;
		void render() override;

	private:
		
	};
}