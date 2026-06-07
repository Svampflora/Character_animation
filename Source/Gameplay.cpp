#include "Gameplay.h"
#include "Endscreen.h"


[[gsl::suppress(f.6)]]
Play_screen::Play_screen() :

	camera{},
	point_volume(),
	mesh(),
	renderer(LoadShader("shaders/points.vs", "shaders/points.fs"))
{

	camera.position = { 10.0f, 10.0f, 15.0f };
	camera.target = { 0.0f, 0.0f,  0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	point_volume.load_slices({
	"assets/slices/0.png",
	"assets/slices/1.png",
	"assets/slices/2.png",
	"assets/slices/3.png",
	"assets/slices/4.png"
		}, VOXEL_SIZE);
}

std::unique_ptr<State> Play_screen::Update()
{
	if (IsKeyReleased(KEY_Q))
	{
		return std::make_unique<End_screen>();
	}

	const Gamepad gamepad(0);

	//insect.update(gamepad);

	return nullptr;
}

void Play_screen::Render() const noexcept
{

	Vector3 forward =
		Vector3Normalize(
			Vector3Subtract(
				camera.target,
				camera.position));

	Vector3 right =
		Vector3Normalize(
			Vector3CrossProduct(
				forward,
				camera.up));



	Vector3 up =
		Vector3Normalize(
			Vector3CrossProduct(
				right,
				forward));

	BeginMode3D(camera);

	DrawGrid(20, 10.0f);


	renderer.Draw(point_volume.Points(), camera);

	EndMode3D();
}

