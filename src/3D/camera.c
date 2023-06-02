#include "3D/camera.h"

Camera make_camera(float zoom, float aspect) {
    Camera result;
    result.perspective = make_perspective(zoom, aspect, 0.1, 100);
    result.view = make_view((Vec3){0}, (Vec3){{1,0,0}});
    return result;
}

Mat4 camera_mat(Camera* cam) {
    return mat4_mul(cam->perspective.mat, cam->view.mat);
}


Vec3 camera_to_world(Camera* cam, Vec3 v) {
    Vec4 v4 = vec4_transform(vec4_from_vec3(v), mat4_inverse(camera_mat(cam)));
    return vec3_from_vec4(v4);
}

Vec3 world_to_camera(Camera* cam, Vec3 v) {
    Vec4 v4 = vec4_transform(vec4_from_vec3(v), camera_mat(cam));
    return vec3_from_vec4(v4);
}