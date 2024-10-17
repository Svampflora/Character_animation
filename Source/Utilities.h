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
static inline void raylib_example(int gamepad)
{
    
    if (IsKeyPressed(KEY_LEFT) && gamepad > 0) gamepad--;
    if (IsKeyPressed(KEY_RIGHT)) gamepad++;

    if (IsGamepadAvailable(gamepad))
    {
        DrawText(TextFormat("GP%d: %s", gamepad, GetGamepadName(gamepad)), 10, 10, 10, BLACK);

        if (TextIsEqual(GetGamepadName(gamepad), XBOX360_LEGACY_NAME_ID) || TextIsEqual(GetGamepadName(gamepad), XBOX360_NAME_ID))
        {
            //DrawTexture(texXboxPad, 0, 0, DARKGRAY);

            // Draw buttons: xbox home
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE)) DrawCircle(394, 89, 19, RED);

            // Draw buttons: basic
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT)) DrawCircle(436, 150, 9, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_LEFT)) DrawCircle(352, 150, 9, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) DrawCircle(501, 151, 15, BLUE);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) DrawCircle(536, 187, 15, LIME);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) DrawCircle(572, 151, 15, MAROON);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP)) DrawCircle(536, 115, 15, GOLD);

            // Draw buttons: d-pad
            DrawRectangle(317, 202, 19, 71, BLACK);
            DrawRectangle(293, 228, 69, 19, BLACK);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) DrawRectangle(317, 202, 19, 26, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) DrawRectangle(317, 202 + 45, 19, 26, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) DrawRectangle(292, 228, 25, 19, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) DrawRectangle(292 + 44, 228, 26, 19, RED);

            // Draw buttons: left-right back
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) DrawCircle(259, 61, 20, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) DrawCircle(536, 61, 20, RED);

            // Draw axis: left joystick

            Color leftGamepadColor = BLACK;
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_THUMB)) leftGamepadColor = RED;
            DrawCircle(259, 152, 39, BLACK);
            DrawCircle(259, 152, 34, LIGHTGRAY);
            DrawCircle(259 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) * 20),
                152 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) * 20), 25, leftGamepadColor);

            // Draw axis: right joystick
            Color rightGamepadColor = BLACK;
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_THUMB)) rightGamepadColor = RED;
            DrawCircle(461, 237, 38, BLACK);
            DrawCircle(461, 237, 33, LIGHTGRAY);
            DrawCircle(461 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) * 20),
                237 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) * 20), 25, rightGamepadColor);

            // Draw axis: left-right triggers
            DrawRectangle(170, 30, 15, 70, GRAY);
            DrawRectangle(604, 30, 15, 70, GRAY);
            DrawRectangle(170, 30, 15, (int)(((1 + GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER)) / 2) * 70), RED);
            DrawRectangle(604, 30, 15, (int)(((1 + GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER)) / 2) * 70), RED);

            //DrawText(TextFormat("Xbox axis LT: %02.02f", GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER)), 10, 40, 10, BLACK);
            //DrawText(TextFormat("Xbox axis RT: %02.02f", GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER)), 10, 60, 10, BLACK);
        }
        else if (TextIsEqual(GetGamepadName(gamepad), PS3_NAME_ID))
        {
            //DrawTexture(texPs3Pad, 0, 0, DARKGRAY);

            // Draw buttons: ps
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE)) DrawCircle(396, 222, 13, RED);

            // Draw buttons: basic
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_LEFT)) DrawRectangle(328, 170, 32, 13, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT)) DrawTriangle({ 436, 168 }, { 436, 185 },{ 464, 177 }, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP)) DrawCircle(557, 144, 13, LIME);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) DrawCircle(586, 173, 13, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) DrawCircle(557, 203, 13, VIOLET);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) DrawCircle(527, 173, 13, PINK);

            // Draw buttons: d-pad
            DrawRectangle(225, 132, 24, 84, BLACK);
            DrawRectangle(195, 161, 84, 25, BLACK);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) DrawRectangle(225, 132, 24, 29, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) DrawRectangle(225, 132 + 54, 24, 30, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) DrawRectangle(195, 161, 30, 25, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) DrawRectangle(195 + 54, 161, 30, 25, RED);

            // Draw buttons: left-right back buttons
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) DrawCircle(239, 82, 20, RED);
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) DrawCircle(557, 82, 20, RED);

            // Draw axis: left joystick
            Color leftGamepadColor = BLACK;
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_THUMB)) leftGamepadColor = RED;
            DrawCircle(319, 255, 35, leftGamepadColor);
            DrawCircle(319, 255, 31, LIGHTGRAY);
            DrawCircle(319 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) * 20),
                255 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) * 20), 25, leftGamepadColor);

            // Draw axis: right joystick
            Color rightGamepadColor = BLACK;
            if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_THUMB)) rightGamepadColor = RED;
            DrawCircle(475, 255, 35, BLACK);
            DrawCircle(475, 255, 31, LIGHTGRAY);
            DrawCircle(475 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) * 20),
                255 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) * 20), 25, rightGamepadColor);

            // Draw axis: left-right triggers
            DrawRectangle(169, 48, 15, 70, GRAY);
            DrawRectangle(611, 48, 15, 70, GRAY);
            DrawRectangle(169, 48, 15, (int)(((1 - GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER)) / 2) * 70), RED);
            DrawRectangle(611, 48, 15, (int)(((1 - GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER)) / 2) * 70), RED);
        }
        else
        {
            DrawText("- GENERIC GAMEPAD -", 280, 180, 20, GRAY);

            // TODO: Draw generic gamepad
        }

        DrawText(TextFormat("DETECTED AXIS [%i]:", GetGamepadAxisCount(0)), 10, 50, 10, MAROON);

        for (int i = 0; i < GetGamepadAxisCount(0); i++)
        {
            DrawText(TextFormat("AXIS %i: %.02f", i, GetGamepadAxisMovement(0, i)), 20, 70 + 20 * i, 10, DARKGRAY);
        }

        if (GetGamepadButtonPressed() != GAMEPAD_BUTTON_UNKNOWN) DrawText(TextFormat("DETECTED BUTTON: %i", GetGamepadButtonPressed()), 10, 430, 10, RED);
        else DrawText("DETECTED BUTTON: NONE", 10, 430, 10, GRAY);
    }
    else
    {
        DrawText(TextFormat("GP%d: NOT DETECTED", gamepad), 10, 10, 10, GRAY);

        //DrawTexture(texXboxPad, 0, 0, LIGHTGRAY);
    }
}