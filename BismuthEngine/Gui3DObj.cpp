#include "Gui3DObj.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "imgui.h"
#include "glew/include/GL/glew.h"
#include <stdlib.h>

Gui3DOBJ::Gui3DOBJ(bool is_visible) : GuiElement(is_visible) {}

Gui3DOBJ::~Gui3DOBJ() {}

void Gui3DOBJ::Start() {

}

void Gui3DOBJ::Draw() {

	if (!visible) {
		return;
	}


	App->window->GetSize(window_width, window_height);
	ImGui::SetNextWindowPos(ImVec2(200, 18), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2((float)window_width / 2.5, (float)window_height / 2), ImGuiCond_Once);


	if (ImGui::Begin("3D Objects", &visible)) {
		
		/*if (ImGui::CollapsingHeader("Position")) {
			ImGui::SliderInt("X", position.x, -25, 25);
			ImGui::SliderInt("Y", &, -25, 25);
			ImGui::SliderInt("Z", &, -25, 25);
		}

		
		if (ImGui::CollapsingHeader("Transformations")) {
			ImGui::SliderInt("Width", &, 1, 25);
			ImGui::SliderInt("Height", &, 1, 25);
			ImGui::SliderInt("Depth", &, 1, 25);
		}*/

		if (ImGui::Button("CUBE")) { App->scene->createShape(SHAPE::CUBE, vec3(0, 0, 0), vec3(1, 1, 1)); }
		if (ImGui::Button("SPHERE")) { App->scene->createShape(SHAPE::SPHERE, vec3(0, 0, 0), vec3(1, 1, 1)); }
		if (ImGui::Button("OCTOHEDRON")) { App->scene->createShape(SHAPE::OCTOHEDRON, vec3(0, 0, 0), vec3(1, 1, 1)); }
		if (ImGui::Button("DODECAHEDRON")) { App->scene->createShape(SHAPE::DODECAHEDRON, vec3(0, 0, 0), vec3(1, 1, 1)); }
		if (ImGui::Button("ICOSAHEDRON")) { App->scene->createShape(SHAPE::ICOSAHEDRON, vec3(0, 0, 0), vec3(1, 1, 1)); }
		if (ImGui::Button("TETRAHEDRON")) { App->scene->createShape(SHAPE::TETRAHEDRON, vec3(0, 0, 0), vec3(1, 1, 1)); }
		if (ImGui::Button("PLANE")) { App->scene->createShape(SHAPE::PLANE, vec3(0, 0, 0), vec3(1, 1, 1)); }
		if (ImGui::Button("TORUS")) { App->scene->createShape(SHAPE::TORUS, vec3(0, 0, 0), vec3(1, 1, 1)); }
		if (ImGui::Button("CONE")) { App->scene->createShape(SHAPE::CONE, vec3(0, 0, 0), vec3(1, 1, 1)); }
		if (ImGui::Button("CYLINDER")) { App->scene->createShape(SHAPE::CYLINDER, vec3(0, 0, 0), vec3(1, 1, 1)); }
		ImGui::End();
	}
	
}

void Gui3DOBJ::CleanUp()
{
}

