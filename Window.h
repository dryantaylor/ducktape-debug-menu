#pragma once
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "debugMenu.h"

namespace duckTape {
	class Window {
	public:
		Window(debugMenu* menu, std::string select);
		virtual void logic(void) = 0;
		virtual void render(void) = 0;
		virtual ~Window() {};
		

		std::string selectTitle;
		bool isEnabled;
	protected:
		std::uint32_t* getdeltaTimePtr() { return menu->deltaTime; };
		//find way to get current physics tick
		std::uint32_t* getPhysicsTickPtr() { return 0; }
		debugMenu* menu;
	};
}