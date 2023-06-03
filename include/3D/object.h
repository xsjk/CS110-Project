#pragma once

#include "3D/linag.h"
#include "color.h"


typedef Vec3 Point3D;


typedef struct {
    Point3D p1, p2;
} Line3D;

typedef struct {
    Point3D p1, p2, p3;
} Triangle3D;

typedef struct {
    Point3D p1, p2;
} Rectangle3D;

typedef struct {
    Point3D p;
    float r;
} Circle3D;

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

typedef struct {
    Point3D p1;
    Point3D p2;
    Point3D p3;
    Point3D p4;
} Tetrahedron;

typedef struct {
    Point3D p1;
    Point3D p2;
    Point3D p3;
    Point3D p4;
    Point3D p5;
} Pyramid;