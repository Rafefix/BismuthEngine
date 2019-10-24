#ifndef __GUIINSPECTOR_H__
#define __GUIINSPECTOR_H__

#include "ModuleGui.h"

class GameObject;


class GuiInspector : public GuiElement
{
public:
	GuiInspector(bool is_visible = true);
	virtual ~GuiInspector();
public:
	void Start();
	void Draw();
	void CleanUp();
public:
	int		window_width = 0;
	int		window_height = 0;
};

#endif // __GUIINSPECTOR_H__ 
