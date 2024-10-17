#include "Gameplay.h"
#include "Endscreen.h"

std::unique_ptr<State> Play_screen::Update()
{
	if (IsKeyReleased(KEY_Q))
	{
		return std::make_unique<End_screen>();
	}
	int gamepad = 0;
	//raylib_example(gamepad);
	if (IsGamepadAvailable(gamepad))
	{
		DrawText(TextFormat("GP%d: %s", gamepad, GetGamepadName(gamepad)), 10, 10, 10, PINK);

		if (TextIsEqual(GetGamepadName(gamepad), XBOX360_LEGACY_NAME_ID) || TextIsEqual(GetGamepadName(gamepad), XBOX360_NAME_ID))
		{
			const Vector2 right_stick = { GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X), GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) };
			const Vector2 left_stick = { GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X), GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) };
			const bool A = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
			const bool B = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
			const bool Y = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP);

			position = Vector2Add(position, right_stick);
			eye_1.update({ GetScreenWidthF() * 0.5f, GetScreenHeightF() * 0.5f }, left_stick, A);
			float rotation = 0.0f;
			float scale = 1.0f;
			if (B)
			{
				rotation = 90.0f;
			}
			if (Y)
			{
				scale = 2.0f;
			}

			segment.update(position, to_radians(rotation), scale);
		}
	}
	return nullptr;
}

[[gsl::suppress(f.6)]]
Play_screen::Play_screen() :
	eye_1({ GetScreenWidthF() * 0.5f, GetScreenHeightF() * 0.5f }, GetScreenWidthF() * 0.1f),
	segment(10.0f, 0.7f, { GetScreenWidthF() * 0.5f, GetScreenHeightF() * 0.5f }),
	position({ GetScreenWidthF() * 0.5f, GetScreenHeightF() * 0.5f })
{
	
}

void Play_screen::Render() const noexcept
{
	eye_1.draw();
	segment.draw(RED);
}

