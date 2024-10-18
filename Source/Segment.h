#pragma once
#include "Shapes.h"
#include "SecondOrderSystem.h"
#include <vector>

class Segment 
{
protected:
    SecondOrderSystem<Vector2> position;
    SecondOrderSystem<float> rotation;
    SecondOrderSystem<float> scale;

public://TODO: inject the SecondOrderSystems for more controll

    struct Input
    {
        const Vector2 position;
        const float rotation;
        const float scale;
    };

    Segment(const float natural_frequency, const float damping_ratio, const Vector2 _position, const float _rotation = 0.0f, const float _scale = 1.0f) noexcept : 
        position(natural_frequency, damping_ratio, _position),
        rotation(natural_frequency, damping_ratio, _rotation),
        scale(natural_frequency, damping_ratio, _scale)
    {}

    Vector2 world_point(const Vector2& local_point) const noexcept
    {
        const Vector2 current_position = position.get_value();
        const float current_rotation = rotation.get_value();
        const float current_scale = scale.get_value();

        const Vector2 transformed_point = local_point * current_scale;
        const Vector2 rotated = rotate_point(transformed_point, current_rotation);
        return current_position + rotated;
    }
    
    void update(const Input& input) noexcept
    {
        const float delta_time = GetFrameTime();
        position.update(input.position, delta_time);
        rotation.update(input.rotation, delta_time);
        scale.update(input.scale, delta_time);
    }

    void draw(const Color& _color) const noexcept//TODO: inject fan shape
    {
        std::vector<Vector2> e = epicycloid({ position.get_value(), 100.0f }, 2, 64);
        e = transform_shape(e, e.front(), rotation.get_value(), scale.get_value() );
        DrawTriangleFan(e.data(), narrow_cast<int>(e.size()), _color);

        //DrawCircleV(world_point({ 0.0f, 50.0f }), scale.get_value(), GREEN);
        //DrawTriangle(world_point({ 0.0f, 0.0f }), world_point({ -50.0f, 100.0f }), world_point({ 50.0f, 100.0f }), YELLOW);
    }
};

