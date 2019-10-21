#ifndef __GUI3DOBJ__H__
#define __GUI3DOBJ__H__

#include "ModuleGui.h"
#include <string>
#include "SDL/include/SDL.h"
#include "glew/include/GL/glew.h"
#include "NewPrimitives.h"

class Gui3DOBJ : public GuiElement {

public:

	Gui3DOBJ(bool is_visible = true);
	virtual ~Gui3DOBJ();

public:
	void Start();
	void Draw();
	void CleanUp();

private:
	vec3 size;
	bool	Texture = false;
public:
	int		window_width = 0;
	int		window_height = 0;
	int		width = SCREEN_WIDTH;
	int		height = SCREEN_HEIGHT;
};

#endif __GUI3DOBJ__H__
