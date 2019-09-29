#ifndef __GUICONFIG__H__
#define __GUICONFIG__H__

#include "ModuleGui.h"

class GuiConfig : public GuiElement
{
public:

	GuiConfig();
	virtual ~GuiConfig();

public:
	void Start();
	void Draw();
	void CleanUp();

private:
	int		window_width = 0;
	int		window_height = 0;
	int		width = SCREEN_WIDTH;
	int		height = SCREEN_HEIGHT;
	float	brightness = 1.0f;

	bool	fullscreen = false;
	bool	resizable = false;
	bool	borderless = false;
	bool	fulldesktop = false;
};

#endif __GUICONFIG__H__
