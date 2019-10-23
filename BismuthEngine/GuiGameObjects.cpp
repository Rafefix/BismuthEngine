#include "GuiGameObjects.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "imgui.h"

GameObjects::GameObjects(bool is_visible) : GuiElement(is_visible) {}

GameObjects::~GameObjects() {}

void GameObjects::Start()
{
}

void GameObjects::Draw()
{
	App->window->GetSize(window_width, window_height);
	ImGui::SetNextWindowPos(ImVec2(0, 18), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2((float)window_width / 5, (float)window_height - 18), ImGuiCond_Once);

	if (ImGui::Begin("GameObjects: Heriarchy", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
	{

		ImGui::End();
	}
}

void GameObjects::CleanUp()
{
}
