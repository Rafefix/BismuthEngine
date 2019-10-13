#ifndef __MODULEIMPORTER_H__
#define __MODULEIMPORTER_H__

#include "Globals.h"
#include "Module.h"

class ModuleImporter : public Module
{
public:
	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();

public:
	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();



public:
};


#endif //__MODULEIMPORTER_H__
