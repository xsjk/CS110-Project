#pragma once

typedef union {
    struct {
        float x, y, z;
    };
    float m[3];
} Vec3;


typedef union {
    struct {
        float x, y, z, w;
    };
    float m[4];
} Vec4;

typedef union {
    struct {
        float x0, y0, z0,
              x1, y1, z1,
              x2, y2, z2;
    };
    float m[3][3];
} Mat3;

typedef union {
    struct {
        float x0, y0, z0, w0,
              x1, y1, z1, w1,
              x2, y2, z2, w2,
              x3, y3, z3, w3;
    };
    float m[4][4];
} Mat4;
               
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_scale(Vec3 a, float b);
Vec3 cross(Vec3 a, Vec3 b);
float dot(Vec3 a, Vec3 b);
float vec3_length(Vec3 a);
Vec3 normalize(Vec3 a);

Mat3 mat3_identity();
Mat3 mat3_transpose(Mat3 m);
Mat3 mat3_scale(Mat3 m, float s);
float mat3_det(Mat3 m);
Mat3 mat3_inverse(Mat3 m);
Mat3 mat3_mul(Mat3 a, Mat3 b);

Vec4 vec4_add(Vec4 a, Vec4 b);
Vec4 vec4_sub(Vec4 a, Vec4 b);
Vec4 vec4_scale(Vec4 a, float b);

Mat4 mat4_identity();
Mat4 mat4_scale(Mat4 m, float s);
float mat4_det(Mat4 m);

Mat4 mat4_inverse(Mat4 m);
Mat4 mat4_mul(Mat4 a, Mat4 b);


Vec3 vec3_from_vec4(Vec4 v);
Vec4 vec4_from_vec3(Vec3 v);

Vec3 mat3_mul_vec3(Mat3 m, Vec3 v);
Vec4 mat4_mul_vec4(Mat4 m, Vec4 v);
Vec3 mat4_transform(Vec3 a, Mat4 m);
