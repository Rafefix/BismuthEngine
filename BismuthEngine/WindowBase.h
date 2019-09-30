#ifndef __WindowBase__H__
#define __WindowBase__H__

#include "ModuleGui.h"

class WindowBase : public GuiElement
{
public:

	WindowBase(bool is_visible = true);;
	virtual ~WindowBase();

public:
	void Start();
	void Draw();
	void CleanUp();

private:
	int   window_width = 0;
	int   window_height = 0;
};

#endif __WindowBase__H__
