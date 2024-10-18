#pragma once

#include "State.h"
#include "Puppet.h"



class Play_screen : public State
{
	//Eye eye_1;
	//Segment segment;
	Vector2 position;
	std::vector<Face> face;

public:
	
	Play_screen();
	std::unique_ptr<State> Update() override;
	void Render() const noexcept override;
};