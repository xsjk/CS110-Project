#include "3D/transform.h"
#include <math.h>

Rotation make_rotation(float yaw, float pitch, float roll) {
    Rotation result;
    result.yaw = yaw;
    result.pitch = pitch;
    result.roll = roll;
    result.mat = (Mat3) {{
        cosf(pitch) * cosf(yaw), -sinf(pitch) * sinf(roll) * cosf(yaw) - cosf(roll) * sinf(yaw),  sinf(roll) * sinf(yaw) - sinf(pitch) * cosf(roll) * cosf(yaw),
        cosf(pitch) * sinf(yaw),  cosf(roll) * cosf(yaw) - sinf(pitch) * sinf(roll) * sinf(yaw), -sinf(pitch) * cosf(roll) * sinf(yaw) - sinf(roll) * cosf(yaw),
        sinf(pitch),              cosf(pitch) * sinf(roll),                                       cosf(pitch) * cosf(roll)
    }};
    return result;

}

Affine make_affine(Vec3 displacement, Rotation rotation, Vec3 scale) {
    Affine result;
    result.displacement = displacement;
    result.rotation = rotation;
    result.scale = scale;
    return result;
}

View make_view(Vec3 eye, Vec3 front) {
    View result;
    Vec3 f = normalize(front);
    Vec3 s = normalize((Vec3){{f.y, - f.x, 0}});
    Vec3 u = cross(s, f);
    result.mat = (Mat4) {{
         s.x,  s.y,  s.z, -dot(s, eye),
         u.x,  u.y,  u.z, -dot(u, eye),
        -f.x, -f.y, -f.z,  dot(f, eye),
           0,    0,    0,            1
    }};
    return result;
}


Perspective make_perspective(float fov, float aspect, float near, float far) {
    float tanHalfFovy = tanf(fov / 2);
    Perspective result;
    result.fov = fov;
    result.aspect = aspect;
    result.near = near;
    result.far = far;
    result.mat = (Mat4){0};
    result.mat.m[0][0] = 1.f / (aspect * tanHalfFovy);
    result.mat.m[1][1] = 1.f / (tanHalfFovy);
    result.mat.m[2][2] = -(far + near) / (far - near);
    result.mat.m[2][3] = -1.f;
    result.mat.m[3][2] = -(2 * far * near) / (far - near);
    return result;
}

