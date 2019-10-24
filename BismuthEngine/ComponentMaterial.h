#ifndef _COMPONENTMATERIAL_H_
#define _COMPONENTMATERIAL_H_

#include "Component.h"

class CMaterial : public Component {
public:
	CMaterial(COMPONENT_TYPE type, GameObject* parent, bool active) :
		Component(type, parent, active) {}

	~CMaterial() {}

	
	void Update() {}
	void Enable() { active = true; }

	void OnEditor() {
		if (ImGui::CollapsingHeader("Material")) {
			ImGui::Image((void*)texture, ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
		}
	}

public:
	uint texture = 0;
};

#endif // _COMPONENTMATERIAL_H_ 
