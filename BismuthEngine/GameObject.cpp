#include "GameObject.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "ComponentTransformation.h"
#include "glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Application.h"
#include "ModuleImporter.h"

#include "glmath.h"


GameObject::GameObject(std::string name, GameObject* parent) :
	name(name), parent(parent)
{
	Mesh_comp = (CMesh*)AddComponent(COMPONENT_TYPE::MESH);
	Tex_comp = (CMaterial*)AddComponent(COMPONENT_TYPE::MATERIAL);
	Transf_comp = (CTransform*)AddComponent(COMPONENT_TYPE::TRANSFORM);
}


void GameObject::Update() {
	
	for (int i = 0; i < components.size(); ++i)
		if (components[i]->active) components[i]->Update();
}


Component* GameObject::AddComponent(COMPONENT_TYPE type, bool active) {
	Component* ret = nullptr;
	switch (type)
	{
	case COMPONENT_TYPE::MATERIAL:
		ret = new CMaterial(type, this, active);
		if (ret != nullptr) components.push_back(ret); break;

	case COMPONENT_TYPE::MESH:
		ret = new CMesh(type, this, active);
		if (ret != nullptr) components.push_back(ret); break;
		
	case COMPONENT_TYPE::TRANSFORM:
		ret = new CTransform(type, this, active);
		if (ret != nullptr) components.push_back(ret); break;

	}


	return ret;
}

void GameObject::OnEditor() {
	for (int i = 0; i < components.size(); ++i)
		components[i]->OnEditor();
}

void GameObject::Draw() const {
	
	for (uint i = 0; i < Mesh_comp->mesh.size(); ++i) {

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		if (Tex_comp->active) {
			glBindTexture(GL_TEXTURE_2D, Tex_comp->texture);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, App->importer->def_texture);
		}
			glActiveTexture(GL_TEXTURE0);
			glBindBuffer(GL_ARRAY_BUFFER, Mesh_comp->mesh[i]->id_texture);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		

		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, Mesh_comp->mesh[i]->id_vertex);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh_comp->mesh[i]->id_index);
		glDrawElements(GL_TRIANGLES, Mesh_comp->mesh[i]->num_indices, GL_UNSIGNED_INT, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void GameObject::CleanUp() {

	for (int i = 0; i < components.size(); ++i) {
		delete components[i];
		components[i] = nullptr;
	}
}

//void GameObject::Delete()
//{
//
//}
