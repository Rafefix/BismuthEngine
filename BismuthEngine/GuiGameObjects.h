#ifndef __GUIGAMEOBJECTS__H__
#define __GUIGAMEOBJECTS__H__

#include "ModuleGui.h"

class GameObjects : public GuiElement
{
public:

	GameObjects(bool is_visible = true);;
	virtual ~GameObjects();

public:
	void Start();
	void Draw();
	void CleanUp();

private:
	int   window_width = 0;
	int   window_height = 0;
};

#endif __GUIGAMEOBJECTS__H__
