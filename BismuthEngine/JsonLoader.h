#pragma once
#ifndef __JSONLoader_H__
#define __JSONLoader_H__

#include "Globals.h"
#include "json/json.hpp"

using json = nlohmann::json;

class JsonLoader
{
public:

	JsonLoader() {}

	~JsonLoader() {}

	json Load(const char* file) const;

	void Save(const char* file, json jsonfile);

};

#endif
