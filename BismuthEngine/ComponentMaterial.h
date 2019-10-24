#ifndef _COMPONENTMATERIAL_H_
#define _COMPONENTMATERIAL_H_

#include "Component.h"

class ComponentMaterial : public Component {
public:
	ComponentMaterial(COMPONENT_TYPE type, GameObject* parent, bool active) :
		Component(type, parent, active) {}

	~ComponentMaterial() {}

	
	void Update() {}
	void Enable() { active = true; }
	void Disable() { active = false; }

	void OnEditor() {}

public:
	uint texture = 0;
};

#endif // _COMPONENTMATERIAL_H_ 
