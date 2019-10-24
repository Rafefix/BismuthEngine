#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Globals.h"

class GameObject;

enum class COMPONENT_TYPE {
	NONE,
	TRANSFORM,
	MATERIAL,
	MESH
};

class Component {
public:
	
	Component(COMPONENT_TYPE type, GameObject* parent = nullptr, bool active = true) :
		type(type), active(active), parent(parent) {}


	virtual ~Component() {}

	virtual void Update() {}
	virtual void Enable() {}
	virtual void Disable() {}

	virtual void OnEditor() {}

public:
	COMPONENT_TYPE type;
	GameObject* parent;
	bool active;
};

#endif // __COMPONENT_H__ 
