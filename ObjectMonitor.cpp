#include "ObjectMonitor.h"

duckTape::objectMonitor::objectMonitor(debugMenu* menu, std::string select): Window(menu, select)
{

}

void duckTape::objectMonitor::logic()
{
}

void duckTape::objectMonitor::render()
{
	if (isEnabled) {
		ImGui::Begin("Object Monitoring", &isEnabled);
		//iterate through every component in the scene
		//create combo box for each item and show them as an option
		//show button which creates a new window tracking that component!
		ImGui::End();
	}
}
