#include "Gameplay.h"
#include "Endscreen.h"


[[gsl::suppress(f.6)]]
Play_screen::Play_screen() :
	actor(),
	camera_controller{actor.position}
{



}

std::unique_ptr<State> Play_screen::Update()
{
	if (IsKeyReleased(KEY_Q))
	{
		return std::make_unique<End_screen>();
	}

	const Gamepad gamepad(0);
	camera_controller.Update();
	camera_controller.Update_zoom();

	//insect.update(gamepad);

	return nullptr;
}

void Play_screen::Render() const noexcept
{

	//Vector3 forward =
	//	Vector3Normalize(
	//		Vector3Subtract(
	//			camera_controller.target,
	//			camera_controller.position));

	//Vector3 right =
	//	Vector3Normalize(
	//		Vector3CrossProduct(
	//			forward,
	//			camera_controller.up));



	//Vector3 up =
	//	Vector3Normalize(
	//		Vector3CrossProduct(
	//			right,
	//			forward));
	camera_controller.Begin_3D();

	DrawGrid(20, 10.0f);

	actor.Draw(camera_controller.camera);

	camera_controller.End_3D();
}

