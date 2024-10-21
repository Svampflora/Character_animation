#pragma once

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#include "raymath.h"
#pragma warning(pop)
#include <utility>

static inline float GetScreenWidthF() noexcept
{
	return static_cast<float>(GetScreenWidth());
}

static inline float GetScreenHeightF() noexcept
{
	return static_cast<float>(GetScreenHeight());
}

static inline float GetRandomValueF(int min, int max) noexcept
{
	return static_cast<float>(GetRandomValue(min, max));
}

inline Vector2 operator+(const Vector2& a, const Vector2& b)  noexcept
{
    return { a.x + b.x, a.y + b.y };
}

inline Vector2 operator += ( Vector2& a, const Vector2& b) noexcept
{
    a = a + b;
    return a;
}

inline Vector2 operator-(const Vector2& a, const Vector2& b)  noexcept
{
    return { a.x - b.x, a.y - b.y };
}

inline Vector2 operator*(const Vector2& a, const Vector2& b) noexcept
{
    return { a.x * b.x, a.y * b.y };
}

inline Vector2 operator*(const Vector2& vec, float scalar) noexcept
{
    return { vec.x * scalar, vec.y * scalar };
}

inline Vector2 operator*(float scalar, const Vector2& vec) noexcept
{
    return { vec.x * scalar, vec.y * scalar };
}

inline Vector2 operator *= (Vector2& a, const Vector2& b) noexcept
{
    a = a * b;
    return a;

}

inline Vector2 operator *= (Vector2& a, const float& b) noexcept
{
    a = a * b;
    return a;

}

static inline Vector2 rotate_point(const Vector2& point, const float angle) noexcept
{
    return 
    {
        point.x * cosf(angle) - point.y * sinf(angle),
        point.x * sinf(angle) + point.y * cosf(angle)
    };
}


static inline void DrawCircleF(float centerX, float centerY, float radius, Color color ) noexcept
{
	DrawCircle(static_cast<int>(centerX), static_cast<int>(centerY), radius, color);
}

static inline void DrawTextF(const char* text, float posX, float posY, int fontSize, Color color) noexcept
{
	DrawText(text, static_cast<int>(posX), static_cast<int>(posY), fontSize, color);
}

template <typename T, typename U>
inline T narrow_cast(U&& u) noexcept
{
	return static_cast<T>(std::forward<U>(u));
}

typedef struct Vector2i {
	int x;                
	int y;                
} Vector2i;

typedef struct Circle {
	Vector2 center;
	float radius;
} Circle;

//typedef struct Transform {
//    Vector2 position = {0.0f, 0.0f};
//    float rotation = 0.0f;
//    float scale = 1.0f;
//} Transform;

static inline float half_chord_length(const Circle _circle, const float _distance) noexcept
{
    return sqrtf((_circle.radius * _circle.radius) - (_distance * _distance));
}

static constexpr inline float to_radians(float _degrees) noexcept
{
    return _degrees / 180 * PI;
}

static inline Vector2 UnitCircularOffset(Vector2 _vector) 
{
    const float magnitude = Vector2Length(_vector);
    if (magnitude == 0.0f)
    {
        return { 0.0f , 0.0f };
    }
    const Vector2 normalized = Vector2Normalize(_vector);
    return Vector2Multiply(normalized, Vector2One());
}

static inline bool Vector2Same(Vector2 v1, Vector2 v2) noexcept
{
    if (v1.x == v2.x && v1.y == v2.y)
    {
        return true;
    }
    return false;
}

// NOTE: Gamepad name ID depends on drivers and OS
#define XBOX360_LEGACY_NAME_ID  "Xbox Controller"
#define XBOX360_NAME_ID     "Xbox 360 Controller"
#define PS3_NAME_ID         "Sony PLAYSTATION(R)3 Controller"

typedef struct GamePad 
{
    Vector2 right_stick{0.0f, 0.0f};
    Vector2 left_stick{ 0.0f, 0.0f };
    bool A{ 0.0f};
    bool B{ 0.0f };
    bool X{ 0.0f};
    bool Y{ 0.0f };
    bool left{ 0.0f };
    bool right{ 0.0f };
    bool up{ 0.0f };
    bool down{ 0.0f };
    bool home{ 0.0f };
    bool start{ 0.0f };
    bool select{ 0.0f };
    bool left_trigger{ 0.0f };
    bool right_trigger{ 0.0f };
    bool left_stick_button{ 0.0f };
    bool right_stick_button{ 0.0f };
    bool left_shoulder{ 0.0f };
    bool right_shoulder{ 0.0f };


    GamePad(const int gamepad_nr)
    {
        if (IsGamepadAvailable(gamepad_nr))
        {
            if (TextIsEqual(GetGamepadName(gamepad_nr), XBOX360_LEGACY_NAME_ID) || 
                TextIsEqual(GetGamepadName(gamepad_nr), XBOX360_NAME_ID) || 
                TextIsEqual(GetGamepadName(gamepad_nr), PS3_NAME_ID))
            {

                home = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_MIDDLE);
                start = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_MIDDLE_RIGHT);
                select = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_MIDDLE_LEFT);
                X = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
                A = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
                B = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
                Y = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_RIGHT_FACE_UP);
                up = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_LEFT_FACE_UP);
                down = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
                left = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
                right = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
                right_stick = { GetGamepadAxisMovement(gamepad_nr, GAMEPAD_AXIS_RIGHT_X), GetGamepadAxisMovement(gamepad_nr, GAMEPAD_AXIS_RIGHT_Y) };
                left_stick = { GetGamepadAxisMovement(gamepad_nr, GAMEPAD_AXIS_LEFT_X), GetGamepadAxisMovement(gamepad_nr, GAMEPAD_AXIS_LEFT_Y) };
                left_trigger = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_LEFT_TRIGGER_1);
                right_trigger = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
                left_stick_button = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_LEFT_THUMB);
                right_stick_button = IsGamepadButtonDown(gamepad_nr, GAMEPAD_BUTTON_RIGHT_THUMB);
                left_shoulder = GetGamepadAxisMovement(gamepad_nr, GAMEPAD_AXIS_LEFT_TRIGGER);
                right_shoulder = GetGamepadAxisMovement(gamepad_nr, GAMEPAD_AXIS_RIGHT_TRIGGER);

            }

            //GetGamepadButtonPressed() != GAMEPAD_BUTTON_UNKNOWN
        }
        else
        {
            throw;
        }
    }

} Controller;

