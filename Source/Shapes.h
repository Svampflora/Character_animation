#pragma once
#include <vector>
#include "Utilities.h"

static inline std::vector<Vector2> cat_pupil(const Circle _pupil, const float _shut_factor, const int _resolution)
{
	std::vector<Vector2> fan;
	fan.reserve(_resolution);
	fan.emplace_back(_pupil.center);
	const float angle_increment = -(2 * PI) / (_resolution - 2);

	for (size_t i = 1; i <= _resolution - 1; ++i) 
	{
		const float angle = angle_increment * i;


		float y = _pupil.center.y + _pupil.radius * sinf(angle);
		const float width = half_chord_length(_pupil, y - _pupil.center.y) * _shut_factor;
		float x = _pupil.center.x + width * cosf(angle);

		fan.emplace_back(x, y);
	}

 	return fan;
}

static inline std::vector<Vector2> crescent(const Circle _circle, const float _phase_factor, const int _resolution)
{
	std::vector<Vector2> strip;
	strip.reserve(_resolution * 2);
	strip.emplace_back(_circle.center);
	const float angle_increment = - PI / _resolution;

	for (int i = 0; i <= _resolution; ++i)
	{
		const float angle = i * angle_increment;

		const Vector2 outer_point = 
		{
			_circle.center.x + _circle.radius * cosf(angle),
			_circle.center.y + _circle.radius * sinf(angle)
		};

		const float thickness = half_chord_length(_circle, outer_point.x - _circle.center.x) * _phase_factor;
		const Vector2 inner_point = {
			_circle.center.x + _circle.radius * cosf(angle),
			_circle.center.y + thickness
		};

		strip.emplace_back(outer_point);
		strip.emplace_back(inner_point);
	}

	return strip;
}

static inline std::vector<Vector2> epicycloid(const Circle _circle, const int _cusps, const int _resolution)
{
	std::vector<Vector2> fan;
	fan.reserve(_resolution);
	fan.emplace_back(_circle.center);
	const float angle_increment = -(2 * PI) / (_resolution - 2);

	const float R = _circle.radius;
	const float r = R / _cusps;

	for (size_t i = 1; i < _resolution; ++i)
	{
		const float theta = angle_increment * i;

		const float x = (_circle.center.x + (R + r) * cosf(theta)) - (r * cosf((R + r) / r * theta));
		const float y = (_circle.center.y + (R + r) * sinf(theta)) - (r * sinf((R + r) / r * theta));

		fan.emplace_back(x, y);
	}

	return fan;
}

static inline std::vector<Vector2> transform_shape(std::vector<Vector2> _points, const Vector2 _center, const float _scale, const float _angle) noexcept
{
	for (auto& point : _points)
	{
		float x = point.x - _center.x;
		float y = point.y - _center.y;

		x *= _scale;
		y *= _scale;

		const float rotated_x = x * cosf(_angle) - y * sinf(_angle);
		const float rotated_y = x * sinf(_angle) + y * cosf(_angle);

		point.x = _center.x + rotated_x;
		point.y = _center.y + rotated_y;
	}

	return _points;
}
