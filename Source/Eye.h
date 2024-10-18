#pragma once
#include "Utilities.h"
#include "Shapes.h"


class Eye
{

	Circle sclera;
	Circle iris;
	float lid_factor;
	

	float max_travel_length() const noexcept;
	bool within_boundry() noexcept;
	void look_direction(const Vector2& _input);
	void blink(float _target_factor) noexcept;

public:
	struct Input
	{
		Vector2 direction;
		bool blinking;
	};

	Eye(const Vector2& _local_offset, const float& _size) noexcept;
	void update(const Input& _input);
	void draw(const Color& _color, const Vector2& _position, const float& _rotation, const float& _scale) const;
	Vector2 local_offset() const noexcept;
};