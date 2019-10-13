#include "ModuleImporter.h"
#include "Application.h"


#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include  "Assimp/include/postprocess.h"
#include  "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

ModuleImporter::ModuleImporter(Application * app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleImporter::~ModuleImporter()
{}

bool ModuleImporter::CleanUp()
{

	return true;
}

bool ModuleImporter::Init(json file)
{
	return true;
}

bool ModuleImporter::Start()
{
	return true;
}

update_status ModuleImporter::Update(float dt)
{
	return UPDATE_CONTINUE;
}