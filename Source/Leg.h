#pragma once
#include "Segment.h"


static inline std::pair<Vector2, Vector2> intersections(const Circle& circle_1, const Circle& circle_2)
{
    const Vector2 distance_vector = circle_2.center - circle_1.center;
    const float distance = Vector2Distance(circle_1.center, circle_2.center);

    if (distance > (circle_1.radius + circle_2.radius) || distance < (circle_1.radius - circle_2.radius)) 
    {
        throw;
    }

    const float a = (circle_1.radius * circle_1.radius - circle_2.radius * circle_2.radius + distance * distance) / (2 * distance);
    const float px = circle_1.center.x + a * (distance_vector.x / distance);
    const float py = circle_1.center.y + a * (distance_vector.y / distance);
    const float h = narrow_cast<float>(sqrt(circle_1.radius * circle_1.radius - a * a));
    const float offsetX = -distance_vector.y * (h / distance);
    const float offsetY = distance_vector.x * (h / distance);
    const Vector2 point_1 = { px + offsetX, py + offsetY };
    const Vector2 point_2 = { px - offsetX, py - offsetY };

    return { point_1, point_2 };
}

class Leg : public Segment
{
    std::vector<Segment> segments;
    Vector2 target;

    float max_length() const noexcept
    {
        float total_length = 0.0f;
        for (auto& segment : segments)
        {
            total_length += segment.get_values().scale;
        }
        return total_length;
    }

    Vector2 target_vector() const noexcept
    {
        const Vector2 base_position = get_values().position;
        return target - base_position;
    }

    void set_target(const Vector2& _target) noexcept
    {
        target = _target;
    }

public:
    Leg(std::vector<Segment> _joints) : Segment(_joints[0]),
        segments(std::move(_joints)),
        target{ 0.0f, 0.0f }
    {}

    void update(const Vector2& _target) 
    {
        set_target(_target);

        if (segments.size() < 2)
        {
            return;
        }

        const Vector2 base_position = get_values().position;
        const Vector2 direction_to_target = Vector2Normalize(target_vector());
        const float distance_to_target = Vector2Length(target_vector());
        const float total_segment_length = max_length();
        const float effective_length = std::min(distance_to_target, total_segment_length);
        //effective_length = Clamp(effective_length, 0.5f * total_segment_length, effective_length);
        const Vector2 tip_position = base_position + direction_to_target * effective_length;
        
        DrawLineV(base_position, tip_position, YELLOW);
        
        std::pair<Vector2, Vector2> points;
        const float fraction = effective_length / segments.size();
        unsigned int index = 0;
        for (auto it = segments.begin(); it != segments.end(); ++it)
        {
            if (it != segments.end()-1)
            {
                points = intersections({ it->get_values().position, it->get_values().scale}, { (it + 1)->get_values().position, (it + 1)->get_values().scale});
                DrawCircleV(points.first, 10, RED);
                DrawCircleV(points.second, 10, BLUE);
            }
            const Vector2 segment_position = base_position + direction_to_target * (fraction * index);
            it->update(Segment::Input{ segment_position, std::nullopt, std::nullopt });
            index++;
        }

    }


    void draw() const noexcept
    {

        for (const auto& segment : segments)
        {
            segment.visualize();

        }
    }

};