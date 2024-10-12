#pragma once


#include "Utilities.h"


class Eye
{
	Circle sclera;
	Circle iris;

	float max_travel_length() noexcept
	{
		return sclera.radius - iris.radius;
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

	bool within_boundry() noexcept
	{
		if (CheckCollisionPointCircle(iris.center, sclera.center, max_travel_length()))
		{
			return true;
		}
		return false;
	}

public:
	Eye(const Vector2 _position, const float _size) noexcept
	{
		sclera = { _position, _size };
		iris = { _position, 0.5f * _size };
	}
	void update(const Vector2 _position, const Vector2 _input)
	{
		eye_positioning(_position);
		if (Vector2Same(_input, Vector2Zero()))
		{
			look_direction(Vector2Zero());
		}
		else
		{
			look_direction(_input);
		}
	}
	void draw() const noexcept
	{
		DrawCircleV(sclera.center, sclera.radius, WHITE);
		DrawCircleV(iris.center, iris.radius, BLACK);
	};
};