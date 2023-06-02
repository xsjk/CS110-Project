#include "3D/object.h"
#include "3D/camera.h"
#include "display.h"
#include "defines.h"


void drawPoint3D(Point3D point, Color color) {
    point = world_to_camera(point);
    int x = (point.x + 1) * (LCD_W / 2);
    int y = (point.y + 1) * (LCD_H / 2);
    int z = (point.z + 1) * (LCD_H / 2);
    if (x < 0 || x >= LCD_W || y < 0 || y >= LCD_H) {
        return;
    }
    // Depth depth = ((point.z - 0.5) * 2) * DEPTH_MAX;
    // Depth last_depth = zbuffer[y * LCD_W + x];
    // if (depth < last_depth) {
    //     zbuffer[y * LCD_W + x] = depth;
    //     framebuffer[y * LCD_W + x] = color;
    // }
}


void drawLine3D(Line3D line, Color color) {
    line.p1 = world_to_camera(line.p1);
    line.p2 = world_to_camera(line.p2);
    int x1 = (line.p1.x + 1) * (LCD_W / 2);
    int y1 = (line.p1.y + 1) * (LCD_H / 2);
    int x2 = (line.p2.x + 1) * (LCD_W / 2);
    int y2 = (line.p2.y + 1) * (LCD_H / 2);

    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int n = dx + dy - 1;
    float d = 1.0 / n;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (true) {
        drawPoint3D((Point3D) {{x1, y1, line.p1.z + (line.p2.z - line.p1.z) * (x1 - x2) / (x1 - x2)}}, color);
        if (x1 == x2 && y1 == y2) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 < dy) { err += dx; y1 += sy; }
    }

}

void drawCube(Cube cube, Color color) {
    Point3D p1 = cube.p1;
    Point3D p2 = cube.p2;
    Point3D p3 = (Point3D) {{p1.x, p1.y, p2.z}};
    Point3D p4 = (Point3D) {{p1.x, p2.y, p1.z}};
    Point3D p5 = (Point3D) {{p2.x, p1.y, p1.z}};
    Point3D p6 = (Point3D) {{p1.x, p2.y, p2.z}};
    Point3D p7 = (Point3D) {{p2.x, p1.y, p2.z}};
    Point3D p8 = (Point3D) {{p2.x, p2.y, p1.z}};

    drawLine3D((Line3D){p1, p2}, color);
    drawLine3D((Line3D){p1, p3}, color);
    drawLine3D((Line3D){p1, p4}, color);
    drawLine3D((Line3D){p2, p5}, color);
    drawLine3D((Line3D){p2, p7}, color);
    drawLine3D((Line3D){p3, p5}, color);
    drawLine3D((Line3D){p3, p6}, color);
    drawLine3D((Line3D){p4, p6}, color);
    drawLine3D((Line3D){p4, p7}, color);
    drawLine3D((Line3D){p5, p8}, color);
    drawLine3D((Line3D){p6, p8}, color);
    drawLine3D((Line3D){p7, p8}, color);

}


