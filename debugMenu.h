#pragma once
#include "SDL.h"
#include <iostream>
#include "../SceneManager.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

namespace duckTape {
	constexpr int EVENT_PEEK_SIZE = 20;
	class Window;
	class debugMenu {
		friend class Window;
	public:
		debugMenu(std::uint32_t* deltaTime, SDL_Window* win);
		void eventProcess();
		void logic();
		void render();
		~debugMenu();
	private:
		bool isEnabled;
		std::uint32_t* deltaTime;
		SDL_Event* events;
		Window** windows;
		static const int num_windows;
		
	};
}