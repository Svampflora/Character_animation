#pragma once

#include "Utilities.h"
#include "Shapes.h"
#include <array>



static inline std::vector<Vector2> eye_lid(const Circle _eye, const float _lid_shut_factor, const int _resolution)
{
	const int points_per_circle = _resolution;
	const float outer_radius = _eye.radius;

	std::vector<Vector2> crescent_strip;
	
	const float angle_increment = (2 * PI) / points_per_circle;

	for (int i = 0; i <= points_per_circle; ++i)
	{
		const float angle = i * angle_increment;

		const Vector2 outer_point = {
			_eye.center.x + outer_radius * cosf(angle),
			_eye.center.y + outer_radius * sinf(angle)
		};

		const float inner_radius = half_chord_length(_eye, outer_point.x - _eye.center.x) * _lid_shut_factor;
		const Vector2 inner_point = {
			_eye.center.x + outer_radius * cosf(angle),
			_eye.center.y + inner_radius * sinf(angle)
		};

		crescent_strip.push_back(outer_point);
		crescent_strip.push_back(inner_point);
	}

	return crescent_strip;
}

class Eye
{
	Circle sclera;
	Circle iris;
	float lid_factor;
	

	float max_travel_length() noexcept
	{
		return sclera.radius - iris.radius;
	}
	bool within_boundry() noexcept
	{
		if (CheckCollisionPointCircle(iris.center, sclera.center, max_travel_length()))
		{
			return true;
		}
		return false;
	}
	void eye_positioning(const Vector2 _position)
	{
		const Vector2 offset = Vector2Subtract(iris.center, sclera.center);
		sclera.center = _position;
		iris.center = Vector2Add(sclera.center, offset);
	}
	void look_direction(const Vector2 _input)
	{
		const float max_speed = sclera.radius * 3.0f;
		const Vector2 offset = Vector2Multiply({ max_travel_length(), max_travel_length() }, UnitCircularOffset(_input));
		const Vector2 target = Vector2Add(sclera.center, offset);

		const float distance_to_target = Vector2Distance(iris.center, target);

		const float easing_factor = distance_to_target / max_travel_length();
		const float current_speed = max_speed * easing_factor;

		iris.center = Vector2MoveTowards(iris.center, target, current_speed * GetFrameTime());
	}
	void blink(float _target_factor) noexcept
	{
		const float max_speed = sclera.radius * 10.0f;
		const float distance_to_target = _target_factor - lid_factor;
		const float easing_factor = distance_to_target / sclera.radius;
		const float current_speed = max_speed * easing_factor;

		lid_factor += current_speed * GetFrameTime();
	}

public:
	Eye(const Vector2 _position, const float _size) noexcept
	{
		sclera = { _position, _size };
		iris = { _position, 0.5f * _size };
		lid_factor = 0.0f;
	}
	void update(const Vector2 _position, const Vector2 _direction, const bool _blink)
	{
		eye_positioning(_position);
		if (Vector2Same(_direction, Vector2Zero()))
		{
			look_direction(Vector2Zero());
		}
		else
		{
			look_direction(_direction);
		}

		if (_blink)
		{
			blink(0);
		}
		else
		{
			blink(0.5f);
		}
	}
	void draw() const
	{

		DrawCircleV(sclera.center, sclera.radius, WHITE);
		DrawCircleV(iris.center, iris.radius, BLACK);


		std::vector<Vector2> lid = eye_lid(sclera, lid_factor, 64);
		DrawTriangleStrip(lid.data(), narrow_cast<int>(lid.size()), DARKPURPLE);
	};
};