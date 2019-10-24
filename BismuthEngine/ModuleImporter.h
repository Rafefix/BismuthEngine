#ifndef __MODULEIMPORTER_H__
#define __MODULEIMPORTER_H__

#include "Module.h"
#include <vector>
#include "GameObject.h"

// ---------------------------------------------------
class ModuleImporter : public Module
{
public:

	ModuleImporter(Application* app, bool start_enabled = true);
	virtual ~ModuleImporter();

	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void LoadFile(const char* path, uint tex = 0);
	uint GetTexture(const char* path);
	GameObject* CreateGameObject();
public:
	uint texture;
	bool loadedAll = false;
	
};


#endif //__MODULEIMPORTER_H__