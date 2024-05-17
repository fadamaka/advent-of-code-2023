///////////////////////////////////////////////////////////////////////////////
// Vectors.h
// =========
// 2D/3D/4D vectors
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2007-02-14
// UPDATED: 2020-06-29
//
// Copyright (C) 2007-2020 Song Ho Ahn
///////////////////////////////////////////////////////////////////////////////

#ifndef VECTORS_H_DEF
#define VECTORS_H_DEF

#include <cmath>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// 2D vector
///////////////////////////////////////////////////////////////////////////////
struct Vector2 {
    long double x;
    long double y;

    // ctors
    Vector2() : x(0), y(0){};
    Vector2(long double x, long double y) : x(x), y(y){};

    // utils functions
    Vector2& set(long double x, long double y);
    long double length() const;                           //
    long double distance(const Vector2& vec) const;       // distance between two vectors
    Vector2& normalize();                                 //
    long double dot(const Vector2& vec) const;            // dot product
    bool equal(const Vector2& vec, long double e) const;  // compare with epsilon

    // operators
    Vector2 operator-() const;                         // unary operator (negate)
    Vector2 operator+(const Vector2& rhs) const;       // add rhs
    Vector2 operator-(const Vector2& rhs) const;       // subtract rhs
    Vector2& operator+=(const Vector2& rhs);           // add rhs and update this object
    Vector2& operator-=(const Vector2& rhs);           // subtract rhs and update this object
    Vector2 operator*(const long double scale) const;  // scale
    Vector2 operator*(const Vector2& rhs) const;       // multiply each element
    Vector2& operator*=(const long double scale);      // scale and update this object
    Vector2& operator*=(const Vector2& rhs);           // multiply each element and update this object
    Vector2 operator/(const long double scale) const;  // inverse scale
    Vector2& operator/=(const long double scale);      // scale and update this object
    bool operator==(const Vector2& rhs) const;         // exact compare, no epsilon
    bool operator!=(const Vector2& rhs) const;         // exact compare, no epsilon
    bool operator<(const Vector2& rhs) const;          // comparison for sort
    long double operator[](int index) const;           // subscript operator v[0], v[1]
    long double& operator[](int index);                // subscript operator v[0], v[1]

    friend Vector2 operator*(const long double a, const Vector2 vec);
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);
};

///////////////////////////////////////////////////////////////////////////////
// 3D vector
///////////////////////////////////////////////////////////////////////////////
struct Vector3 {
    long double x;
    long double y;
    long double z;

    // ctors
    Vector3() : x(0), y(0), z(0){};
    Vector3(long double x, long double y, long double z) : x(x), y(y), z(z){};

    // utils functions
    Vector3& set(long double x, long double y, long double z);
    long double length() const;                           //
    long double distance(const Vector3& vec) const;       // distance between two vectors
    long double angle(const Vector3& vec) const;          // angle between two vectors
    Vector3& normalize();                                 //
    long double dot(const Vector3& vec) const;            // dot product
    Vector3 cross(const Vector3& vec) const;              // cross product
    bool equal(const Vector3& vec, long double e) const;  // compare with epsilon

    // operators
    Vector3 operator-() const;                         // unary operator (negate)
    Vector3 operator+(const Vector3& rhs) const;       // add rhs
    Vector3 operator-(const Vector3& rhs) const;       // subtract rhs
    Vector3& operator+=(const Vector3& rhs);           // add rhs and update this object
    Vector3& operator-=(const Vector3& rhs);           // subtract rhs and update this object
    Vector3 operator*(const long double scale) const;  // scale
    Vector3 operator*(const Vector3& rhs) const;       // multiplay each element
    Vector3& operator*=(const long double scale);      // scale and update this object
    Vector3& operator*=(const Vector3& rhs);           // product each element and update this object
    Vector3 operator/(const long double scale) const;  // inverse scale
    Vector3& operator/=(const long double scale);      // scale and update this object
    bool operator==(const Vector3& rhs) const;         // exact compare, no epsilon
    bool operator!=(const Vector3& rhs) const;         // exact compare, no epsilon
    bool operator<(const Vector3& rhs) const;          // comparison for sort
    long double operator[](int index) const;           // subscript operator v[0], v[1]
    long double& operator[](int index);                // subscript operator v[0], v[1]

    friend Vector3 operator*(const long double a, const Vector3 vec);
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);
};

///////////////////////////////////////////////////////////////////////////////
// 4D vector
///////////////////////////////////////////////////////////////////////////////
struct Vector4 {
    long double x;
    long double y;
    long double z;
    long double w;

    // ctors
    Vector4() : x(0), y(0), z(0), w(0){};
    Vector4(long double x, long double y, long double z, long double w) : x(x), y(y), z(z), w(w){};

    // utils functions
    Vector4& set(long double x, long double y, long double z, long double w);
    long double length() const;                           //
    long double distance(const Vector4& vec) const;       // distance between two vectors
    Vector4& normalize();                                 //
    long double dot(const Vector4& vec) const;            // dot product
    bool equal(const Vector4& vec, long double e) const;  // compare with epsilon

    // operators
    Vector4 operator-() const;                         // unary operator (negate)
    Vector4 operator+(const Vector4& rhs) const;       // add rhs
    Vector4 operator-(const Vector4& rhs) const;       // subtract rhs
    Vector4& operator+=(const Vector4& rhs);           // add rhs and update this object
    Vector4& operator-=(const Vector4& rhs);           // subtract rhs and update this object
    Vector4 operator*(const long double scale) const;  // scale
    Vector4 operator*(const Vector4& rhs) const;       // multiply each element
    Vector4& operator*=(const long double scale);      // scale and update this object
    Vector4& operator*=(const Vector4& rhs);           // multiply each element and update this object
    Vector4 operator/(const long double scale) const;  // inverse scale
    Vector4& operator/=(const long double scale);      // scale and update this object
    bool operator==(const Vector4& rhs) const;         // exact compare, no epsilon
    bool operator!=(const Vector4& rhs) const;         // exact compare, no epsilon
    bool operator<(const Vector4& rhs) const;          // comparison for sort
    long double operator[](int index) const;           // subscript operator v[0], v[1]
    long double& operator[](int index);                // subscript operator v[0], v[1]

    friend Vector4 operator*(const long double a, const Vector4 vec);
    friend std::ostream& operator<<(std::ostream& os, const Vector4& vec);
};

// fast math routines from Doom3 SDK
inline long double invSqrt(long double x) {
    long double xhalf = 0.5f * x;
    int i = *(int*)&x;               // get bits for long doubleing value
    i = 0x5f3759df - (i >> 1);       // gives initial guess
    x = *(long double*)&i;           // convert bits back to long double
    x = x * (1.5f - xhalf * x * x);  // Newton step
    return x;
}

///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector2
///////////////////////////////////////////////////////////////////////////////
inline Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

inline Vector2 Vector2::operator+(const Vector2& rhs) const {
    return Vector2(x + rhs.x, y + rhs.y);
}

inline Vector2 Vector2::operator-(const Vector2& rhs) const {
    return Vector2(x - rhs.x, y - rhs.y);
}

inline Vector2& Vector2::operator+=(const Vector2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

inline Vector2 Vector2::operator*(const long double a) const {
    return Vector2(x * a, y * a);
}

inline Vector2 Vector2::operator*(const Vector2& rhs) const {
    return Vector2(x * rhs.x, y * rhs.y);
}

inline Vector2& Vector2::operator*=(const long double a) {
    x *= a;
    y *= a;
    return *this;
}

inline Vector2& Vector2::operator*=(const Vector2& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
}

inline Vector2 Vector2::operator/(const long double a) const {
    return Vector2(x / a, y / a);
}

inline Vector2& Vector2::operator/=(const long double a) {
    x /= a;
    y /= a;
    return *this;
}

inline bool Vector2::operator==(const Vector2& rhs) const {
    return (x == rhs.x) && (y == rhs.y);
}

inline bool Vector2::operator!=(const Vector2& rhs) const {
    return (x != rhs.x) || (y != rhs.y);
}

inline bool Vector2::operator<(const Vector2& rhs) const {
    if (x < rhs.x) return true;
    if (x > rhs.x) return false;
    if (y < rhs.y) return true;
    if (y > rhs.y) return false;
    return false;
}

inline long double Vector2::operator[](int index) const {
    return (&x)[index];
}

inline long double& Vector2::operator[](int index) {
    return (&x)[index];
}

inline Vector2& Vector2::set(long double x, long double y) {
    this->x = x;
    this->y = y;
    return *this;
}

inline long double Vector2::length() const {
    return sqrtf(x * x + y * y);
}

inline long double Vector2::distance(const Vector2& vec) const {
    return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
}

inline Vector2& Vector2::normalize() {
    //@@const long double EPSILON = 0.000001f;
    long double xxyy = x * x + y * y;
    //@@if(xxyy < EPSILON)
    //@@    return *this;

    // long double invLength = invSqrt(xxyy);
    long double invLength = 1.0f / sqrtf(xxyy);
    x *= invLength;
    y *= invLength;
    return *this;
}

inline long double Vector2::dot(const Vector2& rhs) const {
    return (x * rhs.x + y * rhs.y);
}

inline bool Vector2::equal(const Vector2& rhs, long double epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon;
}

inline Vector2 operator*(const long double a, const Vector2 vec) {
    return Vector2(a * vec.x, a * vec.y);
}

inline std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}
// END OF VECTOR2 /////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector3
///////////////////////////////////////////////////////////////////////////////
inline Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::operator+(const Vector3& rhs) const {
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

inline Vector3 Vector3::operator-(const Vector3& rhs) const {
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

inline Vector3& Vector3::operator+=(const Vector3& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

inline Vector3 Vector3::operator*(const long double a) const {
    return Vector3(x * a, y * a, z * a);
}

inline Vector3 Vector3::operator*(const Vector3& rhs) const {
    return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

inline Vector3& Vector3::operator*=(const long double a) {
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

inline Vector3& Vector3::operator*=(const Vector3& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

inline Vector3 Vector3::operator/(const long double a) const {
    return Vector3(x / a, y / a, z / a);
}

inline Vector3& Vector3::operator/=(const long double a) {
    x /= a;
    y /= a;
    z /= a;
    return *this;
}

inline bool Vector3::operator==(const Vector3& rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

inline bool Vector3::operator!=(const Vector3& rhs) const {
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}

inline bool Vector3::operator<(const Vector3& rhs) const {
    if (x < rhs.x) return true;
    if (x > rhs.x) return false;
    if (y < rhs.y) return true;
    if (y > rhs.y) return false;
    if (z < rhs.z) return true;
    if (z > rhs.z) return false;
    return false;
}

inline long double Vector3::operator[](int index) const {
    return (&x)[index];
}

inline long double& Vector3::operator[](int index) {
    return (&x)[index];
}

inline Vector3& Vector3::set(long double x, long double y, long double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    return *this;
}

inline long double Vector3::length() const {
    return sqrtf(x * x + y * y + z * z);
}

inline long double Vector3::distance(const Vector3& vec) const {
    return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
}

inline long double Vector3::angle(const Vector3& vec) const {
    // return angle between [0, 180]
    long double l1 = this->length();
    long double l2 = vec.length();
    long double d = this->dot(vec);
    long double angle = acosf(d / (l1 * l2)) / 3.141592f * 180.0f;
    return angle;
}

inline Vector3& Vector3::normalize() {
    //@@const long double EPSILON = 0.000001f;
    long double xxyyzz = x * x + y * y + z * z;
    //@@if(xxyyzz < EPSILON)
    //@@    return *this; // do nothing if it is ~zero vector

    // long double invLength = invSqrt(xxyyzz);
    long double invLength = 1.0f / sqrtf(xxyyzz);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

inline long double Vector3::dot(const Vector3& rhs) const {
    return (x * rhs.x + y * rhs.y + z * rhs.z);
}

inline Vector3 Vector3::cross(const Vector3& rhs) const {
    return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

inline bool Vector3::equal(const Vector3& rhs, long double epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon && fabs(z - rhs.z) < epsilon;
}

inline Vector3 operator*(const long double a, const Vector3 vec) {
    return Vector3(a * vec.x, a * vec.y, a * vec.z);
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
    os << "(" << std::to_string(vec.x) << ", " << std::to_string(vec.y) << ", " << std::to_string(vec.z) << ")";
    return os;
}
// END OF VECTOR3 /////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector4
///////////////////////////////////////////////////////////////////////////////
inline Vector4 Vector4::operator-() const {
    return Vector4(-x, -y, -z, -w);
}

inline Vector4 Vector4::operator+(const Vector4& rhs) const {
    return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

inline Vector4 Vector4::operator-(const Vector4& rhs) const {
    return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

inline Vector4& Vector4::operator+=(const Vector4& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

inline Vector4& Vector4::operator-=(const Vector4& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

inline Vector4 Vector4::operator*(const long double a) const {
    return Vector4(x * a, y * a, z * a, w * a);
}

inline Vector4 Vector4::operator*(const Vector4& rhs) const {
    return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

inline Vector4& Vector4::operator*=(const long double a) {
    x *= a;
    y *= a;
    z *= a;
    w *= a;
    return *this;
}

inline Vector4& Vector4::operator*=(const Vector4& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
}

inline Vector4 Vector4::operator/(const long double a) const {
    return Vector4(x / a, y / a, z / a, w / a);
}

inline Vector4& Vector4::operator/=(const long double a) {
    x /= a;
    y /= a;
    z /= a;
    w /= a;
    return *this;
}

inline bool Vector4::operator==(const Vector4& rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
}

inline bool Vector4::operator!=(const Vector4& rhs) const {
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z) || (w != rhs.w);
}

inline bool Vector4::operator<(const Vector4& rhs) const {
    if (x < rhs.x) return true;
    if (x > rhs.x) return false;
    if (y < rhs.y) return true;
    if (y > rhs.y) return false;
    if (z < rhs.z) return true;
    if (z > rhs.z) return false;
    if (w < rhs.w) return true;
    if (w > rhs.w) return false;
    return false;
}

inline long double Vector4::operator[](int index) const {
    return (&x)[index];
}

inline long double& Vector4::operator[](int index) {
    return (&x)[index];
}

inline Vector4& Vector4::set(long double x, long double y, long double z, long double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    return *this;
}

inline long double Vector4::length() const {
    return sqrtf(x * x + y * y + z * z + w * w);
}

inline long double Vector4::distance(const Vector4& vec) const {
    return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z) + (vec.w - w) * (vec.w - w));
}

inline Vector4& Vector4::normalize() {
    // NOTE: leave w-component untouched
    //@@const long double EPSILON = 0.000001f;
    long double xxyyzz = x * x + y * y + z * z;
    //@@if(xxyyzz < EPSILON)
    //@@    return *this; // do nothing if it is zero vector

    // long double invLength = invSqrt(xxyyzz);
    long double invLength = 1.0f / sqrtf(xxyyzz);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

inline long double Vector4::dot(const Vector4& rhs) const {
    return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
}

inline bool Vector4::equal(const Vector4& rhs, long double epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon &&
           fabs(z - rhs.z) < epsilon && fabs(w - rhs.w) < epsilon;
}

inline Vector4 operator*(const long double a, const Vector4 vec) {
    return Vector4(a * vec.x, a * vec.y, a * vec.z, a * vec.w);
}

inline std::ostream& operator<<(std::ostream& os, const Vector4& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}
// END OF VECTOR4 /////////////////////////////////////////////////////////////

#endif
