#pragma once

#include "3D/transform.h"

typedef struct {
    Perspective perspective;
    View view;
} Camera;


Camera make_camera(float zoom, float aspect);
Mat4 camera_mat(Camera* cam);

Vec3 camera_to_world(Camera* cam, Vec3 v);
Vec3 world_to_camera(Camera* cam, Vec3 v);
