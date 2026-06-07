#include "Camera_controller.h"

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raymath.h"
#pragma warning(pop)

#include "Utilities.h"

Camera_controller::Camera_controller(Vector3& _target)
    : target(_target)
{
    camera.position = { target.x, camera_distance, camera_distance };
    camera.target = Vector3{ target };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 55.0f;
    camera.projection = CAMERA_CUSTOM;
}

void Camera_controller::Update()
{
    Mouse_drag_orbit();
    Mouse_scroll_zoom();

    const Vector2 target_angle = camera_angle;
    const float   target_distance = camera_distance;
    const Vector3 target_pos
    {
        target.x + target_distance * cosf(target_angle.y) * sinf(target_angle.x),
        target.y + target_distance * sinf(target_angle.y),
        target.z + target_distance * cosf(target_angle.y) * cosf(target_angle.x)
    };


    {
        camera.position = target_pos;
        camera.target = target;
    }
}

void Camera_controller::Update_zoom()
{
    Mouse_scroll_zoom();
    const Vector2 target_angle = camera_angle;
    const float   target_distance = camera_distance;
    const Vector3 target_pos
    {
        target.x + target_distance * cosf(target_angle.y) * sinf(target_angle.x),
        target.y + target_distance * sinf(target_angle.y),
        target.z + target_distance * cosf(target_angle.y) * cosf(target_angle.x)
    };

    camera.position = target_pos;
    camera.target = target;
}

void Camera_controller::Set_projection(CameraProjection projection)
{
    camera.projection = projection;

}

void Camera_controller::Begin_3D()const noexcept
{
    BeginMode3D(camera);

}

void Camera_controller::End_3D()const noexcept
{
    EndMode3D();

}

void Camera_controller::Orthographic_zoom()
{

}

void Camera_controller::Mouse_drag_orbit()
{
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        const Vector2 delta = GetMouseDelta();

        camera_angle.x -= delta.x * 0.01f;
        camera_angle.y += delta.y * 0.01f;
    }
    smooth = false;

}

void Camera_controller::Mouse_scroll_zoom()
{
    const float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        camera_distance -= wheel * 1.5f;
        camera_distance = Clamp(camera_distance, 2.0f, 40.0f);
    }
    smooth = false;

}

void Camera_controller::Set_top_down()
{
    camera.position = { target.x, target.y + camera_distance, target.z };
    camera.target = target;
    camera.up = { 0.0f, 0.0f, -1.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    smooth = true;
}

void Camera_controller::Set_birds_eye()
{
    camera.position = { target.x, camera_distance, camera_distance };
    camera.target = Vector3{ target };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 55.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    smooth = true;
}

void Camera_controller::Set_orbit()
{
}



void Camera_controller::Set_target(Vector3& _target) noexcept
{
    target = _target;
}



