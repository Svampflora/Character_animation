#include "Eye.h"

float Eye::max_travel_length() const noexcept
{
	return sclera.radius - iris.radius;
}

bool Eye::within_boundry() noexcept
{
	if (CheckCollisionPointCircle(iris.center, sclera.center, max_travel_length()))
	{
		return true;
	}
	return false;
}

void Eye::look_direction(const Vector2& _input)
{
	const float max_speed = sclera.radius * 3.0f;
	const Vector2 offset = Vector2Multiply({ max_travel_length(), max_travel_length() }, UnitCircularOffset(_input));
	const Vector2 target = Vector2Add(sclera.center, offset);

	const float distance_to_target = Vector2Distance(iris.center, target);

	const float easing_factor = distance_to_target / max_travel_length();
	const float current_speed = max_speed * easing_factor;

	iris.center = Vector2MoveTowards(iris.center, target, current_speed * GetFrameTime());
}

void Eye::blink(float _target_factor) noexcept
{
	const float max_speed = sclera.radius * 10.0f;
	const float distance_to_target = _target_factor - lid_factor;
	const float easing_factor = distance_to_target / sclera.radius;
	const float current_speed = max_speed * easing_factor;

	lid_factor += current_speed * GetFrameTime();
}

Eye::Eye(const Vector2& _position, const float& _size) noexcept
{
	sclera = { _position, _size };
	iris = { _position, 0.5f * _size };
	lid_factor = 0.0f;
}

void Eye::update(const Input& _input)
{
	if (Vector2Same(_input.direction, Vector2Zero()))
	{
		look_direction(Vector2Zero());
	}
	else
	{
		look_direction(_input.direction);
	}

	if (_input.blinking)
	{
		blink(0);
	}
	else
	{
		blink(0.5f);
	}
}

void Eye::draw(const Color& _color, const Vector2& _position, const float& _rotation, const float& _scale) const noexcept
{
	const Circle scaled_sclera{ _position, sclera.radius * _scale };
	const Vector2 offset = Vector2Subtract(iris.center * _scale, sclera.center * _scale);

	DrawCircleV(scaled_sclera.center, scaled_sclera.radius, WHITE);
	DrawCircleV(Vector2Add(scaled_sclera.center, offset), iris.radius * _scale, BLACK);

	std::vector<Vector2> lid = eye_lids(Circle{ {0.0f,0.0f},sclera.radius }, lid_factor, 64);
	lid = transform_shape(lid, _position, _rotation, _scale);
	DrawTriangleStrip(lid.data(), narrow_cast<int>(lid.size()), _color);

}

Vector2 Eye::local_position() const noexcept
{
	return sclera.center;
};
