#ifndef __GUIABOUT__
#define __GUIABOUT__

#include "ModuleGui.h"

class GuiAbout : public GuiElement
{
public:

	GuiAbout(bool is_visible = true);
	virtual ~GuiAbout();

public:
	void Start();
	void Draw();
	void CleanUp();

private:
	int   window_width = 0;
	int   window_height = 0;
};

#endif __GUIABOUT__
