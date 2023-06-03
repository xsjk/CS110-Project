#include "3D/display.h"
#include "3D/camera.h"
#include "display.h"
#include "defines.h"
#include "math.h"

void drawPoint3D(Point3D point, Color color) {
    point = world_to_camera(point);
    int x = (point.x + 1) * (LCD_W / 2);
    int y = (-point.y + 1) * (LCD_H / 2);
    // int z = (point.z + 1) * (LCD_H / 2);
    if (x < 0 || x >= LCD_W || y < 0 || y >= LCD_H) {
        return;
    }
    /* It should consider depth buffer but we don't have big enought RAM */
    // Depth depth = ((point.z - 0.5) * 2) * DEPTH_MAX;
    // Depth last_depth = zbuffer[y * LCD_W + x];
    // if (depth < last_depth) {
    //     zbuffer[y * LCD_W + x] = depth;
    //     framebuffer[y * LCD_W + x] = color;
    // }
    framebuffer[y * LCD_W + x] = color;
}


void drawLine3D(Line3D line, Color color) {
    line.p1 = world_to_camera(line.p1);
    line.p2 = world_to_camera(line.p2);
    int x1 = (line.p1.x + 1) * (LCD_W / 2);
    int y1 = (-line.p1.y + 1) * (LCD_H / 2);
    int x2 = (line.p2.x + 1) * (LCD_W / 2);
    int y2 = (-line.p2.y + 1) * (LCD_H / 2);
    drawLine(x1, y1, x2, y2, color);
}

void drawRectangle3D(Rectangle3D rect, Color color) {
    Point3D p1 = rect.p1;
    Point3D p2 = rect.p2;
    Point3D p3 = {{p1.x, p2.y, p1.z}};
    Point3D p4 = {{p2.x, p1.y, p1.z}};
    drawLine3D((Line3D) {p1, p3}, color);
    drawLine3D((Line3D) {p3, p2}, color);
    drawLine3D((Line3D) {p2, p4}, color);
    drawLine3D((Line3D) {p4, p1}, color);
}

void fillRectangle3D(Rectangle3D rect, Color color) {
    Point3D p1 = rect.p1;
    Point3D p2 = rect.p2;
    Point3D p3 = {{p1.x, p2.y, p1.z}};
    Point3D p4 = {{p2.x, p1.y, p1.z}};
    p1 = world_to_camera(p1);
    p2 = world_to_camera(p2);
    p3 = world_to_camera(p3);
    p4 = world_to_camera(p4);
    fillTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    fillTriangle(p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
}


void drawTriangle3D(Triangle3D triangle, Color color) {
    drawLine3D((Line3D) {triangle.p1, triangle.p2}, color);
    drawLine3D((Line3D) {triangle.p2, triangle.p3}, color);
    drawLine3D((Line3D) {triangle.p3, triangle.p1}, color);
}


void drawCircle3D(Circle3D circle, Color color) {
    Point3D p = circle.p;
    float r = circle.r;
    int n = 10;
    for (int i = 0; i < n; i++) {
        float theta1 = i * 2 * M_PI / n;
        float theta2 = (i + 1) * 2 * M_PI / n;
        Point3D p1 = {{p.x + r * cosf(theta1), p.y + r * sinf(theta1), p.z}};
        Point3D p2 = {{p.x + r * cosf(theta2), p.y + r * sinf(theta2), p.z}};
        drawLine3D((Line3D) {p1, p2}, color);
    }
}

void drawSphere(Sphere sphere, Color color) {
    Point3D p = sphere.p;
    float r = sphere.r;
    int n = 10;
    int m = 10;
    for (int i = 0; i < n; i++) {
        float theta1 = i * M_PI / n;
        float theta2 = (i + 1) * M_PI / n;
        for (int j = 0; j < m; j++) {
            float phi1 = j * 2 * M_PI / m;
            float phi2 = (j + 1) * 2 * M_PI / m;
            Point3D p1 = {{p.x + r * sinf(theta1) * cosf(phi1), p.y + r * sinf(theta1) * sinf(phi1), p.z + r * cosf(theta1)}};
            Point3D p2 = {{p.x + r * sinf(theta1) * cosf(phi2), p.y + r * sinf(theta1) * sinf(phi2), p.z + r * cosf(theta1)}};
            Point3D p3 = {{p.x + r * sinf(theta2) * cosf(phi1), p.y + r * sinf(theta2) * sinf(phi1), p.z + r * cosf(theta2)}};
            Point3D p4 = {{p.x + r * sinf(theta2) * cosf(phi2), p.y + r * sinf(theta2) * sinf(phi2), p.z + r * cosf(theta2)}};
            drawTriangle3D((Triangle3D) {p1, p2, p3}, color);
            drawTriangle3D((Triangle3D) {p2, p3, p4}, color);
        }
    }
}

void drawCylinder(Cylinder cylinder, Color color) {
    Point3D p = cylinder.p;
    float r = cylinder.r;
    float h = cylinder.h;
    int n = 10;
    int m = 10;
    for (int i = 0; i < n; i++) {
        // float theta1 = i * M_PI / n;
        // float theta2 = (i + 1) * M_PI / n;
        for (int j = 0; j < m; j++) {
            float phi1 = j * 2 * M_PI / m;
            float phi2 = (j + 1) * 2 * M_PI / m;
            Point3D p1 = {{p.x + r * cosf(phi1), p.y + r * sinf(phi1), p.z + h / 2}};
            Point3D p2 = {{p.x + r * cosf(phi2), p.y + r * sinf(phi2), p.z + h / 2}};
            Point3D p3 = {{p.x + r * cosf(phi1), p.y + r * sinf(phi1), p.z - h / 2}};
            Point3D p4 = {{p.x + r * cosf(phi2), p.y + r * sinf(phi2), p.z - h / 2}};
            drawTriangle3D((Triangle3D) {p1, p2, p3}, color);
            drawTriangle3D((Triangle3D) {p2, p3, p4}, color);
        }
    }
    drawCircle3D((Circle3D) {{{p.x, p.y, p.z + h / 2}}, r}, color);
    drawCircle3D((Circle3D) {{{p.x, p.y, p.z - h / 2}}, r}, color);
}


void drawCone(Cone cone, Color color) {
    Point3D p = cone.p;
    float r = cone.r;
    float h = cone.h;
    Point3D p1 = {{p.x, p.y, p.z + h}};
    int n = 10;
    int m = 10;
    for (int i = 0; i < n; i++) {
        float theta1 = i * M_PI / n;
        float theta2 = (i + 1) * M_PI / n;
        for (int j = 0; j < m; j++) {
            float phi1 = j * 2 * M_PI / m;
            float phi2 = (j + 1) * 2 * M_PI / m;
            Point3D p2 = {{p.x + r * sinf(theta1) * cosf(phi1), p.y + r * sinf(theta1) * sinf(phi1), p.z}};
            Point3D p3 = {{p.x + r * sinf(theta1) * cosf(phi2), p.y + r * sinf(theta1) * sinf(phi2), p.z}};
            Point3D p4 = {{p.x + r * sinf(theta2) * cosf(phi1), p.y + r * sinf(theta2) * sinf(phi1), p.z}};
            Point3D p5 = {{p.x + r * sinf(theta2) * cosf(phi2), p.y + r * sinf(theta2) * sinf(phi2), p.z}};
            drawTriangle3D((Triangle3D) {p1, p2, p3}, color);
            drawTriangle3D((Triangle3D) {p1, p3, p4}, color);
            drawTriangle3D((Triangle3D) {p1, p4, p5}, color);
        }
    }
}



void drawCube(Cube cube, Color color) {
    Point3D p1 = cube.p1;
    Point3D p2 = cube.p2;
    Point3D p3 = {{p1.x, p1.y, p2.z}};
    Point3D p4 = {{p1.x, p2.y, p1.z}};
    Point3D p5 = {{p2.x, p1.y, p1.z}};
    Point3D p6 = {{p1.x, p2.y, p2.z}};
    Point3D p7 = {{p2.x, p1.y, p2.z}};
    Point3D p8 = {{p2.x, p2.y, p1.z}};

    drawLine3D((Line3D) {p1, p3}, color);
    drawLine3D((Line3D) {p1, p4}, color);
    drawLine3D((Line3D) {p1, p5}, color);
    drawLine3D((Line3D) {p2, p6}, color);
    drawLine3D((Line3D) {p2, p7}, color);
    drawLine3D((Line3D) {p2, p8}, color);
    drawLine3D((Line3D) {p3, p6}, color);
    drawLine3D((Line3D) {p3, p7}, color);
    drawLine3D((Line3D) {p4, p6}, color);
    drawLine3D((Line3D) {p4, p8}, color);
    drawLine3D((Line3D) {p5, p7}, color);
    drawLine3D((Line3D) {p5, p8}, color);
}



void drawTetrahedron(Tetrahedron tetrahedron, Color color) {
    Point3D p1 = tetrahedron.p1;
    Point3D p2 = tetrahedron.p2;
    Point3D p3 = tetrahedron.p3;
    Point3D p4 = tetrahedron.p4;

    drawLine3D((Line3D) {p1, p2}, color);
    drawLine3D((Line3D) {p1, p3}, color);
    drawLine3D((Line3D) {p1, p4}, color);
    drawLine3D((Line3D) {p2, p3}, color);
    drawLine3D((Line3D) {p2, p4}, color);
    drawLine3D((Line3D) {p3, p4}, color);
}


void drawPyramid(Pyramid pyramid, Color color) {
    Point3D p1 = pyramid.p1;
    Point3D p2 = pyramid.p2;
    Point3D p3 = pyramid.p3;
    Point3D p4 = pyramid.p4;
    Point3D p5 = pyramid.p5;

    drawLine3D((Line3D) {p1, p2}, color);
    drawLine3D((Line3D) {p1, p3}, color);
    drawLine3D((Line3D) {p1, p4}, color);
    drawLine3D((Line3D) {p1, p5}, color);
    drawLine3D((Line3D) {p2, p3}, color);
    drawLine3D((Line3D) {p3, p4}, color);
    drawLine3D((Line3D) {p4, p5}, color);
    drawLine3D((Line3D) {p5, p2}, color);
}



void drawBlock3D(int x, int y, Color color) {
    drawCube((Cube) {{{x, y, 0}}, {{x + 1, y + 1, 1}}}, color);
}


void drawAxes3D(float length) {
    drawLine3D((Line3D) {{{0, 0, 0}}, {{length, 0, 0}}}, RED);
    drawLine3D((Line3D) {{{0, 0, 0}}, {{0, length, 0}}}, GREEN);
    drawLine3D((Line3D) {{{0, 0, 0}}, {{0, 0, length}}}, BLUE);
}


