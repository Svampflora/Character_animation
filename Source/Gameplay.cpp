#include "Gameplay.h"
#include "Endscreen.h"


[[gsl::suppress(f.6)]]
Play_screen::Play_screen() :
	position({ GetScreenWidthF() * 0.5f, GetScreenHeightF() * 0.5f }),
	face(),
	legs()
	
{
	std::vector<Vector2> cardioid = epicycloid({ {0.0f,0.0f}, 1.0f}, 2, 64);
	cardioid = transform_shape(cardioid, { 0.0f,0.0f }, 1.5f * PI, GetScreenWidthF() * 0.1f);
	const Eye left({ -GetScreenWidthF() * 0.05f, 0.0f }, GetScreenWidthF() * 0.05f);
	const Eye right({ GetScreenWidthF() * 0.05f, 0.0f }, GetScreenWidthF() * 0.05f);
	std::vector<Eye> eyes{ left, right };
	Face a_face(cardioid, eyes, 10.0f, 0.7f, Transform2D{ position });
	face.push_back(a_face);

	std::vector<Segment> segs;
	segs.reserve(3);
	for (int i = 0; i < 3; i++)
	{
		const Transform2D transform{ position + Vector2{0.0f, GetScreenHeightF() * 0.1f * i}, PI * 0.3f, GetScreenHeightF() * 0.1f };
		Segment seg { {}, 10.0f, 0.7f, transform };
		segs.emplace_back(seg);
	}
	legs.push_back(Leg(segs));

}

std::unique_ptr<State> Play_screen::Update()
{
	if (IsKeyReleased(KEY_Q))
	{
		return std::make_unique<End_screen>();
	}

	const GamePad gamepad(0);

	position = Vector2Add(position, gamepad.right_stick * 5);
	float rotation = 0.0f;
	float scale = 1.0f;
	if (gamepad.B)
	{
		rotation = 90.0f;
	}
	if (gamepad.Y)
	{
		scale = 2.0f;
	}

	face.begin()->update(Segment::Input{position, to_radians(rotation), scale}, Eye::Input{ gamepad.left_stick, gamepad.A});
	legs.begin()->update(GetMousePosition());
	//legs.begin()->update({GetScreenWidthF(), GetScreenHeightF()});
	return nullptr;
}

void Play_screen::Render() const noexcept
{
	//face.begin()->draw(RED);
	legs.begin()->draw();
}

