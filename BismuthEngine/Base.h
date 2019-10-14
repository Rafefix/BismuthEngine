#pragma once
#ifndef __BASE_H__
#define __BASE_H__

#include "Globals.h"

class Resources
{
public:
	enum class RType { none = 0, mesh };

public:

	Resources(Resources::RType type);
	virtual ~Resources();

};

#endif