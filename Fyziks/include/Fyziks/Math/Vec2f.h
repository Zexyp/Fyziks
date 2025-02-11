#pragma once

#include "Fyziks/Api.h"
#include <cmath>

namespace fy {
    class FYZIKS_API Vec2f {
    public:
        float x, y;

        Vec2f() : x(0.0f), y(0.0f) {}

        Vec2f(float x, float y) : x(x), y(y) {}

        Vec2f operator-() const {
            return {-this->x, -this->y};
        }

        void operator+=(const Vec2f &other) {
            this->x += other.x;
            this->y += other.y;
        }

        void operator-=(const Vec2f &other) {
            this->x -= other.x;
            this->y -= other.y;
        }

        void operator*=(const Vec2f &other) {
            this->x *= other.x;
            this->y *= other.y;
        }

        void operator/=(const Vec2f &other) {
            this->x /= other.x;
            this->y /= other.y;
        }

        float length() {
            return sqrtf(this->x * this->x + this->y * this->y);
        }

        static float dot(const Vec2f &vec1, const Vec2f &vec2) {
            return vec1.x * vec2.x + vec1.y * vec2.y;
        }

        static Vec2f normalize(Vec2f vec) {
            float length = vec.length();

            if (length != 0) {
                vec.x /= length;
                vec.y /= length;
            }

            return vec;
        }

        void normalize() {
            float length = this->length();

            if (length != 0) {
                this->x /= length;
                this->y /= length;
            }
        }

        static float distance(const Vec2f &vec1, const Vec2f &vec2) {
            float dx = vec1.x - vec2.x;
            float dy = vec1.y - vec2.y;
            return sqrtf(dx * dx + dy * dy);
        }
    };

    inline Vec2f operator+(const Vec2f &vec1, const Vec2f &vec2) {
        return {vec1.x + vec2.x, vec1.y + vec2.y};
    }

    inline Vec2f operator-(const Vec2f &vec1, const Vec2f &vec2) {
        return {vec1.x - vec2.x, vec1.y - vec2.y};
    }

    inline Vec2f operator*(const Vec2f &vec, float scalar) {
        return {vec.x * scalar, vec.y * scalar};
    }

    inline Vec2f operator*(float scalar, const Vec2f &vec) {
        return {vec.x * scalar, vec.y * scalar};
    }
}
