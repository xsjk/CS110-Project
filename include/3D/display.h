#pragma once

#include "3D/object.h"


/**
 * @brief draw a 3D point
 * @param p the point to draw
 * @param color the color of the point
 */
void drawPoint3D(Point3D p, Color color);


/**
 * @brief draw a 3D line
 * @param line the line to draw
 * @param color the color of the line
 */
void drawLine3D(Line3D line, Color color);

/**
 * @brief draw a 3D rectangle
 * @param rect the rectangle to draw
 * @param color the color of the rectangle
 * @note the rectangle is assumed to be parallel to xOy
*/
void drawRectangle3D(Rectangle3D rect, Color color);

/**
 * @brief fill a 3D rectangle
 * @param rect the rectangle to be filled
 * @param color the color to fill
 * @note the rectangle is assumed to be parallel to xOy
*/
void fillRectangle3D(Rectangle3D rect, Color color);

/**
 * @brief draw a 3D triangle
 * @param triangle the triangle to draw
 * @param color the color of the triangle
 */
void drawTriangle3D(Triangle3D triangle, Color color);


/**
 * @brief draw a 3D circle
 * @param circle the circle to draw
 * @param color the color of the circle
 */
void drawCircle3D(Circle3D circle, Color color);


/**
 * @brief draw a 3D sphere
 * @param sphere the sphere to draw
 * @param color the color of the sphere
 */
void drawSphere(Sphere sphere, Color color);


/**
 * @brief draw a 3D cylinder
 * @param cylinder the cylinder to draw
 * @param color the color of the cylinder
 */
void drawCylinder(Cylinder cylinder, Color color);


/**
 * @brief draw a 3D cone
 * @param cone the cone to draw
 * @param color the color of the cone
 */
void drawCone(Cone cone, Color color);


/**
 * @brief draw a 3D cube
 * @param cube the cube to draw
 * @param color the color of the cube
 */
void drawCube(Cube cube, Color color);


/**
 * @brief draw a 3D tetrahedron
 * @param tetrahedron the tetrahedron to draw
 * @param color the color of the tetrahedron
 */
void drawTetrahedron(Tetrahedron tetrahedron, Color color);


/**
 * @brief draw a 3D pyramid
 * @param pyramid the pyramid to draw
 * @param color the color of the pyramid
 */
void drawPyramid(Pyramid pyramid, Color color);


/**
 * @brief draw a 3D block
 * @param x the x position of corner of the block
 * @param y the y position of corner of the block
*/
void drawBlock3D(int i, int j, Color color);


/**
 * @brief draw the axes of the 3D space
 * @param length the length of the axes
 */
void drawAxes3D(float length);