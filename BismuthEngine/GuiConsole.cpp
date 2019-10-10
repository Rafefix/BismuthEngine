#include "GuiConsole.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include <stdlib.h>

GuiConsole::GuiConsole(bool is_visible) : GuiElement(is_visible) {}

GuiConsole::~GuiConsole() {
	ClearLog();
}

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
	ImGui::SetNextWindowSize(ImVec2((float)window_width / 2, (float)window_height/ 4.5), ImGuiCond_Once);

	if (ImGui::Begin("Console", &visible))
	{

		if (ImGui::SmallButton("Clear")) { ClearLog(); } ImGui::SameLine();
		if (ImGui::SmallButton("Add Dummy Text")) { AddLog("some text"); AddLog("display very important message here!"); } ImGui::SameLine();
		if (ImGui::Checkbox("Auto-scroll", &Scroll)); ImGui::Separator();

		
		for (int i = 0; i < LogList.Size; i++)
		{
			const char* item = LogList[i];
		
			ImGui::TextUnformatted(item);
		}

		if (Scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::End();
	}
}

void GuiConsole::CleanUp()
{
}

void GuiConsole::ClearLog()
{
	LogList.clear();
}

void GuiConsole::AddLog(char * log, ...)
{
	LogList.push_back(log);
}
