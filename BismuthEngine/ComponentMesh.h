#ifndef _COMPONENTMESH_H_
#define _COMPONENTMESH_H_

#include "Component.h"
#include <vector>

struct MeshData {

	uint id_index = 0;
	uint num_indices = 0;
	uint* indices = nullptr;
	uint id_vertex = 0;
	uint num_vertices = 0;
	float* vertices = nullptr;
	uint id_texture = 0;
	uint num_texture = 0;
	float* textures = nullptr;

};


class ComponentMesh : public Component {
public:
	ComponentMesh(COMPONENT_TYPE type, GameObject* parent, bool active) :
		Component(type, parent, active) {}

	~ComponentMesh() {}

	void Update() {}
	void Enable() { active = true; }

	void OnEditor() {
		
		if (ImGui::CollapsingHeader("Mesh")) {
			ImGui::Checkbox("Enabled", &active);

			ImGui::Text("Vertices:");
			ImGui::SameLine();
			uint cnt1 = 0;
			for (uint i = 0; i < mesh.size(); ++i) cnt1 += mesh[i]->num_vertices;
			ImGui::TextColored({ 255, 255, 0, 255 }, "%d", cnt1);

			ImGui::Text("Faces:");
			ImGui::SameLine();
			uint cnt2 = 0;
			for (uint i = 0; i < mesh.size(); ++i) cnt2 += mesh[i]->num_indices;
			ImGui::TextColored({ 255, 255, 0, 255 }, "%d", cnt2);

			ImGui::NewLine();
		}
	}

	void Load() {};

public:
	std::vector<MeshData*> mesh;
};

#endif // _COMPONENTMESH_H_ 
