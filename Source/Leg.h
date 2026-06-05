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

    float effective_length() const
    {
        const float distance_to_target = Vector2Length(target_vector());
        const float total_segment_length = max_length();
        return std::min(distance_to_target, total_segment_length);
    }

    void set_target(const Vector2& _target) noexcept
    {
        target = _target;
    }

public:
    Leg(std::vector<Segment> _joints) : Segment(_joints[0]),
        segments(std::move(_joints)),
        target{ 0.0f, 0.0f }
    {
        segments.begin()->update(Segment::Input{ std::nullopt, std::nullopt, 2.0f * segments.begin()->get_values().scale });
        segments.rbegin()->update(Segment::Input{ std::nullopt, std::nullopt, 2.0f * segments.rbegin()->get_values().scale });
    }


    void update(const Vector2& _target) 
    {
        set_target(_target);

        if (segments.size() < 2)
        {
            return;
        }
        const Vector2 base_position = get_values().position;
        const Vector2 direction_to_target = Vector2Normalize(target_vector());
        const float effective_distance = effective_length();
        const float fraction = effective_distance / (segments.size() - 1);
        unsigned int index = 0;
        for (auto it = segments.begin(); it != segments.end(); ++it)
        {
            const Vector2 segment_position = base_position + direction_to_target * (fraction * index);
            it->update(Segment::Input{ segment_position, std::nullopt, std::nullopt });
            index++;
        }
    }


    void draw() const
    {

        const Vector2 base_position = get_values().position;
        const Vector2 direction_to_target = Vector2Normalize(target_vector());
        const Vector2 tip_position = base_position + direction_to_target * effective_length();

        std::pair<Vector2, Vector2> points_to_previous;
        std::pair<Vector2, Vector2> points_to_next;

        //DrawLineV(base_position, tip_position, YELLOW);
        for (auto it = segments.begin(); it != segments.end(); ++it)
        {
            it->visualize();
            if (it == segments.begin())
            {
                points_to_next = intersections({ it->get_values().position, it->get_values().scale }, { (it + 1)->get_values().position, (it + 1)->get_values().scale });
                DrawLineEx(it->get_values().position, points_to_next.second, 20, GREEN);
            }
            else if (it == segments.end() - 1)
            {
                points_to_previous = intersections({ it->get_values().position, it->get_values().scale }, { (it - 1)->get_values().position, (it - 1)->get_values().scale });
                DrawLineEx(it->get_values().position, points_to_previous.second,10, GREEN);
            }
            else
            {
                points_to_previous = intersections({ it->get_values().position, it->get_values().scale }, { (it - 1)->get_values().position, (it - 1)->get_values().scale });
                points_to_next = intersections({ it->get_values().position, it->get_values().scale }, { (it + 1)->get_values().position, (it + 1)->get_values().scale });
                DrawLineEx(points_to_previous.first, points_to_next.first, 15, GREEN);
            }
        }
    }
};