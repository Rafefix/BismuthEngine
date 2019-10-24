#include "GuiInspector.h"
#include "ModuleGameObject.h"
#include "Application.h"
#include "ModuleScene.h"
#include "imgui.h"


GuiInspector::GuiInspector(bool is_visible) : GuiElement(is_visible) {}

GuiInspector::~GuiInspector() {}

void GuiInspector::Start()
{
}
void GuiInspector::Draw() {
	
	/*if (!visible) {
		return;
	}
	*/
	App->window->GetSize(window_width, window_height);
	ImGui::SetNextWindowPos(ImVec2(300, 600), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2((float)window_width / 2, (float)window_height / 4.5), ImGuiCond_Once);

	ImGui::Begin("Inspector", &visible);

	if (App->scene->selected != nullptr) {
		ImGui::TextColored(ImVec4(0, 128, 128, 255), App->scene->selected->name.c_str());
		ImGui::NewLine();
		App->scene->selected->OnEditor();
	}

	ImGui::End();
}

void GuiInspector::CleanUp()
{
}