#pragma once

class vec3 {
public:
    double e[3];

    vec3() : e{0.0, 0.0, 0.0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
    vec3(const vec3& other) : e{other.e[0], other.e[1], other.e[2]} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3& operator=(const vec3& other) {
        e[0] = other.e[0]; 
        e[1] = other.e[1]; 
        e[2] = other.e[2];
        return *this;
    }

    bool operator==(const vec3& other) const {
        return e[0] == other.e[0] && e[1] == other.e[1] && e[2] == other.e[2];
    }

    bool operator!=(const vec3& other) const {
        return !(*this == other);
    }

    void zero() {
        e[0] = e[1] = e[2] = 0.0;
    }

    vec3 operator-() const {
        return vec3(-e[0], -e[1], -e[2]);
    }

    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3 operator+(const vec3& other) const {
        return vec3(e[0] + other.e[0], e[1] + other.e[1], e[2] + other.e[2]);
    }

    vec3 operator-(const vec3& other) const {
        return vec3(e[0] - other.e[0], e[1] - other.e[1], e[2] - other.e[2]);
    }

    vec3 operator*(const vec3& other) const {
        return vec3(e[0] * other.e[0], e[1] * other.e[1], e[2] * other.e[2]);
    }

    vec3 operator*(double s) const {
        return vec3(e[0] * s, e[1] * s, e[2] * s);
    }

    vec3 operator/(double s) const {
        double oneOverS = 1.0 / s;
        return vec3(e[0] * oneOverS, e[1] * oneOverS, e[2] * oneOverS);
    }

    vec3& operator+=(const vec3& s) {
        e[0] += s.e[0]; 
        e[1] += s.e[1]; 
        e[2] += s.e[2];
        return *this;
    }

    vec3& operator-=(const vec3& s) {
        e[0] -= s.e[0]; 
        e[1] -= s.e[1]; 
        e[2] -= s.e[2];
        return *this;
    }

    vec3& operator*=(double s) {
        e[0] *= s; 
        e[1] *= s; 
        e[2] *= s;
        return *this;
    }

    vec3& operator/=(double s) {
        double oneOverS = 1.0 / s;
        e[0] *= oneOverS; 
        e[1] *= oneOverS; 
        e[2] *= oneOverS;
        return *this;
    }

    double lengthSquared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    double length() const {
        return std::sqrt(lengthSquared());
    }

    void normalize() {
        double magSq = lengthSquared();
        if (magSq > 0.0) {
            double oneOverMag = 1.0 / std::sqrt(magSq);
            e[0] *= oneOverMag;
            e[1] *= oneOverMag;
            e[2] *= oneOverMag;
        }
    }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator*(double k, const vec3& v) {
    return vec3(k * v.e[0], k * v.e[1], k * v.e[2]);
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 crossProduct(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unitVector(const vec3& v) {
    return v / v.length();
}