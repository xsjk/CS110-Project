#pragma once

#include "3D/linag.h"

typedef struct {
    float yaw, pitch, roll;
    Mat3 mat;
} Rotation;

Rotation make_rotation(float yaw, float pitch, float roll);

typedef struct {
    Vec3 displacement, scale;
    Rotation rotation;
} Affine;

Affine make_affine(Vec3 displacement, Rotation rotation, Vec3 scale);


typedef struct {
  float yaw, pitch;
  Vec3 eye, front;
  // Vec3 up is always (0, 0, 1)
  Mat4 mat;
} View;

View make_view(Vec3 eye, Vec3 front);


typedef struct {
  float fov, aspect, near, far;
  Mat4 mat;
} Perspective;

Perspective make_perspective(float fov, float aspect, float near, float far);

