#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include "Module.h"
#include "Component.h"
#include <vector>

class CMesh;
class CMaterial;
class CTransform;

class GameObject {
public:

	GameObject() {};
	GameObject(std::string name, GameObject* parent = nullptr);
	
	virtual ~GameObject() {};
	void Update();
	void Draw() const;		
	void CleanUp();

	Component* AddComponent(COMPONENT_TYPE type, bool active = true);
	void OnEditor();
public:

	CMesh* Mesh_comp = nullptr;
	CMaterial* Tex_comp = nullptr;
	CTransform* Transf_comp = nullptr;

	std::string name = nullptr;
	std::vector<Component*> components;
	std::vector<GameObject*> children;
	GameObject* parent;
};

#endif // __GAMEOBJECT_H__ 
