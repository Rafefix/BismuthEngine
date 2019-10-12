#include "JsonLoader.h"
#include <fstream>
#include <iomanip>

json JsonLoader::Load(const char * file) const
{
	json JsonFile;
	
	if (file == nullptr) {
		LOG("JsonLoader: %c was nullptr", file);
	}
	else
	{
		std::ifstream load;
		load.open(file);
		if (load.is_open()) {

			try
			{
				JsonFile = json::parse(load);
			}
			catch (json::parse_error& error)
			{
				LOG("Parse Error in loading file: %c", error.what());
			}

			load.close();
		}
		else
			LOG("JsonLoader: load %c couldn't open", file);

	}


	return json();
}

void JsonLoader::Save(const char * file, json jsonfile)
{

	std::ofstream save;

	save.open(file);

	if (save.is_open()) {

		save << std::setw(4) << jsonfile << std::endl;
		save.close();

	}
	else
		LOG("JsonLoader: save %c couldn't open", file);

}
