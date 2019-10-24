#ifndef __MODULEGAMEOBJECT_H__
#define __MODULEGAMEOBJECT_H__

#include <vector>
#include "Module.h"
#include <vector>

struct MeshData {

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

class GameObject {
public:
	GameObject() {};
	
	virtual ~GameObject() {};

	void Draw() const;		
	void CleanUp();

public:
	
	std::vector<MeshData*> mesh;
	uint texture = 0;	
};

#endif // __MODULEGAMEOBJECT_H__ 
