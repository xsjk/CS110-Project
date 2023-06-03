#pragma once

#include "3D/transform.h"

typedef struct {
    Perspective perspective;
    View view;
    Mat4 mat;
} Camera;

extern Camera camera;

/**
 * @brief Set the zoom and aspect of the camera
 * @param zoom the zoom of the camera
 */
void set_camera(float zoom);


/**
 * @brief Set the view of the camera
 * @param eye the position of the camera
 * @param front the direction the camera is facing
*/
void set_view(Vec3 eye, Vec3 front);


/**
 * @brief Transform a vector from camera space to world space
 * @param v 
 * @return Vec3 
 */
Vec3 camera_to_world(Vec3 v);

/**
 * @brief Transform a vector from world space to camera space
 * @param v 
 * @return Vec3
 */
Vec3 world_to_camera(Vec3 v);


/**
 * @brief Initialize the camera with default values
 */
void camera_init(void);
