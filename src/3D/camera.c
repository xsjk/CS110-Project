#include "3D/camera.h"
#include "display.h"

Camera camera;

void set_camera(float zoom) {
    camera.perspective = make_perspective(zoom, (LCD_W/LCD_H), 0.1, 100);
    camera.view = make_view((Vec3){0}, (Vec3){{1,0,0}});
    camera.mat = mat4_mul(camera.perspective.mat, camera.view.mat);
}

void set_view(Vec3 eye, Vec3 front) {
    camera.view = make_view(eye, front);
    camera.mat = mat4_mul(camera.perspective.mat, camera.view.mat);
}

void set_perspective(Perspective perspective) {
    camera.perspective = perspective;
    camera.mat = mat4_mul(camera.perspective.mat, camera.view.mat);
}

Vec3 camera_to_world(Vec3 v) {
    return mat4_transform(v, mat4_inverse(camera.mat));
}

Vec3 world_to_camera(Vec3 v) {
    return mat4_transform(v, camera.mat);
}


void camera_init(void) {
    set_camera(1);
    Vec3 dir = {{0,2,-9}};
    set_view((Vec3){{10,0,15}}, dir);
}