#ifndef __ModuleGui_H__
#define __ModuleGui_H__

#include "Module.h"
#include <list>
#include <string>
#include "imgui.h"
#include "SDL/include/SDL_events.h"

#include "SDL/include/SDL_rect.h"
#include "SDL/include/SDL_video.h"

#define CURSOR_WIDTH 2

struct SDL_Texture;
struct _TTF_Font;
struct SDL_Rect;
struct SDL_Color; 

class GameObjects;
class GuiConfig;
class GuiAbout;
class GuiConsole;
class Gui3DOBJ;
class GuiInspector;

class  GuiElement
{
public:
	GuiElement(bool is_visible) {
		visible = is_visible;
	};
	virtual ~GuiElement() {};

	virtual void Start() {};
	virtual void Draw() {};
	virtual void CleanUp() {};


	bool visible = false;
};

// ---------------------------------------------------
class ModuleGui : public Module
{
public:

	ModuleGui(Application* app, bool start_enabled = true);
	~ModuleGui();

public:

	bool Init(json file);
	bool Start();
	bool CleanUp();
	void Draw() const;
	void MouseInput(SDL_Event * event);
	update_status PreUpdate(float dt);
	update_status Update(float dt);

	GuiConsole* console = nullptr;
	
private:

	void AddGuiElement(GuiElement* element);
	
	void HelpMarker(const char* desc);


private:

	bool show_demo_window = false;
	bool show_style_editor = false;
	bool show_console = true;

	class std::list<GuiElement*> gui_elements;

	GameObjects* heri = nullptr;
	GuiConfig* config = nullptr;
	GuiAbout* about = nullptr;
	Gui3DOBJ* obj = nullptr;
	GuiInspector* inspector = nullptr;

public:

	ImGuiIO* io;
	
};

#endif  __ModuleGui_H__