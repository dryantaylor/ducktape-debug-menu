#include "frameMonitor.h"
static constexpr int MONITORING_SAMPLES = 256;


duckTape::frameMonitor::frameMonitor(debugMenu* menu, std::string select):
Window(menu ,select) {

	constFTenabled = false;
	constFTvalue = 0;
	monitoringEnabled = false;
	FTtick = 0;

	monitoringTick = 0;
	monitoringInterval = 100;
	monitoringValues = new float[MONITORING_SAMPLES];
	std::fill(monitoringValues, &monitoringValues[MONITORING_SAMPLES], 0.0f);
	writeIndex = 0;
}

void duckTape::frameMonitor::logic() {
	if (monitoringEnabled) {
		monitoringTick+= *getdeltaTimePtr();
	}

	if (constFTenabled) {
		FTtick += *getdeltaTimePtr();
		if (FTtick >= constFTvalue) {
			*getdeltaTimePtr() = FTtick;
			FTtick = 0;
		}
		else { *getdeltaTimePtr() = 0; }

	}

	if (monitoringEnabled && 
		monitoringTick >= monitoringInterval &&
		*getdeltaTimePtr() != 0) {
		
		while (monitoringTick > monitoringInterval) {
			monitoringValues[writeIndex] = *getdeltaTimePtr();
			writeIndex = (writeIndex + 1) % (MONITORING_SAMPLES);
			std::cout << writeIndex << std::endl;
			monitoringTick -= monitoringInterval;
		}
		
	}


}

void duckTape::frameMonitor::render() {
	if (isEnabled) {
		static char buf[4] = "";
		ImGui::Begin("Frame monitor", &isEnabled);
		ImGui::InputText("set const framerate", buf, 4,
			ImGuiInputTextFlags_CharsDecimal);
		ImGui::Checkbox("enable const framerate", &constFTenabled);
		
		ImGui::Separator();
		ImGui::SeparatorText("Monitoring");
		ImGui::Checkbox("monitoring enabled", &monitoringEnabled);
		if (monitoringEnabled) {
			char out[] = "";
			ImGui::PlotLines("frame times: ", monitoringValues,
				MONITORING_SAMPLES, writeIndex);
		}
		ImGui::Text("Current Ph<ysics Tick: ");
		ImGui::Text()
		ImGui::End();

		if (constFTenabled) {
			try {
				std::uint32_t fr =  std::stoul(buf, nullptr);

				//oh nuuu 0fps is actually a lie, and is instead 2e^(-7) fps
				constFTvalue = fr > 0 ? 1000 / fr : SDL_MAX_UINT32;
				std::cout << constFTvalue << std::endl;
			}
			catch (std::exception e) {
				constFTenabled = false;
				std::cout << buf << std::endl;
				std::cout << e.what() << std::endl;
			}
		}
	}
}

duckTape::frameMonitor::~frameMonitor() {

}