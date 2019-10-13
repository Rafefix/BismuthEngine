#ifndef __Application__
#define __Application__

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
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

	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleRenderer3D* renderer3D = nullptr;
	ModuleCamera3D* camera = nullptr;
	ModuleImporter* imp = nullptr;


	ModuleScene* scene = nullptr;
	ModuleGui* gui = nullptr;

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
	JsonLoader jsonLoader;

	std::list<Module*> modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* App;

#endif __Application__