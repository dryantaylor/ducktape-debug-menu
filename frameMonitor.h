#pragma once
#include "Window.h"
#include <cstdint>
#include <deque>

namespace duckTape {
	
	class frameMonitor : public Window {
	public:
		
		frameMonitor(debugMenu* menu, std::string select);
		void logic() override;
		void render() override;
		~frameMonitor() override;

	private:

		bool constFTenabled;
		std::uint32_t constFTvalue;
		std::uint32_t FTtick;
		bool monitoringEnabled;
		std::uint32_t monitoringTick;
		std::uint32_t monitoringInterval;
		float* monitoringValues;
		int writeIndex;
	};
}