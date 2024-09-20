#include "debugMenu.h"
#include "frameMonitor.h"
#include "ObjectMonitor.h"

const int duckTape::debugMenu::num_windows = 2;
duckTape::debugMenu::debugMenu(std::uint32_t* deltaTime, SDL_Window* win)
{
	this->deltaTime = deltaTime;
	
	this->isEnabled = false;
	
	
	this->windows =  new Window*[num_windows]
		{ new frameMonitor(this,"frame monitor:"), new objectMonitor(this, "Object Monitor select") };
	
	
	events = new SDL_Event[EVENT_PEEK_SIZE];
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(win, getSceneManager.getActiveScene()->scene_RENDERER);
	ImGui_ImplSDLRenderer2_Init(getSceneManager.getActiveScene()->scene_RENDERER);
    
}


void duckTape::debugMenu::eventProcess() {
	ImGuiIO& io = ImGui::GetIO();
	int mouseX, mouseY;
	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
	io.DeltaTime = *deltaTime / 1000.0;
	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	int numEvents = SDL_PeepEvents(events, EVENT_PEEK_SIZE, 
		SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
	for (int i = 0; i < numEvents; i++) {
		SDL_Event* e = &events[i];
		if (e->type == SDL_KEYUP && e->key.keysym.scancode == SDL_SCANCODE_F2) {
			isEnabled = !isEnabled;
			std::cout << "changed" << std::endl;
		}
		ImGui_ImplSDL2_ProcessEvent(e);
	}
}

void duckTape::debugMenu::logic() {
	for (int i = 0; i < num_windows; i++) {
		windows[i]->logic();
	}
}

void duckTape::debugMenu::render() {
	if (isEnabled) {
		static char out[5];
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		for (int i = 0; i < num_windows; i++) {
			
			windows[i]->render();
			
		}
		
		ImGui::Begin("DuckTape Debugger", &isEnabled);
		for (int i = 0; i < num_windows; i++) {
			ImGui::Checkbox(windows[i]->selectTitle.c_str(), 
				&(windows[i]->isEnabled));
		}
		ImGui::End();

		

		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), 
			getSceneManager.getActiveScene()->scene_RENDERER);
	}
}

duckTape::debugMenu::~debugMenu()
{
	for (int i = 0; i < num_windows; i++) {
		delete windows[i];
	}
	windows = NULL;
}
