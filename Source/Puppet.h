#pragma once
#include "Segment.h"
#include "Eye.h"


class Face : public Segment
{
	std::vector<Eye> eyes;

public:

	Face(const std::vector<Vector2>& _shape, const std::vector<Eye>& _eyes, const float& natural_frequency, const float& damping_ratio, const Transform2D& _transform) :
		Segment(_shape, natural_frequency, damping_ratio, _transform),
		eyes(_eyes)
	{}

	void update(const Segment::Input& _segment_input, const Eye::Input& _eye_input)
	{
		for (auto& eye : eyes)
		{
			eye.update(_eye_input);
		}
		Segment::update(_segment_input);
	}

	void draw(Color _color) const noexcept
	{
		Segment::draw(_color);
		for (auto& eye : eyes)
		{
			eye.draw(_color, world_point(eye.local_position()), rotation.get_value(), scale.get_value());
		}
	}
};

//class Puppet
//{
//	//std::vector<Segment> shape;
//	//std::vector<Segment> traits;
//	Face face;
//
//	//void draw_traits()
//	//{
//	//	for (auto& trait : traits)
//	//	{
//	//		trait.draw(RED);
//	//	}
//	//}
//
//	//void draw_shape()
//	//{
//
//	//}
//
//public:
//
//	void update()
//	{
//		face.update()
//	}
//
//	void draw()
//	{
//		//draw_traits();
//		face.draw();
//	}
//};