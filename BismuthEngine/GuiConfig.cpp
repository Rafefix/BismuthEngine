#include "GuiConfig.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleScene.h"
#include "ModuleRenderer3D.h"
#include "imgui.h"
#include "glew/include/GL/glew.h"
#include <stdlib.h>

GuiConfig::GuiConfig(bool is_visible) : GuiElement(is_visible) {}

GuiConfig::~GuiConfig() {}

void GuiConfig::Start(){

	SDL_GetVersion(&sdl_version);

	if (SDL_Has3DNow())
		caps += "3DNow, ";
	if (SDL_HasAltiVec())
		caps += "AltiVec, ";
	if (SDL_HasAVX())
		caps += "AVX, ";
	if (SDL_HasAVX2())
		caps += "AVX2, ";
	if (SDL_HasMMX())
		caps += "MMX, ";
	if (SDL_HasRDTSC())
		caps += "RDTSC, ";
	if (SDL_HasSSE())
		caps += "SSE, ";
	if (SDL_HasSSE2())
		caps += "SSE2, ";
	if (SDL_HasSSE3())
		caps += "SSE3, ";
	if (SDL_HasSSE41())
		caps += "SSE41, ";
	if (SDL_HasSSE42())
		caps += "SSE42";

}

void GuiConfig::Draw(){
	
	if (!visible) {
		return;
	}

	App->window->GetSize(window_width, window_height);
	ImGui::SetNextWindowPos(ImVec2(200, 18), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2((float)window_width / 2.5, (float)window_height/2 ), ImGuiCond_Once);

	
		

	if (ImGui::Begin("Configuration", &visible))
	{

		if (ImGui::CollapsingHeader("Window")) {
			//App->renderer3D->OnResize((int)width, (int)height); //LATER1 BUG WHEN OPENED WINDOW MENU GRID NOT RENDERING CORRECTLY
			App->window->GetSize(width, height);

			ImGui::SliderInt("Width", &width, 1, 1920);
			ImGui::SliderInt("Height", &height, 1, 1080);
			
			
			ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f);

			SDL_SetWindowBrightness(App->window->window, brightness);
			SDL_SetWindowSize(App->window->window, width, height);


			if (ImGui::Checkbox("Full Screen", &fullscreen)) {
				App->window->SetFullScreen(fullscreen);
			}

			if (ImGui::Checkbox("Resizable", &resizable)) {
				App->window->SetResizable(resizable);
			}

			if (ImGui::Checkbox("Borderless", &borderless)) {
				App->window->SetBorderless(borderless);
			}

			if (ImGui::Checkbox("Set Default", &defaults)) {
				SDL_SetWindowSize(App->window->window, 1024, 768);
			}

			if (width != 1024 || height != 768) {
				defaults = false;
			}

		}
		
		if (ImGui::CollapsingHeader("Style editor")) {
			ImGui::ShowStyleEditor();
		}
		
		if (ImGui::CollapsingHeader("Input")){
	
			float x = App->gui->io->MousePos.x;
			float y = App->gui->io->MousePos.y;

			ImGui::Text("Mouse position: (%g, %g)",x , y);
			
			ImGui::Text("Mouse delta: (%g, %g)", App->gui->io->MouseDelta.x, App->gui->io->MouseDelta.y);

			ImGui::Text("Mouse down:");    
			for (int i = 0; i < IM_ARRAYSIZE(App->gui->io->MouseDown); i++) {
				if (App->gui->io->MouseDownDuration[i] >= 0.0f) {
					ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, App->gui->io->MouseDownDuration[i]);
				}
			}
					
				ImGui::Text("Mouse clicked:");  
			for (int i = 0; i < IM_ARRAYSIZE(App->gui->io->MouseDown); i++) {
				if (ImGui::IsMouseClicked(i)) {
						ImGui::SameLine(); ImGui::Text("b%d", i);
				}

			}
			
				ImGui::Text("Mouse dbl-clicked:");
			for (int i = 0; i < IM_ARRAYSIZE(App->gui->io->MouseDown); i++) {
				if (ImGui::IsMouseDoubleClicked(i)) {
					ImGui::SameLine(); ImGui::Text("b%d", i);
				}
			}
				
				ImGui::Text("Mouse released:"); 
			for (int i = 0; i < IM_ARRAYSIZE(App->gui->io->MouseDown); i++) {
				if (ImGui::IsMouseReleased(i)) {
					ImGui::SameLine(); ImGui::Text("b%d", i);
				}
			}
				
				
		}


		if (ImGui::CollapsingHeader("Hardware")){
			
		
			ImGui::Text("CPUs: ");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%d", SDL_GetCPUCount());
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "(Cache: %d kb)", SDL_GetCPUCacheLineSize());

			ImGui::Text("System RAM: ");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%f Gb", SDL_GetSystemRAM() / 1024.0f);

			ImGui::Text("Caps: ");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), caps.c_str());

			ImGui::Separator();

			ImGui::Text("GPU: ");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", glGetString(GL_RENDERER));

			ImGui::Text("Brand: ");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", glGetString(GL_VENDOR));

			ImGui::Text("Version: ");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", glGetString(GL_VERSION));

			glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &video_mem_budget);
			ImGui::Text("VRAM Budget");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(255, 255, 0, 255), "%f", float(video_mem_budget) / (1024.0f));

			glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &video_mem_available);
			ImGui::Text("VRAM Available");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(255, 255, 0, 255), "%f", float(video_mem_usage) / (1024.f));

			video_mem_usage = video_mem_budget - video_mem_available;
			ImGui::Text("VRAM Usage");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(255, 255, 0, 255), "%f", float(video_mem_available) / (1024.f));
	
		}

		if (ImGui::CollapsingHeader("Application"))
		{
			ImGui::SliderInt("Max FPS", &App->maxFps, 1, 200);
				

			ImGui::Text("Limit Framerate:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), "%d", App->maxFps);

			char title[25];
			sprintf_s(title, 25, "Framerate %.1f", App->fps_vec[App->fps_vec.size() - 1]);
			ImGui::PlotHistogram("##framerate", &App->fps_vec[0], App->fps_vec.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			sprintf_s(title, 25, "Milliseconds %0.1f", App->ms_vec[App->ms_vec.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &App->ms_vec[0], App->ms_vec.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
	
		}
		

		
		
	}

	ImGui::End();
}

void GuiConfig::CleanUp()
{
}

