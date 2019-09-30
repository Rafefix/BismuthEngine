#include "GuiConfig.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "glew/include/GL/glew.h"
#include <stdio.h>

GuiConfig::GuiConfig(bool is_visible) : GuiElement(is_visible), fps_vec(HISTOGRAM_BARS), ms_vec(HISTOGRAM_BARS) {}

GuiConfig::~GuiConfig() {}

void GuiConfig::Start(){

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
	App->window->GetSize(window_width, window_height);
	ImGui::SetNextWindowPos(ImVec2(200, 18), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2((float)window_width / 5, (float)window_height - 18), ImGuiCond_Once);

	if (!visible) {
		return;
	}
		

	if (ImGui::Begin("Configuration", &visible, ImGuiWindowFlags_AlwaysAutoResize))
	{

		App->window->GetSize(width, height);

		ImGui::SliderInt("Width", &width, 1, 1920);
		ImGui::SliderInt("Height", &height, 1, 1080);
		ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f);

		SDL_SetWindowBrightness(App->window->window, brightness);
		SDL_SetWindowSize(App->window->window, width, height);


		if (ImGui::Checkbox("Full Screen", &fullscreen)){
			App->window->SetFullScreen(fullscreen);
		}
			
		

		if (ImGui::Checkbox("Resizable", &resizable)) {
			App->window->SetResizable(resizable); 
		}

		if (ImGui::Checkbox("Borderless", &borderless)) {
			App->window->SetBorderless(borderless);
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
	
		}

		if (ImGui::CollapsingHeader("Application"))
		{
			int max_fps = App->GetMaxFps();

			if (ImGui::SliderInt("Max FPS", &max_fps, 0, 200)) {
				App->SetMaxFps(max_fps);
			}
				

			ImGui::Text("Limit Framerate:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), "%d", App->GetMaxFps());

			char title[25];
			sprintf_s(title, 25, "Framerate %.1f", fps_vec[fps_vec.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fps_vec[0], fps_vec.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));

			sprintf_s(title, 25, "Milliseconds %0.1f", ms_vec[ms_vec.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &ms_vec[0], ms_vec.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
		}

		ImGui::End();
	}


}

void GuiConfig::CleanUp()
{
}

void GuiConfig::GetFps(float fps)
{
	static uint count = 0;

	if (count == HISTOGRAM_BARS)
	{
		for (uint i = 0; i < HISTOGRAM_BARS - 1; ++i)
			fps_vec[i] = fps_vec[i + 1];
	}
	else
		++count;

	fps_vec[count - 1] = fps;
}

void GuiConfig::GetMs(float ms)
{
	static uint count = 0;

	if (count == HISTOGRAM_BARS)
	{
		for (uint i = 0; i < HISTOGRAM_BARS - 1; ++i)
			ms_vec[i] = ms_vec[i + 1];
	}
	else
		++count;

	ms_vec[count - 1] = ms;
}