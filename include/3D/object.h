#pragma once

#include "3D/linag.h"
#include "color.h"


typedef Vec3 Point3D;

/**
 * @brief draw a 3D point
 * @param p the point to draw
 * @param color the color of the point
 */
void drawPoint3D(Point3D p, Color color);

typedef struct {
    Point3D p1, p2, p3;
} Triangle3D;

typedef struct {
    Point3D p1, p2;
} Line3D;

/**
 * @brief draw a 3D line
 * @param line the line to draw
 * @param color the color of the line
 */
void drawLine3D(Line3D line, Color color);

typedef struct {
    Point3D p;
    float r;
} Sphere;

typedef struct {
    Point3D p;
    float r;
    float h;
} Cylinder;

typedef struct {
    Point3D p;
    float r;
    float h;
} Cone;

typedef struct {
    Point3D p1;
    Point3D p2;
} Cube;


/**
 * @brief draw a 3D cube
 * @param cube the cube to draw
 * @param color the color of the cube
 */
void drawCube(Cube cube, Color color);
