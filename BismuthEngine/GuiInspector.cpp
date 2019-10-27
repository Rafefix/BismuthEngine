#include "GuiInspector.h"
#include "GameObject.h"
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
	//LATER1 TRY TO MAKE IT CLOSE AND OPEN AGAIN by double clicking sleected or something idk


	App->window->GetSize(window_width, window_height);
	ImGui::SetNextWindowPos(ImVec2(650, 200), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2((float)window_width / 3, (float)window_height / 2), ImGuiCond_Once);

	ImGui::Begin("Inspector", &visible);

	if (App->scene->selected != nullptr) {

		ImGui::TextColored(ImVec4(0, 128, 128, 255), App->scene->selected->name.c_str());

		static char new_name[50] = "";
		strcpy_s(new_name, 50, App->scene->selected->name.c_str());

		if (ImGui::InputText("", new_name, 50, ImGuiInputTextFlags_EnterReturnsTrue));
		{
			App->scene->selected->name = new_name;
		}

		App->scene->selected->OnEditor();
	}

	ImGui::End();
}

void GuiInspector::CleanUp()
{
}