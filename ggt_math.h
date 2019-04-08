#ifndef GGT_MATH_H
#define GGT_MATH_H

#include <math.h>

#ifndef M_PI
#define M_PI 3.141592653589793238f
#endif

//
// Vec2, Vec2i
//
union Vec2;
union Vec2i;
union Vec2 {
    struct { float x, y; };
    float axis[2];
    inline Vec2 operator+(const Vec2 b) const { return Vec2(x + b.x, y + b.y); }
    inline Vec2 operator-(const Vec2 b) const { return Vec2(x - b.x, y - b.y); }
    inline Vec2 operator*(const Vec2 b) const { return Vec2(x * b.x, y * b.y); }
    inline Vec2 operator/(const Vec2 b) const { return Vec2(x / b.x, y / b.y); }
    inline Vec2 operator+(const float b) const { return Vec2(x + b, y + b); }
    inline Vec2 operator-(const float b) const { return Vec2(x - b, y - b); }
    inline Vec2 operator*(const float b) const { return Vec2(x * b, y * b); }
    inline Vec2 operator/(const float b) const { return Vec2(x / b, y / b); }
    inline Vec2& operator+=(const Vec2 b){ *this = Vec2(x + b.x, y + b.y); return *this; }
    inline Vec2& operator-=(const Vec2 b){ *this = Vec2(x - b.x, y - b.y); return *this; }
    inline Vec2& operator*=(const Vec2 b){ *this = Vec2(x * b.x, y * b.y); return *this; }
    inline Vec2& operator/=(const Vec2 b){ *this = Vec2(x / b.x, y / b.y); return *this; }
    inline Vec2& operator+=(const float b){ *this = Vec2(x + b, y + b); return *this; }
    inline Vec2& operator-=(const float b){ *this = Vec2(x - b, y - b); return *this; }
    inline Vec2& operator*=(const float b){ *this = Vec2(x * b, y * b); return *this; }
    inline Vec2& operator/=(const float b){ *this = Vec2(x / b, y / b); return *this; }
    inline Vec2 operator-() const { return {-x, -y}; }
    inline bool operator!=(const Vec2 u) const { return x != u.x || y != u.y; }
    inline bool operator==(const Vec2 u) const { return x == u.x && y == u.y; }
    inline bool operator<(const Vec2 u) const { return x < u.x && y < u.y; }
    inline bool operator<=(const Vec2 u) const { return x <= u.x && y <= u.y; }
    inline bool operator>(const Vec2 u) const { return x > u.x && y > u.y; }
    inline bool operator>=(const Vec2 u) const { return x >= u.x && y >= u.y; }
    inline Vec2(float o) : x(o), y(o) { }
    inline Vec2(float ox, float oy) : x(ox), y(oy) { }
    inline Vec2() : x(0), y(0) { }
    operator Vec2i();
};
union Vec2i {
    struct { int x, y; };
    int axis[2];
    inline Vec2i operator+(const Vec2i b) const { return Vec2i(x + b.x, y + b.y); }
    inline Vec2i operator-(const Vec2i b) const { return Vec2i(x - b.x, y - b.y); }
    inline Vec2i operator*(const Vec2i b) const { return Vec2i(x * b.x, y * b.y); }
    inline Vec2i operator/(const Vec2i b) const { return Vec2i(x / b.x, y / b.y); }
    inline Vec2i operator+(const int b) const { return Vec2i(x + b, y + b); }
    inline Vec2i operator-(const int b) const { return Vec2i(x - b, y - b); }
    inline Vec2i operator*(const int b) const { return Vec2i(x * b, y * b); }
    inline Vec2i operator/(const int b) const { return Vec2i(x / b, y / b); }
    inline Vec2i& operator+=(const Vec2i b){ *this = Vec2i(x + b.x, y + b.y); return *this; }
    inline Vec2i& operator-=(const Vec2i b){ *this = Vec2i(x - b.x, y - b.y); return *this; }
    inline Vec2i& operator*=(const Vec2i b){ *this = Vec2i(x * b.x, y * b.y); return *this; }
    inline Vec2i& operator/=(const Vec2i b){ *this = Vec2i(x / b.x, y / b.y); return *this; }
    inline Vec2i& operator+=(const int b){ *this = Vec2i(x + b, y + b); return *this; }
    inline Vec2i& operator-=(const int b){ *this = Vec2i(x - b, y - b); return *this; }
    inline Vec2i& operator*=(const int b){ *this = Vec2i(x * b, y * b); return *this; }
    inline Vec2i& operator/=(const int b){ *this = Vec2i(x / b, y / b); return *this; }
    inline Vec2i operator-() const { return {-x, -y}; }
    inline bool operator!=(const Vec2i u) const { return x != u.x || y != u.y; }
    inline bool operator==(const Vec2i u) const { return x == u.x && y == u.y; }
    inline bool operator<(const Vec2i u) const { return x < u.x && y < u.y; }
    inline bool operator<=(const Vec2i u) const { return x <= u.x && y <= u.y; }
    inline bool operator>(const Vec2i u) const { return x > u.x && y > u.y; }
    inline bool operator>=(const Vec2i u) const { return x >= u.x && y >= u.y; }
    inline Vec2i(int o) : x(o), y(o) { }
    inline Vec2i(int ox, int oy) : x(ox), y(oy) { }
    inline Vec2i() : x(0), y(0) { }
    operator Vec2();
};
inline Vec2::operator Vec2i(){ return Vec2i((int)x, (int)y); }
inline Vec2i::operator Vec2(){ return Vec2((float)x, (float)y); }

inline float dot(Vec2 u, Vec2 v){
    return u.x*v.x + u.y*v.y;
}
inline float cross(Vec2 a, Vec2 b){
    return a.x*b.y-a.y*b.x;
}
inline float length_sqr(Vec2 u){
    return u.x*u.x + u.y*u.y;
}
inline float length(Vec2 u){
    return sqrtf(u.x*u.x + u.y*u.y);
}
inline Vec2 normalize(Vec2 u){
    return u/sqrtf(u.x*u.x + u.y*u.y);
}
inline Vec2 operator*(float s, Vec2 v){
    return {s*v.x, s*v.y};
}

inline Vec2 operator*(float k, Vec2i v){
    return {k*v.x, k*v.y};
}
inline Vec2 operator*(Vec2i v, float k){
    return {k*v.x, k*v.y};
}

inline float project_onto(Vec2 p, Vec2 axis){
    return dot(axis, p)/length_sqr(axis);
}
inline float norm1(Vec2 v){
    return (float)(fabs(v.x)+fabs(v.y));
}
inline float norm_inf(Vec2 v){
    float x = (float)fabs(v.x);
    float y = (float)fabs(v.y);
    return fmaxf(x, y);
}
inline Vec2 orthogonal(Vec2 v){
    return Vec2(-v.y, v.x);
}


inline Vec2 floor(Vec2 v){
    return {floorf(v.x), floorf(v.y)};
}
inline Vec2 round(Vec2 v){
    return {roundf(v.x), roundf(v.y)};
}
inline Vec2 ceil(Vec2 v){
    return {ceilf(v.x), ceilf(v.y)};
}


//
// Vec3
//
union Vec3;
union Vec3i;
union Vec3 {
    struct { float x, y, z; };
    float axis[3];
    inline Vec3 operator+(const Vec3 b) const { return Vec3(x + b.x, y + b.y, z + b.z); }
    inline Vec3 operator-(const Vec3 b) const { return Vec3(x - b.x, y - b.y, z - b.z); }
    inline Vec3 operator*(const Vec3 b) const { return Vec3(x * b.x, y * b.y, z * b.z); }
    inline Vec3 operator/(const Vec3 b) const { return Vec3(x / b.x, y / b.y, z / b.z); }
    inline Vec3 operator+(const float b) const { return Vec3(x + b, y + b, z + b); }
    inline Vec3 operator-(const float b) const { return Vec3(x - b, y - b, z - b); }
    inline Vec3 operator*(const float b) const { return Vec3(x * b, y * b, z * b); }
    inline Vec3 operator/(const float b) const { return Vec3(x / b, y / b, z / b); }
    inline Vec3& operator+=(const Vec3 b){ *this = Vec3(x + b.x, y + b.y, z + b.z); return *this; }
    inline Vec3& operator-=(const Vec3 b){ *this = Vec3(x - b.x, y - b.y, z - b.z); return *this; }
    inline Vec3& operator*=(const Vec3 b){ *this = Vec3(x * b.x, y * b.y, z * b.z); return *this; }
    inline Vec3& operator/=(const Vec3 b){ *this = Vec3(x / b.x, y / b.y, z / b.z); return *this; }
    inline Vec3& operator+=(const float b){ *this = Vec3(x + b, y + b, z + b); return *this; }
    inline Vec3& operator-=(const float b){ *this = Vec3(x - b, y - b, z - b); return *this; }
    inline Vec3& operator*=(const float b){ *this = Vec3(x * b, y * b, z * b); return *this; }
    inline Vec3& operator/=(const float b){ *this = Vec3(x / b, y / b, z / b); return *this; }
    inline Vec3 operator-() const { return {-x, -y, -z}; }
    inline bool operator!=(const Vec3 u) const { return x != u.x || y != u.y || z != u.z; }
    inline bool operator==(const Vec3 u) const { return x == u.x && y == u.y && z == u.z; }
    inline bool operator<(const Vec3 u) const { return x < u.x && y < u.y && z < u.z; }
    inline bool operator<=(const Vec3 u) const { return x <= u.x && y <= u.y && z <= u.z; }
    inline bool operator>(const Vec3 u) const { return x > u.x && y > u.y && z > u.z; }
    inline bool operator>=(const Vec3 u) const { return x >= u.x && y >= u.y && z >= u.z; }
    inline Vec3(float o) : x(o), y(o), z(o) { }
    inline Vec3(float ox, float oy, float oz) : x(ox), y(oy), z(oz) { }
    inline Vec3() : x(0), y(0), z(0) { }
    operator Vec3i();
};
union Vec3i {
    struct { int x, y, z; };
    int axis[3];
    inline Vec3i operator+(const Vec3i b) const { return Vec3i(x + b.x, y + b.y, z + b.z); }
    inline Vec3i operator-(const Vec3i b) const { return Vec3i(x - b.x, y - b.y, z - b.z); }
    inline Vec3i operator*(const Vec3i b) const { return Vec3i(x * b.x, y * b.y, z * b.z); }
    inline Vec3i operator/(const Vec3i b) const { return Vec3i(x / b.x, y / b.y, z / b.z); }
    inline Vec3i operator+(const int b) const { return Vec3i(x + b, y + b, z + b); }
    inline Vec3i operator-(const int b) const { return Vec3i(x - b, y - b, z - b); }
    inline Vec3i operator*(const int b) const { return Vec3i(x * b, y * b, z * b); }
    inline Vec3i operator/(const int b) const { return Vec3i(x / b, y / b, z / b); }
    inline Vec3i& operator+=(const Vec3i b){ *this = Vec3i(x + b.x, y + b.y, z + b.z); return *this; }
    inline Vec3i& operator-=(const Vec3i b){ *this = Vec3i(x - b.x, y - b.y, z - b.z); return *this; }
    inline Vec3i& operator*=(const Vec3i b){ *this = Vec3i(x * b.x, y * b.y, z * b.z); return *this; }
    inline Vec3i& operator/=(const Vec3i b){ *this = Vec3i(x / b.x, y / b.y, z / b.z); return *this; }
    inline Vec3i& operator+=(const int b){ *this = Vec3i(x + b, y + b, z + b); return *this; }
    inline Vec3i& operator-=(const int b){ *this = Vec3i(x - b, y - b, z - b); return *this; }
    inline Vec3i& operator*=(const int b){ *this = Vec3i(x * b, y * b, z * b); return *this; }
    inline Vec3i& operator/=(const int b){ *this = Vec3i(x / b, y / b, z / b); return *this; }
    inline Vec3i operator-() const { return {-x, -y, -z}; }
    inline bool operator!=(const Vec3i u) const { return x != u.x || y != u.y || z != u.z; }
    inline bool operator==(const Vec3i u) const { return x == u.x && y == u.y && z == u.z; }
    inline bool operator<(const Vec3i u) const { return x < u.x && y < u.y && z < u.z; }
    inline bool operator<=(const Vec3i u) const { return x <= u.x && y <= u.y && z <= u.z; }
    inline bool operator>(const Vec3i u) const { return x > u.x && y > u.y && z > u.z; }
    inline bool operator>=(const Vec3i u) const { return x >= u.x && y >= u.y && z >= u.z; }
    inline Vec3i(int o) : x(o), y(o), z(o) { }
    inline Vec3i(int ox, int oy, int oz) : x(ox), y(oy), z(oz) { }
    inline Vec3i() : x(0), y(0), z(0) { }
    operator Vec3();
};
inline Vec3::operator Vec3i(){ return Vec3i((int)x, (int)y, (int)z); }
inline Vec3i::operator Vec3(){ return Vec3((float)x, (float)y, (float)z); }

inline Vec3 operator*(const float b, const Vec3 v) {
    return {v.x*b, v.y*b, v.z*b};
}
inline Vec3 operator/(const float b, const Vec3 v) {
    return {v.x/b, v.y/b, v.z/b};
}

inline float dot(Vec3 u, Vec3 v){
    return u.x*v.x + u.y*v.y + u.z*v.z;
}
inline float length_sqr(Vec3 u){
    return u.x*u.x + u.y*u.y + u.z*u.z;
}
inline float length(Vec3 u){
    return sqrtf(u.x*u.x + u.y*u.y + u.z*u.z);
}
inline float norm_inf(Vec3 u){
    return (float)fmaxf((float)fabs(u.x), fmaxf((float)fabs(u.y), (float)fabs(u.z)));
}
inline Vec3 normalize(Vec3 u){
    return u/sqrtf(u.x*u.x + u.y*u.y + u.z*u.z);
}
inline Vec3 cross(Vec3 u, Vec3 v){
    return {
        u.y*v.z-u.z*v.y,
        u.z*v.x-u.x*v.z,
        u.x*v.y-u.y*v.x
    };
}

inline Vec3 lerp(float t, Vec3 u, Vec3 v){
    return u*(1.f-t)+v*t;
}

//
// Vec4
//

union Vec4 {
    struct { float x, y, z, w; };
    float axis[4];
    inline Vec4 operator+(const Vec4 b) const { return Vec4(x + b.x, y + b.y, z + b.z, w + b.w); }
    inline Vec4 operator-(const Vec4 b) const { return Vec4(x - b.x, y - b.y, z - b.z, w - b.w); }
    inline Vec4 operator*(const Vec4 b) const { return Vec4(x * b.x, y * b.y, z * b.z, w * b.w); }
    inline Vec4 operator/(const Vec4 b) const { return Vec4(x / b.x, y / b.y, z / b.z, w / b.w); }
    inline Vec4 operator+(const float b) const { return Vec4(x + b, y + b, z + b, w + b); }
    inline Vec4 operator-(const float b) const { return Vec4(x - b, y - b, z - b, w - b); }
    inline Vec4 operator*(const float b) const { return Vec4(x * b, y * b, z * b, w * b); }
    inline Vec4 operator/(const float b) const { return Vec4(x / b, y / b, z / b, w / b); }
    inline Vec4& operator+=(const Vec4 b){ *this = Vec4(x + b.x, y + b.y, z + b.z, w + b.w); return *this; }
    inline Vec4& operator-=(const Vec4 b){ *this = Vec4(x - b.x, y - b.y, z - b.z, w - b.w); return *this; }
    inline Vec4& operator*=(const Vec4 b){ *this = Vec4(x * b.x, y * b.y, z * b.z, w * b.w); return *this; }
    inline Vec4& operator/=(const Vec4 b){ *this = Vec4(x / b.x, y / b.y, z / b.z, w / b.w); return *this; }
    inline Vec4& operator+=(const float b){ *this = Vec4(x + b, y + b, z + b, w + b); return *this; }
    inline Vec4& operator-=(const float b){ *this = Vec4(x - b, y - b, z - b, w - b); return *this; }
    inline Vec4& operator*=(const float b){ *this = Vec4(x * b, y * b, z * b, w * b); return *this; }
    inline Vec4& operator/=(const float b){ *this = Vec4(x / b, y / b, z / b, w / b); return *this; }
    inline Vec4 operator-() const { return {-x, -y, -z, -w}; }
    inline bool operator!=(const Vec4 u) const { return x != u.x || y != u.y || z != u.z || w != u.w; }
    inline bool operator==(const Vec4 u) const { return x == u.x && y == u.y && z == u.z && w == u.w; }
    inline bool operator<(const Vec4 u) const { return x < u.x && y < u.y && z < u.z && w < u.w; }
    inline bool operator<=(const Vec4 u) const { return x <= u.x && y <= u.y && z <= u.z && w <= u.w; }
    inline bool operator>(const Vec4 u) const { return x > u.x && y > u.y && z > u.z && w > u.w; }
    inline bool operator>=(const Vec4 u) const { return x >= u.x && y >= u.y && z >= u.z && w >= u.w; };
    inline Vec4(float o) : x(o), y(o), z(o), w(o) { }
    inline Vec4(float ox, float oy, float oz, float ow) : x(ox), y(oy), z(oz), w(ow) { }
    inline Vec4() : x(0), y(0), z(0), w(0) { }
};

//
// Matrices
//
struct Mat2{
    float values[2][2];
    
    inline Mat2 operator+(const Mat2& m) const {
        return {
            values[0][0]+m.values[0][0], values[1][0]+m.values[1][0],
            values[0][1]+m.values[0][1], values[1][1]+m.values[1][1]
        };
    }
    inline Mat2 operator-(const Mat2& m) const {
        return {
            values[0][0]-m.values[0][0], values[1][0]-m.values[1][0],
            values[0][1]-m.values[0][1], values[1][1]-m.values[1][1]
        };
    }
    inline Mat2 operator*(const Mat2& m) const {
        return {
            values[0][0]*m.values[0][0]+values[1][0]*m.values[0][1], values[0][0]*m.values[1][0]+values[1][0]*m.values[1][1],
            values[0][1]*m.values[0][0]+values[1][1]*m.values[0][1], values[0][1]*m.values[1][0]+values[1][1]*m.values[1][1]
        };
    }
    
    inline Mat2& operator+=(const Mat2& m) {
        *this = *this+m;
        return *this;
    }
    inline Mat2& operator-=(const Mat2& m) {
        *this = *this-m;
        return *this;
    }
    inline Mat2& operator*=(const Mat2& m) {
        *this = *this*m;
        return *this;
    }
    
    inline Mat2(float b00, float b01, float b10, float b11){
        values[0][0] = b00;
        values[1][0] = b01;
        values[0][1] = b10;
        values[1][1] = b11;
    };
};

inline Vec2 operator*(const Mat2& m, const Vec2& v) {
    return {
        m.values[0][0]*v.x+m.values[1][0]*v.y,
        m.values[0][1]*v.x+m.values[1][1]*v.y
    };
}
inline Vec2 operator*(const Vec2& v, const Mat2& m) {
    return {
        m.values[0][0]*v.x+m.values[0][1]*v.y,
        m.values[1][0]*v.x+m.values[1][1]*v.y
    };
}

/* 3x3 matrices */
struct Mat3{
    float values[3][3];
    
    inline Mat3 operator+(const Mat3& m) const {
        return {
            values[0][0]+m.values[0][0], values[1][0]+m.values[1][0], values[2][0]+m.values[2][0],
            values[0][1]+m.values[0][1], values[1][1]+m.values[1][1], values[2][1]+m.values[2][1],
            values[0][2]+m.values[0][2], values[1][2]+m.values[1][2], values[2][2]+m.values[2][2]
        };
    }
    inline Mat3 operator-(const Mat3& m) const {
        return {
            values[0][0]-m.values[0][0], values[1][0]-m.values[1][0], values[2][0]-m.values[2][0],
            values[0][1]-m.values[0][1], values[1][1]-m.values[1][1], values[2][1]-m.values[2][1],
            values[0][2]-m.values[0][2], values[1][2]-m.values[1][2], values[2][2]-m.values[2][2]
        };
    }
    inline Mat3 operator*(const Mat3& m) const {
        return {
            values[0][0]*m.values[0][0]+values[1][0]*m.values[0][1]+values[2][0]*m.values[0][2],
            values[0][0]*m.values[1][0]+values[1][0]*m.values[1][1]+values[2][0]*m.values[1][2],
            values[0][0]*m.values[2][0]+values[1][0]*m.values[2][1]+values[2][0]*m.values[2][2],
            
            values[0][1]*m.values[0][0]+values[1][1]*m.values[0][1]+values[2][1]*m.values[0][2],
            values[0][1]*m.values[1][0]+values[1][1]*m.values[1][1]+values[2][1]*m.values[1][2],
            values[0][1]*m.values[2][0]+values[1][1]*m.values[2][1]+values[2][1]*m.values[2][2],
            
            values[0][2]*m.values[0][0]+values[1][2]*m.values[0][1]+values[2][2]*m.values[0][2],
            values[0][2]*m.values[1][0]+values[1][2]*m.values[1][1]+values[2][2]*m.values[1][2],
            values[0][2]*m.values[2][0]+values[1][2]*m.values[2][1]+values[2][2]*m.values[2][2],
        };
    }
    
    inline Mat3& operator+=(const Mat3& m) {
        *this = *this+m;
        return *this;
    }
    inline Mat3& operator-=(const Mat3& m) {
        *this = *this-m;
        return *this;
    }
    inline Mat3& operator*=(const Mat3& m) {
        *this = *this*m;
        return *this;
    }
    
    inline bool operator==(const Mat3& m) {
        return
            values[0][0] == m.values[0][0] &&
            values[0][1] == m.values[0][1] &&
            values[0][2] == m.values[0][2] &&
            values[1][0] == m.values[1][0] &&
            values[1][1] == m.values[1][1] &&
            values[1][2] == m.values[1][2] &&
            values[2][0] == m.values[2][0] &&
            values[2][1] == m.values[2][1] &&
            values[2][2] == m.values[2][2];
    }
    inline bool operator!=(const Mat3& m) {
        return
            values[0][0] != m.values[0][0] ||
            values[0][1] != m.values[0][1] ||
            values[0][2] != m.values[0][2] ||
            values[1][0] != m.values[1][0] ||
            values[1][1] != m.values[1][1] ||
            values[1][2] != m.values[1][2] ||
            values[2][0] != m.values[2][0] ||
            values[2][1] != m.values[2][1] ||
            values[2][2] != m.values[2][2];
    }
    
    inline Mat3(float b00, float b01, float b02, float b10, float b11, float b12, float b20, float b21, float b22){
        values[0][0] = b00;
        values[1][0] = b01;
        values[2][0] = b02;
        values[0][1] = b10;
        values[1][1] = b11;
        values[2][1] = b12;
        values[0][2] = b20;
        values[1][2] = b21;
        values[2][2] = b22;
    };
    inline Mat3(){};
};
inline Vec3 operator*(const Mat3& m, const Vec3& v) {
    return {
        m.values[0][0]*v.x+m.values[1][0]*v.y+m.values[2][0]*v.z,
        m.values[0][1]*v.x+m.values[1][1]*v.y+m.values[2][1]*v.z,
        m.values[0][2]*v.x+m.values[1][2]*v.y+m.values[2][2]*v.z
    };
}
inline Vec3 operator*(const Vec3& v, const Mat3& m) {
    return {
        m.values[0][0]*v.x+m.values[0][1]*v.y+m.values[0][2]*v.z,
        m.values[1][0]*v.x+m.values[1][1]*v.y+m.values[1][2]*v.z,
        m.values[2][0]*v.x+m.values[2][1]*v.y+m.values[2][2]*v.z
    };
}
inline float det(const Mat3 M){
    return M.values[0][0]*M.values[1][1]*M.values[2][2] +
        M.values[0][1]*M.values[1][2]*M.values[2][0] +
        M.values[0][2]*M.values[1][0]*M.values[2][1] -
        M.values[0][2]*M.values[1][1]*M.values[2][0] -
        M.values[0][1]*M.values[1][0]*M.values[2][2] -
        M.values[0][0]*M.values[1][2]*M.values[2][1];
}
inline Mat3 inv(const Mat3& M){
    Mat3 I;
    float det = M.values[0][0]*M.values[1][1]*M.values[2][2] +
        M.values[0][1]*M.values[1][2]*M.values[2][0] +
        M.values[0][2]*M.values[1][0]*M.values[2][1] -
        M.values[0][2]*M.values[1][1]*M.values[2][0] -
        M.values[0][1]*M.values[1][0]*M.values[2][2] -
        M.values[0][0]*M.values[1][2]*M.values[2][1];
    
    I.values[0][0] = (M.values[1][1] * M.values[2][2] - M.values[2][1] * M.values[1][2]) / det;
    I.values[0][1] = (M.values[0][2] * M.values[2][1] - M.values[0][1] * M.values[2][2]) / det;
    I.values[0][2] = (M.values[0][1] * M.values[1][2] - M.values[0][2] * M.values[1][1]) / det;
    I.values[1][0] = (M.values[1][2] * M.values[2][0] - M.values[1][0] * M.values[2][2]) / det;
    I.values[1][1] = (M.values[0][0] * M.values[2][2] - M.values[0][2] * M.values[2][0]) / det;
    I.values[1][2] = (M.values[1][0] * M.values[0][2] - M.values[0][0] * M.values[1][2]) / det;
    I.values[2][0] = (M.values[1][0] * M.values[2][1] - M.values[2][0] * M.values[1][1]) / det;
    I.values[2][1] = (M.values[2][0] * M.values[0][1] - M.values[0][0] * M.values[2][1]) / det;
    I.values[2][2] = (M.values[0][0] * M.values[1][1] - M.values[1][0] * M.values[0][1]) / det;
    
    return I;
}

const Mat3 mat3_identity = {
    1.f, 0.f, 0.f,
    0.f, 1.f, 0.f,
    0.f, 0.f, 1.f
};


/* 4x4 matrices */
struct Mat4{
    float values[4][4];
    
    inline Mat4 operator+(const Mat4& m) const {
        return {
            values[0][0]+m.values[0][0], values[1][0]+m.values[1][0], values[2][0]+m.values[2][0], values[3][0]+m.values[3][0],
            values[0][1]+m.values[0][1], values[1][1]+m.values[1][1], values[2][1]+m.values[2][1], values[3][1]+m.values[3][1],
            values[0][2]+m.values[0][2], values[1][2]+m.values[1][2], values[2][2]+m.values[2][2], values[3][2]+m.values[3][2],
            values[0][3]+m.values[0][3], values[1][3]+m.values[1][3], values[2][3]+m.values[2][3], values[3][3]+m.values[3][3],
        };
    }
    inline Mat4 operator-(const Mat4& m) const {
        return {
            values[0][0]-m.values[0][0], values[1][0]-m.values[1][0], values[2][0]-m.values[2][0], values[3][0]-m.values[3][0],
            values[0][1]-m.values[0][1], values[1][1]-m.values[1][1], values[2][1]-m.values[2][1], values[3][1]-m.values[3][1],
            values[0][2]-m.values[0][2], values[1][2]-m.values[1][2], values[2][2]-m.values[2][2], values[3][2]-m.values[3][2],
            values[0][3]-m.values[0][3], values[1][3]-m.values[1][3], values[2][3]-m.values[2][3], values[3][3]-m.values[3][3],
        };
    }
    inline Mat4 operator*(const Mat4& m) const {
        return {
            values[0][0]*m.values[0][0] + values[1][0]*m.values[0][1] + values[2][0]*m.values[0][2] + values[3][0]*m.values[0][3],
            values[0][0]*m.values[1][0] + values[1][0]*m.values[1][1] + values[2][0]*m.values[1][2] + values[3][0]*m.values[1][3],
            values[0][0]*m.values[2][0] + values[1][0]*m.values[2][1] + values[2][0]*m.values[2][2] + values[3][0]*m.values[2][3],
            values[0][0]*m.values[3][0] + values[1][0]*m.values[3][1] + values[2][0]*m.values[3][2] + values[3][0]*m.values[3][3],
            
            values[0][1]*m.values[0][0] + values[1][1]*m.values[0][1] + values[2][1]*m.values[0][2] + values[3][1]*m.values[0][3],
            values[0][1]*m.values[1][0] + values[1][1]*m.values[1][1] + values[2][1]*m.values[1][2] + values[3][1]*m.values[1][3],
            values[0][1]*m.values[2][0] + values[1][1]*m.values[2][1] + values[2][1]*m.values[2][2] + values[3][1]*m.values[2][3],
            values[0][1]*m.values[3][0] + values[1][1]*m.values[3][1] + values[2][1]*m.values[3][2] + values[3][1]*m.values[3][3],
            
            values[0][2]*m.values[0][0] + values[1][2]*m.values[0][1] + values[2][2]*m.values[0][2] + values[3][2]*m.values[0][3],
            values[0][2]*m.values[1][0] + values[1][2]*m.values[1][1] + values[2][2]*m.values[1][2] + values[3][2]*m.values[1][3],
            values[0][2]*m.values[2][0] + values[1][2]*m.values[2][1] + values[2][2]*m.values[2][2] + values[3][2]*m.values[2][3],
            values[0][2]*m.values[3][0] + values[1][2]*m.values[3][1] + values[2][2]*m.values[3][2] + values[3][2]*m.values[3][3],
            
            values[0][3]*m.values[0][0] + values[1][3]*m.values[0][1] + values[2][3]*m.values[0][2] + values[3][3]*m.values[0][3],
            values[0][3]*m.values[1][0] + values[1][3]*m.values[1][1] + values[2][3]*m.values[1][2] + values[3][3]*m.values[1][3],
            values[0][3]*m.values[2][0] + values[1][3]*m.values[2][1] + values[2][3]*m.values[2][2] + values[3][3]*m.values[2][3],
            values[0][3]*m.values[3][0] + values[1][3]*m.values[3][1] + values[2][3]*m.values[3][2] + values[3][3]*m.values[3][3],
        };
    }
    
    inline Mat4& operator+=(const Mat4& m) {
        *this = *this+m;
        return *this;
    }
    inline Mat4& operator-=(const Mat4& m) {
        *this = *this-m;
        return *this;
    }
    inline Mat4& operator*=(const Mat4& m) {
        *this = *this*m;
        return *this;
    }
    
    inline Mat4(float b00, float b01, float b02, float b03, float b10, float b11, float b12, float b13, float b20, float b21, float b22, float b23, float b30, float b31, float b32, float b33){
        values[0][0] = b00;
        values[0][1] = b10;
        values[0][2] = b20;
        values[0][3] = b30;
        values[1][0] = b01;
        values[1][1] = b11;
        values[1][2] = b21;
        values[1][3] = b31;
        values[2][0] = b02;
        values[2][1] = b12;
        values[2][2] = b22;
        values[2][3] = b32;
        values[3][0] = b03;
        values[3][1] = b13;
        values[3][2] = b23;
        values[3][3] = b33;
    };
    
    inline Mat4(){};
};
inline Vec4 operator*(const Mat4& m, const Vec4& v) {
    return {
        m.values[0][0]*v.x+m.values[1][0]*v.y+m.values[2][0]*v.z+m.values[3][0]*v.w,
        m.values[0][1]*v.x+m.values[1][1]*v.y+m.values[2][1]*v.z+m.values[3][1]*v.w,
        m.values[0][2]*v.x+m.values[1][2]*v.y+m.values[2][2]*v.z+m.values[3][2]*v.w,
        m.values[0][3]*v.x+m.values[1][3]*v.y+m.values[2][3]*v.z+m.values[3][3]*v.w,
    };
}
inline Vec4 operator*(const Vec4& v, const Mat4& m) {
    return {
        m.values[0][0]*v.x+m.values[0][1]*v.y+m.values[0][2]*v.z+m.values[0][3]*v.w,
        m.values[1][0]*v.x+m.values[1][1]*v.y+m.values[1][2]*v.z+m.values[1][3]*v.w,
        m.values[2][0]*v.x+m.values[2][1]*v.y+m.values[2][2]*v.z+m.values[2][3]*v.w,
        m.values[3][0]*v.x+m.values[3][1]*v.y+m.values[3][2]*v.z+m.values[3][3]*v.w,
    };
}

const Mat4 mat4_identity = {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f
};
inline Mat4 get_affine_matrix(const Mat3 m){
    return {
        m.values[0][0], m.values[1][0], m.values[2][0], 0.f,
        m.values[0][1], m.values[1][1], m.values[2][1], 0.f,
        m.values[0][2], m.values[1][2], m.values[2][2], 0.f,
        0.f,            0.f,            0.f,            1.f
    };
}
inline Mat3 get_vector_matrix(const Mat4 m){
    return {
        m.values[0][0], m.values[1][0], m.values[2][0],
        m.values[0][1], m.values[1][1], m.values[2][1],
        m.values[0][2], m.values[1][2], m.values[2][2],
    };
}

const Mat4 switch_y_and_z = {
    1.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 1.f
};

inline Mat4 get_perspective_matrix(const float half_pov, const float near_, const float far_){
    float s = cosf(half_pov) / sinf(half_pov);
    float f = -far_/(far_-near_);
    return Mat4(
        s, 0.f, 0.f, 0.f,
        0.f,   s, 0.f, 0.f,
        0.f, 0.f, f, f*near_,
        0.f, 0.f,-1.f, 0.f
        );
}
inline Mat4 get_translation_matrix(const Vec3 v){
    return Mat4(
        1.f, 0.f, 0.f, v.x,
        0.f, 1.f, 0.f, v.y,
        0.f, 0.f, 1.f, v.z,
        0.f, 0.f, 0.f, 1.f
        );
}
inline Mat4 get_scale_matrix(const float x, const float y, const float z){
    return Mat4(
        x, 0.f, 0.f, 0.f,
        0.f,   y, 0.f, 0.f,
        0.f, 0.f,   z, 0.f,
        0.f, 0.f, 0.f, 1.f
        );
}
inline Mat4 get_rotation_matrix_x(const float angle){
    float c = cosf(angle), s = sinf(angle);
    return Mat4(
        1.f, 0.f, 0.f, 0.f,
        0.f, c,  -s,  0.f,
        0.f, s,   c,   0.f,
        0.f, 0.f, 0.f, 1.f
        );
}
inline Mat4 get_rotation_matrix_y(const float angle){
    float c = cosf(angle), s = sinf(angle);
    return Mat4(
        c,   0.f,-s,   0.f,
        0.f, 1.f, 0.f, 0.f,
        s,   0.f, c,   0.f,
        0.f, 0.f, 0.f, 1.f
        );
}
inline Mat4 get_rotation_matrix_z(const float angle){
    float c = cosf(angle), s = sinf(angle);
    return Mat4(
        c,  -s,   0.f, 0.f,
        s,   c,   0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
        );
}

inline void print_matrix(const Mat4 m){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++)
            printf(" %.10e", m.values[j][i]);
        printf("\n");
    }
}
inline void print_matrix(const Mat3 m){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++)
            printf(" %.10e", m.values[j][i]);
        printf("\n");
    }
}


#endif