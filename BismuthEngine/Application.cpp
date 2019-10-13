#include "Application.h"

Application::Application(){

	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
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
	
	
	
	// Scenes
	AddModule(scene);
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======

	AddModule(gui);
>>>>>>> parent of c7a45f4... Importer finished

>>>>>>> parent of c7a45f4... Importer finished
	AddModule(gui);
	AddModule(imp);
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
	json file = jsonLoader.Load("File.json");
	std::list<Module*>::iterator item = modules.begin();
	
	while(item != modules.end() && ret == true)
	{
		ret = (*item)->Init(file);
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
	
	frame_time.Start();

	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate(){

	frame_count++;
	
	last_sec_frame_count++;

	dt = (float)frame_time.GetSec();

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

	fps_vec.push_back(prev_last_sec_frame_count);
	if (fps_vec.size() > HISTOGRAM_BARS)
		fps_vec.erase(fps_vec.begin());


	ms_vec.push_back(last_frame_ms);
	if (ms_vec.size() > HISTOGRAM_BARS){ 
		ms_vec.erase(ms_vec.begin());
	}
		

	if (maxFps > 0){
		capped_ms = 1000 / maxFps;
	}else{
		capped_ms = 0;
	}
		

	if (capped_ms > 0 && last_frame_ms < capped_ms){
		SDL_Delay(capped_ms - last_frame_ms);
	}
		

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

