#ifndef __GuiConsole__H__
#define __GuiConsole__H__

#include "ModuleGui.h"

class GuiConsole : public GuiElement
{
public:

	GuiConsole(bool is_visible = true);
	virtual ~GuiConsole();

	ImVector<char*> LogList;

	bool Scroll;

public:

	void Start();
	void Draw();
	void CleanUp();

	void ClearLog();
	void AddLog(char* log, ...);

private:
	
	int   window_width = 0;
	int   window_height = 0;
};

#endif __GuiConsole__H__

