#ifndef __GUICONFIG__H__
#define __GUICONFIG__H__

#include "ModuleGui.h"
#include <string>
#include "SDL/include/SDL.h"
#include "glew/include/GL/glew.h"


class GuiConfig : public GuiElement{

public:

	GuiConfig(bool is_visible = true);
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

	bool fullscreen = false;
	bool resizable = true;
	bool borderless = false;
	bool fulldesktop = false;
	bool defaults = true;


	GLint video_mem_budget = 0;
	GLint video_mem_available = 0;
	GLint video_mem_usage = 0;

	SDL_version sdl_version;

	std::string	caps;
	std::string	cpus;
	std::string	ram;
	std::string	gpu;
};

#endif __GUICONFIG__H__
