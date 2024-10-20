#pragma once
#include <vector>
#include "Utilities.h"

static inline std::vector<Vector2> eye_lids(const Circle& _eye, const float& _lid_shut_factor, const int& _resolution)
{
	const int points_per_circle = _resolution;
	const float outer_radius = _eye.radius * 1.001f;

	std::vector<Vector2> strip;

	const float angle_increment = (2 * PI) / points_per_circle;

	for (int i = 0; i <= points_per_circle; ++i)
	{
		const float angle = i * angle_increment;

		const Vector2 outer_point =
		{
			_eye.center.x + outer_radius * cosf(angle),
			_eye.center.y + outer_radius * sinf(angle)
		};

		const float inner_radius = half_chord_length(_eye, outer_point.x - _eye.center.x) * _lid_shut_factor;
		const Vector2 inner_point =
		{
			_eye.center.x + outer_radius * cosf(angle),
			_eye.center.y + inner_radius * sinf(angle)
		};

		strip.push_back(outer_point);
		strip.push_back(inner_point);
	}

	return strip;
}

static inline std::vector<Vector2> eye_lid(const Circle& _eye, const float& _lid_shut_factor, const int& _resolution) noexcept
{
	std::vector<Vector2> strip;

	const float angle_increment = (PI) / _resolution;

	for (int i = 0; i <= _resolution; ++i)
	{
		const float angle = i * angle_increment;

		const Vector2 outer_point =
		{
			_eye.center.x + _eye.radius * cosf(angle),
			_eye.center.y + _eye.radius * sinf(angle)
		};

		const float inner_radius = half_chord_length(_eye, outer_point.x - _eye.center.x) * _lid_shut_factor;
		const Vector2 inner_point =
		{
			_eye.center.x + _eye.radius * cosf(angle),
			_eye.center.y + inner_radius * sinf(angle)
		};

		strip.push_back(outer_point);
		strip.push_back(inner_point);
	}

	return strip;
}

static inline std::vector<Vector2> cat_pupil(const Circle& _pupil, const float& _shut_factor, const int& _resolution)
{
	std::vector<Vector2> fan;
	fan.reserve(_resolution);
	fan.emplace_back(_pupil.center);
	const float angle_increment = -(2 * PI) / (_resolution - 2);

	for (int i = 1; i <= _resolution - 1; ++i) 
	{
		const float angle = angle_increment * i;


		float y = _pupil.center.y + _pupil.radius * sinf(angle);
		const float width = half_chord_length(_pupil, y - _pupil.center.y) * _shut_factor;
		float x = _pupil.center.x + width * cosf(angle);

		fan.emplace_back(x, y);
	}

 	return fan;
}

static inline std::vector<Vector2> crescent(const Circle& _circle, const float& _phase_factor, const int& _resolution)
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
		const Vector2 inner_point = 
		{
			_circle.center.x + _circle.radius * cosf(angle),
			_circle.center.y + thickness
		};

		strip.emplace_back(outer_point);
		strip.emplace_back(inner_point);
	}

	return strip;
}

static inline std::vector<Vector2> epicycloid(const Circle& _circle, const int& _cusps, const int& _resolution) noexcept
{
	std::vector<Vector2> fan;
	fan.reserve(_resolution);
	fan.emplace_back(_circle.center);
	const float angle_increment = -(2 * PI) / (_resolution - 2);

	const float R = _circle.radius;
	const float r = R / _cusps;

	for (int i = 1; i < _resolution; ++i)
	{
		const float theta = angle_increment * i;

		const float x = (_circle.center.x + (R + r) * cosf(theta)) - (r * cosf((R + r) / r * theta));
		const float y = (_circle.center.y + (R + r) * sinf(theta)) - (r * sinf((R + r) / r * theta));

		fan.emplace_back(x, y);
	}

	return fan;
}

static inline std::vector<Vector2> transform_shape(const std::vector<Vector2>& _points, const Vector2& _position, float _rotation, float _scale) noexcept
{
	std::vector<Vector2> transformed_points;
	transformed_points.reserve(_points.size());

	for (const auto& point : _points)
	{
		const Vector2 scaled_point = point * _scale;
		const Vector2 rotated_point = rotate_point(scaled_point, _rotation);
		transformed_points.emplace_back(rotated_point + _position);
	}

	return transformed_points;
}


