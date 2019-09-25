#ifndef __ModuleGui_H__
#define __ModuleGui_H__

#include "Module.h"
#include <list>
#include <string>
#include "imgui.h"

#include "SDL/include/SDL_rect.h"
#include "SDL/include/SDL_video.h"

#define CURSOR_WIDTH 2

struct SDL_Texture;
struct _TTF_Font;
struct SDL_Rect;
struct SDL_Color; 

class WindowOrder;

class  GuiElement
{
public:
	GuiElement() {};
	virtual ~GuiElement() {};

	virtual void Start() {};
	virtual void Draw() {};
	virtual void CleanUp() {};

};

// ---------------------------------------------------
class ModuleGui : public Module
{
public:

	ModuleGui(Application* app, bool start_enabled = true);
	~ModuleGui();

public:

	bool Init();
	bool Start();
	bool CleanUp();

	update_status PreUpdate(float dt);
	update_status Update(float dt);

private:

	void AddGuiElement(GuiElement* element);
	void StyleEditor(ImGuiStyle* ref = NULL);
	void HelpMarker(const char* desc);

private:
	ImGuiIO* io;

	bool show_demo_window = false;
	bool show_style_editor = false;

	class std::list<GuiElement*> gui_elements;

	WindowOrder*		windoworder = nullptr;
};

#endif  __ModuleGui_H__