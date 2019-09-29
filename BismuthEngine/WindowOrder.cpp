#include "WindowOrder.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "imgui.h"

WindowOrder::WindowOrder() {}

WindowOrder::~WindowOrder() {}

void WindowOrder::Start()
{
}

void WindowOrder::Draw()
{
	App->window->GetSize(window_width, window_height);
	ImGui::SetNextWindowPos(ImVec2(0, 18), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2((float)window_width / 5, (float)window_height - 18), ImGuiCond_Once);

	if (ImGui::Begin("Windows", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
	{

		ImGui::End();
	}
}

void WindowOrder::CleanUp()
{
}
