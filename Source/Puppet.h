#pragma once
#include "Segment.h"
#include "Eye.h"
#include <rlgl.h>
 
constexpr size_t NUM_SLICES = 16;
constexpr float VOXEL_SIZE = 1.0f;

struct Point
{
	Vector3 position;
	Color color;
};

class Point_volume
{
private:
	std::vector<Point> points;
public:
	void Load_slices(const std::vector<std::string>& files,	float voxel_size = 1.0f,	uint8_t alpha_threshold = 10)
	{
		points.clear();

		for (size_t z = 0; z < files.size(); ++z)
		{
			const Image image = LoadImage(files[z].c_str());

			Color* pixels = LoadImageColors(image);

			if (not pixels)
				return;

			for (int y = 0; y < image.height; ++y)
			{
				for (int x = 0; x < image.width; ++x)
				{
					const Color c =	pixels[y * image.width + x];

					if (c.a < alpha_threshold)
						continue;

					Point p
					{
						x * voxel_size,
						y * voxel_size,
						static_cast<float>(z) * voxel_size
					};

					p.color = c;

					points.push_back(p);
				}
			}

			UnloadImageColors(pixels);
			UnloadImage(image);
		}
	}

	[[nodiscard]]
	const std::vector<Point>& Points() const noexcept
	{
		return points;
	}
};

class PointCloudMesh
{
public:
	~PointCloudMesh()
	{
		Destroy();
	}

	void Upload(const std::vector<Point>& points)
	{
		Destroy();

		m_mesh = {};
		m_mesh.vertexCount = static_cast<int>(points.size());
		m_mesh.triangleCount = 0;

		m_mesh.vertices =
			static_cast<float*>(
				MemAlloc(static_cast<int>(points.size()) * 3 * sizeof(float)));

		m_mesh.colors =
			static_cast<unsigned char*>(
				MemAlloc(narrow_cast<int>(points.size()) * 4));

		for (size_t i = 0; i < points.size(); ++i)
		{
			auto* v = &m_mesh.vertices[i * 3];

			v[0] = points[i].position.x;
			v[1] = points[i].position.y;
			v[2] = points[i].position.z;

			auto* c = &m_mesh.colors[i * 4];

			c[0] = points[i].color.r;
			c[1] = points[i].color.g;
			c[2] = points[i].color.b;
			c[3] = points[i].color.a;
		}

		UploadMesh(&m_mesh, false);

		m_uploaded = true;
	}

	void Destroy()
	{
		if (!m_uploaded)
			return;

		UnloadMesh(m_mesh);

		m_mesh = {};
		m_uploaded = false;
	}

	[[nodiscard]]
	Mesh& GetMesh()
	{
		return m_mesh;
	}

private:
	Mesh m_mesh{};
	bool m_uploaded = false;
};


class PointCloudRenderer
{
private:
	Shader m_shader;
	Image im = GenImageColor(1, 1, WHITE);
	Texture tex = LoadTextureFromImage(im);
public:
	explicit PointCloudRenderer(const Shader& shader)
		: m_shader(shader)
	{
	}

	void Draw(const std::vector<Point>& points, const Camera3D& camera) const noexcept
	{
		

		for (const auto& p : points)
		{
			DrawBillboard(
				camera,
				tex,
				p.position,
				VOXEL_SIZE,
				p.color);
		}
	}
};


class Actor
{
private:
	Point_volume point_volume;
	PointCloudRenderer renderer;
public:

	Vector3 position{ Vector3Zero() };

	Actor(): renderer(LoadShader("shaders/points.vs", "shaders/points.fs"))
	{
		Load_slices();
	}

	void Load_slices()
	{
		point_volume.Load_slices(
			{
			"assets/slices/0.png",
			"assets/slices/1.png",
			"assets/slices/2.png",
			"assets/slices/3.png",
			"assets/slices/4.png"
			}, VOXEL_SIZE);
	};

	void Draw(const Camera& camera) const noexcept
	{
		renderer.Draw(point_volume.Points(), camera);
	}

};
//class Insect
//{
//protected:
//	std::vector<vec2> CARDIOID;
//	Circle head;
//	float rotation;
//
//
//public:
//	Insect(vec2 position):
//		CARDIOID(epicycloid({ {0.0f,0.0f}, 1.0f }, 1, 64)),
//		head({position, 20.0f}),
//		rotation(0.0f)
//	{
//
//	}
//
//
//
//	virtual void draw(Color _color) const noexcept
//	{
//		constexpr float rotational_offset = 0.5f * PI;
//		std::vector<vec2> drawable = transform_shape(CARDIOID, head.center, rotation + rotational_offset, half_of(head.radius));
//		DrawTriangleFan(drawable.data(), narrow_cast<int>(drawable.size()), _color);
//		//DrawCircleV(head.center, head.radius, _color);
//	}
//};
//
//class Player : Insect
//{
//
//public:
//
//	Player(vec2 position) :
//		Insect(position)
//	{
//
//	}
//
//	void update(Gamepad gamepad)
//	{
//		if (gamepad.B)
//		{
//			rotation = 90.0f;
//		}
//
//	}
//
//	void draw(Color _color) const noexcept override
//	{
//		Insect::draw(_color);
//	}
//
//};


class Face : public Segment
{
	std::vector<Eye> eyes;

public:

	Face(const std::vector<Vector2>& _shape, const std::vector<Eye>& _eyes, const float& natural_frequency, const float& damping_ratio, const Transform2D& _transform) :
		Segment(_shape, natural_frequency, damping_ratio, _transform),
		eyes(_eyes)
	{}

	void update(const Segment::Input& _segment_input, const Eye::Input& _eye_input)
	{
		for (auto& eye : eyes)
		{
			eye.update(_eye_input);
		}
		Segment::update(_segment_input);
	}

	void draw(Color _color) const noexcept
	{
		Segment::draw(_color);
		for (auto& eye : eyes)
		{
			eye.draw(_color, world_point(eye.local_position()), rotation.get_value(), scale.get_value());
		}
	}
};

