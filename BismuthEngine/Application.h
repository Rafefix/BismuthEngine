#ifndef __Application__
#define __Application__

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"

#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleScene.h"
#include "ModuleGui.h"
#include "ModuleImporter.h"
#include <list>

#define HISTOGRAM_BARS 100

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;

	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleImporter* importer;
	ModuleScene* scene;
	ModuleGui* gui;

	std::vector<float> fps_vec;
	std::vector<float> ms_vec;
	int maxFps = 60;

private:
	
	uint frame_count = 0;
	uint last_sec_frame_count = 0;
	uint prev_last_sec_frame_count = 0;
	uint framerate_cap = 0;
	int	 capped_ms = -1;

	Timer					startup_time;
	Timer					frame_time;
	Timer					last_sec_frame_time;

	float	dt;
	JsonLoader Loader;
	std::list<Module*> modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	

private:
	void LoadAllConfig(json &file);
	void SaveAllConfig();
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* App;

#endif __Application__