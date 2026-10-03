#pragma once

#include <iostream>
#include "common.h"

class vec3 {
public:
    double e[3];

    vec3();
    vec3(double e0, double e1, double e2);
    vec3(const vec3& other);

    double x() const;
    double y() const;
    double z() const;

    vec3& operator=(const vec3& other);
    bool operator==(const vec3& other) const;
    bool operator!=(const vec3& other) const;

    void zero();
    vec3 operator-() const;

    double operator[](int i) const;
    double& operator[](int i);

    vec3 operator+(const vec3& other) const;
    vec3 operator-(const vec3& other) const;
    vec3 operator*(const vec3& other) const;
    vec3 operator*(double s) const;
    vec3 operator/(double s) const;

    vec3& operator+=(const vec3& s);
    vec3& operator-=(const vec3& s);
    vec3& operator*=(double s);
    vec3& operator/=(double s);

    double lengthSquared() const;
    double length() const;
    void normalize();

    static vec3 random() {
        return vec3(randomDouble(), randomDouble(), randomDouble());
    }

    static vec3 random(double min, double max) {
        return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }

    bool nearZero() const {
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }
};

using point3 = vec3;

std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 operator*(double k, const vec3& v);
double dot(const vec3& u, const vec3& v);
vec3 crossProduct(const vec3& u, const vec3& v);
vec3 unitVector(const vec3& v);
vec3 randomUnitVector();
vec3 randomOnHemisphere(const vec3& normal);
vec3 reflect(const vec3& v, const vec3& n);