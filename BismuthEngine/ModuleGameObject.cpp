#include "ModuleGameObject.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"

#include "glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "glmath.h"


GameObject::GameObject(char* name, GameObject* parent) :
	name(name), parent(parent)
{
	c_mesh = (ComponentMesh*)CreateComponent(COMPONENT_TYPE::MESH);
	c_texture = (ComponentMaterial*)CreateComponent(COMPONENT_TYPE::MATERIAL);
}


void GameObject::Update() {
	
	for (int i = 0; i < components.size(); ++i)
		if (components[i]->active) components[i]->Update();
}


Component* GameObject::CreateComponent(COMPONENT_TYPE type, bool active) {
	Component* ret = nullptr;
	switch (type)
	{
	case COMPONENT_TYPE::MATERIAL:
		ret = new ComponentMaterial(type, this, active);
		if (ret != nullptr) components.push_back(ret); break;

	case COMPONENT_TYPE::MESH:
		ret = new ComponentMesh(type, this, active);
		if (ret != nullptr) components.push_back(ret); break;
		
	}


	return ret;
}

void GameObject::OnEditor() {
	for (int i = 0; i < components.size(); ++i)
		components[i]->OnEditor();
}

void GameObject::Draw() const {
	
	for (uint i = 0; i < c_mesh->mesh.size(); ++i) {

		if (c_texture->active) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindTexture(GL_TEXTURE_2D, c_texture->texture);
			glActiveTexture(GL_TEXTURE0);
			glBindBuffer(GL_ARRAY_BUFFER, c_mesh->mesh[i]->id_texture);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		}
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, c_mesh->mesh[i]->id_vertex);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c_mesh->mesh[i]->id_index);
		glDrawElements(GL_TRIANGLES, c_mesh->mesh[i]->num_indices, GL_UNSIGNED_INT, NULL);

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
