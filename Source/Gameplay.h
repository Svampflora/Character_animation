#pragma once

//#include <ranges>

#include "State.h"
#include "Resources.h"
#include "Eye.h"
#include "Segment.h"


class Play_screen : public State
{
	Eye eye_1;
	Segment segment;
	Vector2 position;

public:
	
	Play_screen();
	std::unique_ptr<State> Update() override;
	void Render() const noexcept override;
};