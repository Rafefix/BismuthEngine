#include "Application.h"

Application::Application(){

	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	physics = new ModulePhysics3D(this);
	scene = new ModuleScene(this);
	gui = new ModuleGui(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(physics);
	
	
	// Scenes
	AddModule(scene);

	AddModule(gui);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application(){

	std::list<Module*>::iterator item = modules.begin();
	for (; item != modules.end(); item = next(item))
		delete(*item);

	modules.clear();
}

bool Application::Init(){

	bool ret = true;

	// Call Init() in all modules
	std::list<Module*>::iterator item = modules.begin();

	while(item != modules.end() && ret == true)
	{
		ret = (*item)->Init();
		item = next(item);
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = modules.begin();

	while(item != modules.end() && ret == true)
	{
		ret = (*item)->Start();
		item = next(item);
	} 
	
	framerate_cap = 1000 / maxFPS;
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate(){

	frame_count++;
	
	last_sec_frame_count++;

	dt = frame_time.GetSec();

	frame_time.Start();
}

// ---------------------------------------------
void Application::FinishUpdate(){

	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}
	float avg_fps = float(frame_count) / startup_time.GetSec();
	float seconds_since_startup = startup_time.GetSec();
	uint last_frame_ms = frame_time.Read();
	uint frames_on_last_update = prev_last_sec_frame_count;

	if (last_frame_ms > 0 && last_frame_ms < framerate_cap)
		SDL_Delay(framerate_cap - last_frame_ms);

	gui->ShowFps((float)frames_on_last_update);
	gui->ShowMs((float)last_frame_ms);

}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update(){

	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	std::list<Module*>::iterator item = modules.begin();

	while(item != modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PreUpdate(dt);
		item = next(item);
	}

	item = modules.begin();

	while (item != modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->Update(dt);
		item = next(item);
	}

	item = modules.begin();

	while (item != modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = (*item)->PostUpdate(dt);
		item = next(item);
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp(){

	bool ret = true;
	std::list<Module*>::iterator item = modules.begin();


	while(item != modules.end() && ret == true){

		ret = (*item)->CleanUp();
		item = next(item);
	}
	return ret;
}

void Application::AddModule(Module* mod){
	modules.push_back(mod);


}

void Application::SetMaxFps(uint max_framerate)
{
	if (max_framerate > 0) {
		framerate_cap = 1000 / max_framerate;
	}else {
		framerate_cap = 0;
	}
		
}

uint Application::GetMaxFps() const
{
	if (framerate_cap > 0) {
		return (uint)((1.0f / (float)framerate_cap) * 1000.0f);
	}else {
		return 0;
	}
		
}

