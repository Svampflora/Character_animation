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
			const Vector2 eye_input = { GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X), GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) };
			eye_1.update({ GetScreenWidthF() * 0.5f, GetScreenHeightF() * 0.5f }, eye_input);
		}
	}
	return nullptr;
}

[[gsl::suppress(f.6)]]
Play_screen::Play_screen() : 
	eye_1({GetScreenWidthF() * 0.5f, GetScreenHeightF() * 0.5f}, GetScreenWidthF() * 0.1f)
{
	
}

void Play_screen::Render() const noexcept
{
	eye_1.draw();
}

