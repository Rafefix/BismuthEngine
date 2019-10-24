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

		if (ImGui::CollapsingHeader("Basic shapes")) {
			//LATER1 Maybe add them to gameobjects not priority
		if (ImGui::Button("CUBE")) { 
			App->scene->createShape(SHAPE::CUBE, vec3(0, 0, 0), vec3(1, 1, 1)); 
		}
		if (ImGui::Button("SPHERE")) {
			App->scene->createShape(SHAPE::SPHERE, vec3(0, 0, 0), vec3(1, 1, 1)); 
		}
		if (ImGui::Button("OCTOHEDRON")) { 
			App->scene->createShape(SHAPE::OCTOHEDRON, vec3(0, 0, 0), vec3(1, 1, 1));
		}
		if (ImGui::Button("DODECAHEDRON")) { 
			App->scene->createShape(SHAPE::DODECAHEDRON, vec3(0, 0, 0), vec3(1, 1, 1));
		}
		if (ImGui::Button("ICOSAHEDRON")) {
			App->scene->createShape(SHAPE::ICOSAHEDRON, vec3(0, 0, 0), vec3(1, 1, 1));
		}
		if (ImGui::Button("TETRAHEDRON")) { 
			App->scene->createShape(SHAPE::TETRAHEDRON, vec3(0, 0, 0), vec3(1, 1, 1)); 
		}
		if (ImGui::Button("PLANE")) {
			App->scene->createShape(SHAPE::PLANE, vec3(0, 0, 0), vec3(1, 1, 1));
		}
		//if (ImGui::Button("TORUS")) {
		//App->scene->createShape(SHAPE::TORUS, vec3(0, 0, 0), vec3(1, 1, 1));
		//}
		if (ImGui::Button("CONE")) {
			App->scene->createShape(SHAPE::CONE, vec3(0, 0, 0), vec3(1, 1, 1)); }
		if (ImGui::Button("CYLINDER")) {
			App->scene->createShape(SHAPE::CYLINDER, vec3(0, 0, 0), vec3(1, 1, 1)); }

		}
		
		if (ImGui::CollapsingHeader("Rendering options"))
		{
			if (ImGui::Checkbox("Depth Test", &DepthTest))
				App->renderer3D->DepthTestEnable(DepthTest);

			if (ImGui::Checkbox("Cull Face", &CullFace))
				App->renderer3D->CullFaceEnable(CullFace);

			if (ImGui::Checkbox("Lighting", &Lighting))
				App->renderer3D->LightingEnable(Lighting);

			if (ImGui::Checkbox("Color Material", &MaterialColor))
				App->renderer3D->ColorMaterialEnable(MaterialColor);

			if (ImGui::Checkbox("Texture 2D", &Texture2D))
				App->renderer3D->Texture2DEnable(Texture2D);


		}

		ImGui::End();
	}
	
}

void Gui3DOBJ::CleanUp()
{
}

