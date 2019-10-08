#include "GuiConsole.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "imgui.h"

GuiConsole::GuiConsole(bool is_visible) : GuiElement(is_visible) {}

GuiConsole::~GuiConsole() {}

void GuiConsole::Start()
{
}

void GuiConsole::Draw()
{
	if (!visible) {
		return;
	}

	App->window->GetSize(window_width, window_height);
	ImGui::SetNextWindowPos(ImVec2(300, 600), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2((float)window_width / 2.5, (float)window_height/ 2), ImGuiCond_Once);

	if (ImGui::Begin("Console", &visible))
	{
		ImGui::Text("System RAM: ");
		ImGui::End();
	}
}

void GuiConsole::CleanUp()
{
}
