#pragma once
#include "Utilities.h"
#include "SecondOrderSystem.h"

class Segment 
{
    SecondOrderSystem<Vector2> position;
    SecondOrderSystem<float> rotation;
    SecondOrderSystem<float> scale;

public://TODO: maybe inject Second order for more controll
    Segment(const float natural_frequency, const float damping_ratio, const Vector2 _position, const float _rotation = 0.0f, const float _scale = 1.0f) noexcept : 
        position(natural_frequency, damping_ratio, _position),
        rotation(natural_frequency, damping_ratio, _rotation),
        scale(natural_frequency, damping_ratio, _scale)
    {}

    void update(const Vector2& _position, const float& _rotation, const float& _scale) noexcept
    {
        const float delta_time = GetFrameTime();
        position.update(_position, delta_time);
        rotation.update(_rotation, delta_time);
        scale.update(_scale, delta_time);
    }

    void draw(const Color color) const
    {
        std::vector<Vector2> e = epicycloid({ position.get_value(), 100.0f}, 3, 64);
        e = transform_shape(e, e.front(), scale.get_value(), to_radians(rotation.get_value()));
        DrawTriangleFan(e.data(), narrow_cast<int>(e.size()), color);
    }
};