#pragma once
#include "World/World.h"
class Mouse
{
public:
	Mouse();
	~Mouse();

	void update(const World& world);
};
