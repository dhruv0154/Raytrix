#include "math/vec3.h"

#include <cmath>

vec3::vec3() : e{0.0, 0.0, 0.0} {}

vec3::vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

vec3::vec3(const vec3& other) : e{other.e[0], other.e[1], other.e[2]} {}

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

vec3& vec3::operator=(const vec3& other) {
    e[0] = other.e[0];
    e[1] = other.e[1];
    e[2] = other.e[2];
    return *this;
}

bool vec3::operator==(const vec3& other) const {
    return e[0] == other.e[0] && e[1] == other.e[1] && e[2] == other.e[2];
}

bool vec3::operator!=(const vec3& other) const {
    return !(*this == other);
}

void vec3::zero() {
    e[0] = e[1] = e[2] = 0.0;
}

vec3 vec3::operator-() const {
    return vec3(-e[0], -e[1], -e[2]);
}

double vec3::operator[](int i) const { return e[i]; }
double& vec3::operator[](int i) { return e[i]; }

vec3 vec3::operator+(const vec3& other) const {
    return vec3(e[0] + other.e[0], e[1] + other.e[1], e[2] + other.e[2]);
}

vec3 vec3::operator-(const vec3& other) const {
    return vec3(e[0] - other.e[0], e[1] - other.e[1], e[2] - other.e[2]);
}

vec3 vec3::operator*(const vec3& other) const {
    return vec3(e[0] * other.e[0], e[1] * other.e[1], e[2] * other.e[2]);
}

vec3 vec3::operator*(double s) const {
    return vec3(e[0] * s, e[1] * s, e[2] * s);
}

vec3 vec3::operator/(double s) const {
    double oneOverS = 1.0 / s;
    return vec3(e[0] * oneOverS, e[1] * oneOverS, e[2] * oneOverS);
}

vec3& vec3::operator+=(const vec3& s) {
    e[0] += s.e[0];
    e[1] += s.e[1];
    e[2] += s.e[2];
    return *this;
}

vec3& vec3::operator-=(const vec3& s) {
    e[0] -= s.e[0];
    e[1] -= s.e[1];
    e[2] -= s.e[2];
    return *this;
}

vec3& vec3::operator*=(double s) {
    e[0] *= s;
    e[1] *= s;
    e[2] *= s;
    return *this;
}

vec3& vec3::operator/=(double s) {
    double oneOverS = 1.0 / s;
    e[0] *= oneOverS;
    e[1] *= oneOverS;
    e[2] *= oneOverS;
    return *this;
}

double vec3::lengthSquared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

double vec3::length() const {
    return std::sqrt(lengthSquared());
}

void vec3::normalize() {
    double magSq = lengthSquared();
    if (magSq > 0.0) {
        double oneOverMag = 1.0 / std::sqrt(magSq);
        e[0] *= oneOverMag;
        e[1] *= oneOverMag;
        e[2] *= oneOverMag;
    }
}

std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

vec3 operator*(double k, const vec3& v) {
    return vec3(k * v.e[0], k * v.e[1], k * v.e[2]);
}

double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

vec3 crossProduct(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

vec3 unitVector(const vec3& v) {
    return v / v.length();
}

vec3 randomUnitVector() {
    while (true) {
        auto p = vec3::random(-1, 1);
        auto lenSq = p.lengthSquared();
        // to avoid division by zero we take values greater than 10^-160
        if (1e-160 < lenSq && lenSq <= 1)
            return p / sqrt(lenSq);
    }
}

vec3 randomOnHemisphere(const vec3& normal) {
    vec3 onUnitSphere = randomUnitVector();
    if (dot(onUnitSphere, normal) > 0.0)
        return onUnitSphere;
    else
        return -onUnitSphere;
}