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
	bool Init(json file);
	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	bool LoadFile(const char* path);
	void Draw();
	
public:
	vec3* Vertices = nullptr;
	uint* Indices = nullptr;
	uint VerticesID = 0; 
	uint verticesSize = 0;
	uint IndicesID = 0; 
	uint IndicesSize = 0;

};


#endif //__MODULEIMPORTER_H__
