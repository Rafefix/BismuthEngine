#ifndef __MODULEIMPORTER_H__
#define __MODULEIMPORTER_H__

#include "Globals.h"
#include "Module.h"
#include "Math.h"
#include "glmath.h"

class Meshes;

class ModuleImporter : public Module
{
public:
	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();

public:
	bool Init(json file);
	bool Start();
	bool CleanUp();
	bool LoadFile(const char* path);
	void Draw();

public:
	std::vector<Meshes*> meshes;
	
};


#endif //__MODULEIMPORTER_H__