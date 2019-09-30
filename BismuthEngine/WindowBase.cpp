#include "WindowBase.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "imgui.h"

WindowBase::WindowBase(bool is_visible) : GuiElement(is_visible) {}

WindowBase::~WindowBase() {}

void WindowBase::Start()
{
}

void WindowBase::Draw()
{
	App->window->GetSize(window_width, window_height);
	ImGui::SetNextWindowPos(ImVec2(0, 18), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2((float)window_width / 5, (float)window_height - 18), ImGuiCond_Once);

	if (ImGui::Begin("Windows", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
	{

		ImGui::End();
	}
}

void WindowBase::CleanUp()
{
}
