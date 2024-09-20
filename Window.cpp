#include "Window.h"

duckTape::Window::Window(debugMenu* menu, std::string select)
{
	isEnabled = false;
	this->menu = menu;
	this->selectTitle = select;
}
