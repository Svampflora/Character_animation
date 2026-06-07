#pragma once

#include "State.h"
#include "Puppet.h"
#include "Leg.h"




class Play_screen : public State
{
	Camera3D			camera;
	Point_volume		point_volume;
	PointCloudMesh		mesh;
	PointCloudRenderer	renderer;
	//Vector2 position;
	//std::vector<Face> face;

public:
	
	Play_screen();
	std::unique_ptr<State> Update() override;
	void Render() const noexcept override;
};