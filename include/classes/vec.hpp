#pragma once

template <typename T>
struct Vec2 {
    T x, y;

    friend Vec2 operator+(const Vec2& lhs, const Vec2& rhs) {
        return Vec2 { .x = lhs.x + rhs.x, .y = lhs.y + rhs.y };
    }

    friend Vec2 operator-(const Vec2& lhs, const Vec2& rhs) {
        return Vec2 { .x = lhs.x - rhs.x, .y = lhs.y - rhs.y };
    }

    friend Vec2 operator*(const Vec2& lhs, const Vec2& rhs) {
        return Vec2 { .x = lhs.x * rhs.x, .y = lhs.y * rhs.y };
    }

    friend Vec2 operator/(const Vec2& lhs, const Vec2& rhs) {
        return Vec2 { .x = lhs.x / rhs.x, .y = lhs.y / rhs.y };
    }

    void operator+=(const Vec2& other) {
        this->x += other.x;
    }

    void operator-=(const Vec2& other) {
        this->x -= other.x;
        this->y -= other.y;
    }

    void operator*=(const Vec2& other) {
        this->x *= other.x;
        this->y *= other.y;
    }

    void operator/=(const Vec2& other) {
        this->x /= other.x;
        this->y /= other.y;
    }
};

template <typename T>
struct Vec3 {
    T x, y, z;

    friend Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
        return Vec3 { .x = lhs.x + rhs.x, .y = lhs.y + rhs.y, .z = lhs.z + rhs.z };
    }

    friend Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
        return Vec3 { .x = lhs.x - rhs.x, .y = lhs.y - rhs.y, .z = lhs.z - rhs.z };
    }

    friend Vec3 operator*(const Vec3& lhs, const Vec3& rhs) {
        return Vec3 { .x = lhs.x * rhs.x, .y = lhs.y * rhs.y, .z = lhs.z * rhs.z };
    }

    friend Vec3 operator/(const Vec3& lhs, const Vec3& rhs) {
        return Vec3 { .x = lhs.x / rhs.x, .y = lhs.y / rhs.y, .z = lhs.z / rhs.z };
    }

    void operator+=(const Vec3& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
    }

    void operator-=(const Vec3& other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
    }

    void operator*=(const Vec3& other) {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
    }

    void operator/=(const Vec3& other) {
        this->x /= other.x;
        this->y /= other.y;
        this->z /= other.z;
    }
};

template <typename T>
struct Vec4 {
    T x, y, z, w;

    friend Vec4 operator+(const Vec4& lhs, const Vec4& rhs) {
        return Vec4 {
            .x = lhs.x + rhs.x, .y = lhs.y + rhs.y,
            .z = lhs.z + rhs.z, .w = lhs.w + rhs.w,
        };
    }

    friend Vec4 operator-(const Vec4& lhs, const Vec4& rhs) {
        return Vec4 {
            .x = lhs.x - rhs.x, .y = lhs.y - rhs.y,
            .z = lhs.z - rhs.z, .w = lhs.w - rhs.w,
        };
    }

    friend Vec4 operator*(const Vec4& lhs, const Vec4& rhs) {
        return Vec4 {
            .x = lhs.x * rhs.x, .y = lhs.y * rhs.y,
            .z = lhs.z * rhs.z, .w = lhs.w * rhs.w,
        };
    }

    friend Vec4 operator/(const Vec4& lhs, const Vec4& rhs) {
        return Vec4 {
            .x = lhs.x / rhs.x, .y = lhs.y / rhs.y,
            .z = lhs.z / rhs.z, .w = lhs.w / rhs.w,
        };
    }

    void operator+=(const Vec4& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        this->w += other.w;
    }

    void operator-=(const Vec4& other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        this->w -= other.w;
    }

    void operator*=(const Vec4& other) {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        this->w *= other.w;
    }

    void operator/=(const Vec4& other) {
        this->x /= other.x;
        this->y /= other.y;
        this->z /= other.z;
        this->w /= other.w;
    }
};

using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;

using Vec3i = Vec3<int>;
using Vec3u = Vec3<unsigned int>;
using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;

using Vec4i = Vec4<int>;
using Vec4u = Vec4<unsigned int>;
using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;
