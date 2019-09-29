#include "GuiConfig.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "imgui.h"

GuiConfig::GuiConfig() {}

GuiConfig::~GuiConfig() {}

void GuiConfig::Start(){
}

void GuiConfig::Draw(){
	App->window->GetSize(window_width, window_height);
	ImGui::SetNextWindowPos(ImVec2(200, 18), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2((float)window_width / 5, (float)window_height - 18), ImGuiCond_Once);

	if (ImGui::Begin("Configuration", NULL, ImGuiWindowFlags_NoCollapse)){

		ImGui::SliderInt("Width", &width, 1, 1920);
		ImGui::SliderInt("Height", &height, 1, 1080);
		ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f);

		SDL_SetWindowBrightness(App->window->window, brightness);
		SDL_SetWindowSize(App->window->window, width, height);


		if (ImGui::Checkbox("Full Screen", &fullscreen)){
			App->window->SetFullScreen(fullscreen);
		}
			
		//ImGui::SameLine();

		if (ImGui::Checkbox("Resizable", &resizable)) {
			App->window->SetResizable(resizable); //CHECK LATER
		}

		if (ImGui::Checkbox("Borderless", &borderless)) {
			App->window->SetBorderless(borderless);
		}
		
			

		ImGui::End();
	}


}

void GuiConfig::CleanUp()
{
}