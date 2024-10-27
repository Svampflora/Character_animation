#pragma once
#include "Shapes.h"
#include "SecondOrderSystem.h"
#include <vector>
#include <optional>

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
        std::optional<Vector2> position;
        std::optional<float> rotation;
        std::optional<float> scale;
    };

    Segment(const std::vector<Vector2>& _shape, const float& natural_frequency, const float& damping_ratio, const Transform2D& _transform) noexcept :
        shape(_shape),
        position(natural_frequency, damping_ratio, _transform.position),
        rotation(natural_frequency, damping_ratio, _transform.rotation),
        scale(natural_frequency, damping_ratio, _transform.scale)
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

    Transform2D get_values() const noexcept
    {
        return { position.get_value(), rotation.get_value(), scale.get_value() };
    }
    
    virtual void update(const Input& input) noexcept
    {
        const float delta_time = GetFrameTime();

        if (input.position.has_value()) 
        {
            position.update(input.position.value(), delta_time);
        }

        if (input.rotation.has_value()) 
        {
            rotation.update(input.rotation.value(), delta_time);
        }

        if (input.scale.has_value()) 
        {
            scale.update(input.scale.value(), delta_time);
        }
    }

    virtual void draw(const Color& _color) const noexcept
    {
        std::vector<Vector2> drawable = transform_shape(shape, position.get_value(), rotation.get_value(), scale.get_value());
        DrawTriangleFan(drawable.data(), narrow_cast<int>(drawable.size()), _color);

    }

    void visualize() const noexcept
    {
        DrawCircleLines(narrow_cast<int>(position.get_value().x), narrow_cast<int>(position.get_value().y), scale.get_value(), GREEN);
        const Vector2 outer_point =
        {
            position.get_value().x + scale.get_value() * cosf(rotation.get_value()),
            position.get_value().y + scale.get_value() * sinf(rotation.get_value())
        };
        DrawLineV(position.get_value(), outer_point, GREEN);
    }

    virtual ~Segment() = default;
};

