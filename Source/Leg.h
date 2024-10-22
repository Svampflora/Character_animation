#pragma once
#include "Segment.h"

class Leg : public Segment
{
	std::vector<Segment> joints;

public: 

	Leg()
	{
	};
};