#ifndef __MODULEGAMEOBJECT_H__
#define __MODULEGAMEOBJECT_H__

#include <vector>
#include "Module.h"
#include "Component.h"
#include <vector>

class ComponentMesh;
class ComponentMaterial;
class ComponentTransform;

class GameObject {
public:

	GameObject() {};
	GameObject(std::string name, GameObject* parent = nullptr);
	
	virtual ~GameObject() {};
	void Start();
	void Update();
	void Draw() const;		
	void CleanUp();

	Component* CreateComponent(COMPONENT_TYPE type, bool active = true);
	void OnEditor();
public:

	ComponentMesh* Mesh_comp = nullptr;
	ComponentMaterial* Tex_comp = nullptr;	
	ComponentTransform* Transf_comp = nullptr;

	std::string name = nullptr;
	std::vector<Component*> components;
	std::vector<GameObject*> children;
	GameObject* parent;
};

#endif // __MODULEGAMEOBJECT_H__ 
