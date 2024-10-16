#pragma once

template<typename T>
class SecondOrderSystem 
{
    const float omega;
    const float zeta;
    T value;     
    T velocity;     

public:
    
    SecondOrderSystem(const float natural_frequency, const float damping_ratio, T initial_value) noexcept :
        omega(natural_frequency), 
        zeta(damping_ratio), 
        value(initial_value), 
        velocity(T{})  // possible to add initial responce rate "r" = initial_velocity
    {}

    void update(T target, float deltaTime) noexcept
    {
        T acceleration = omega * omega * (target - value) - 2 * zeta * omega * velocity;

        velocity += acceleration * deltaTime;
        value += velocity * deltaTime;
    }

    T get_value() const noexcept
    {
        return value;
    }
};
