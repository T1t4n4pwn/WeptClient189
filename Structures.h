#pragma once
#include <iostream>

class Vector2 {
public:
    float X, Y;


    Vector2(float x, float y) {
        X = x;
        Y = y;
    }
    Vector2 operator - (const Vector2& rhs) const { return Vector2(X - rhs.X, Y - rhs.Y); }
    Vector2 Invert() const { return Vector2{ -X, -Y }; }
    Vector2& operator*(const Vector2& obj) {
        X *= obj.X;
        Y *= obj.Y;
    }

};

class Vector3 {
public:
    float X, Y, Z;

    Vector3() {
        X = NAN;
        Y = NAN;
        Z = NAN;
    }

    Vector3(float x, float y, float z) {
        X = x;
        Y = y;
        Z = z;
    }
    Vector3 operator-(const Vector3& rhs) const { return Vector3(X - rhs.X, Y - rhs.Y, Z - rhs.Z); }
    Vector3 operator*(const Vector3& rhs) const { return Vector3(X * rhs.X, Y * rhs.Y, Z * rhs.Z); }
    Vector3 operator*(const float rhs) const { return Vector3(X * rhs, Y * rhs, Z * rhs); }
    Vector3 operator+(const Vector3& rhs) const { return Vector3(X + rhs.X, Y + rhs.Y, Z + rhs.Z); }

    void printData() {
    
        printf("X: %.2F | Y: %.2F | Z: %.2F\n", X, Y, Z);
    }

};

class Vector4 {
public:
    float X, Y, Z, W;

    Vector4() {
        X = NAN;
        Y = NAN;
        Z = NAN;
        W = NAN;
    }

    Vector4(float x, float y, float z, float w) {
        X = x;
        Y = y;
        Z = z;
        W = w;
    }

    Vector4 operator*(const Vector4& obj) {
        Vector4 ret(X *= obj.X, Y *= obj.Y, Z *= obj.Z, W *= obj.W);
        return ret;
    }

    Vector4& operator=(const Vector4& obj) {
        
        X = obj.X;
        Y = obj.Y;
        Z = obj.Z;
        W = obj.W;

        return *this;
    }

};

class Matrix {
public:

    float Data[4][4];

    Matrix() {
        memset(Data, 0, sizeof(Data));
    }

    Matrix(float* data) {
        memcpy(Data, data, 64);
    }

    void parseMatrix(float* data) {
        memcpy(Data, data, 64);
    }

    void printData() {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++) {
                printf("%.2f ", Data[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
    }
};
