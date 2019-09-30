#ifndef __GUICONFIG__H__
#define __GUICONFIG__H__

#include "ModuleGui.h"
#include <string>

#include <vector>

#define HISTOGRAM_BARS 50

class GuiConfig : public GuiElement{

public:

	GuiConfig(bool is_visible = true);
	virtual ~GuiConfig();

public:
	void Start();
	void Draw();
	void CleanUp();

	void GetFps(float fps);
	void GetMs(float ms);

private:
	int		window_width = 0;
	int		window_height = 0;
	int		width = SCREEN_WIDTH;
	int		height = SCREEN_HEIGHT;
	float	brightness = 1.0f;

	bool	fullscreen = false;
	bool	resizable = true;
	bool	borderless = false;
	bool	fulldesktop = false;

	std::vector<float> fps_vec;
	std::vector<float> ms_vec;

	std::string	caps;
	std::string	cpus;
	std::string	ram;
	std::string	gpu;
};

#endif __GUICONFIG__H__
