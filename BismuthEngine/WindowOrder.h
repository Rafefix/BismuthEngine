#ifndef __WindowOrder__H__
#define __WindowOrder__H__

#include "ModuleGui.h"

class WindowOrder : public GuiElement
{
public:

	WindowOrder(bool is_visible = true);;
	virtual ~WindowOrder();

public:
	void Start();
	void Draw();
	void CleanUp();

private:
	int   window_width = 0;
	int   window_height = 0;
};

#endif __WindowOrder__H__
