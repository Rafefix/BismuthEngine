#ifndef __MODULEIMPORTER_H__
#define __MODULEIMPORTER_H__

#include "Module.h"
#include <vector>

struct MeshIndexes {

	uint id_index = 0;
	uint num_indices = 0;
	uint* indices = nullptr;
	uint id_vertex = 0;
	uint num_vertices = 0;
	float* vertices = nullptr;
	uint id_texture = 0;
	uint num_texture = 0;
	float* textures = nullptr;
};

struct Mesh {

	std::vector<MeshIndexes*> mesh;
	uint texture = 0;
};

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
	void Draw(Mesh fbx_mesh);
	uint GetTexture(const char* path);

public:

	std::vector<Mesh> MeshArray;
	uint texture;

};


#endif //__MODULEIMPORTER_H__