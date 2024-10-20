#pragma once
#include "Shapes.h"
#include "SecondOrderSystem.h"
#include <vector>

class Segment 
{
    std::vector<Vector2> shape;
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

    Segment(const std::vector<Vector2>& _shape, const float& natural_frequency, const float& damping_ratio, 
                        const Vector2& _position, const float& _rotation = 0.0f, const float& _scale = 1.0f) noexcept :
        shape(_shape),
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

    void draw(const Color& _color) const noexcept
    {
        std::vector<Vector2> drawable = transform_shape(shape, position.get_value(), rotation.get_value(), scale.get_value());
        DrawTriangleFan(drawable.data(), narrow_cast<int>(drawable.size()), _color);

    }
};

