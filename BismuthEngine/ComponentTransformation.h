#ifndef _COMPONENTTRANSFORMATION_H_
#define _COMPONENTTRANSFORMATION_H_

#include "Component.h"
#include "GuiInspector.h"
#include <vector>



class CTransform : public Component {
public:
	CTransform(COMPONENT_TYPE type, GameObject* parent, bool active) :
		Component(type, parent, active) {}

	~CTransform() {}

	void Update() {}
	void Enable() { active = true; }

	void OnEditor() {
		

		if (ImGui::CollapsingHeader("Transform")) {
			
			ImGui::SliderInt("X Rotation", &Rotx, -180, 180);
			ImGui::SliderInt("Y Rotation", &Roty, -180, 180);
			ImGui::SliderInt("Z Rotation", &Rotz, -180, 180);
		}
	}

	void Load() {};

public:

	int Rotx = 0;
	int Roty = 0;
	int Rotz = 0;

};

#endif // _COMPONENTTRANSFORMATION_H_ 

