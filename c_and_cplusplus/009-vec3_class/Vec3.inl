/************************************************************************
* CREATED TIME: 2016-9-22 17:26:44
* LAST MODIFIED TIME: 2016-9-22 17:26:44
* DESCRIPTION: 三维向量类
* BY: 357688981@qq.com
************************************************************************/

#include "Vec3.h"


inline void Vec3::set(float xx, float yy, float zz) {
    this->x = xx;
    this->y = yy;
    this->z = zz;
}

inline void Vec3::set(const float* array) {
    // MY_ASSERT(array);
    x = array[0];
    y = array[1];
    z = array[2];
}

inline void Vec3::set(const Vec3& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

inline void Vec3::set(const Vec3& p1, const Vec3& p2) {
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
}

inline void Vec3::setZero() {
    x = y = z = 0.0f;
}

inline void Vec3::add(const Vec3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

inline void Vec3::add(float xx, float yy, float zz)
{
    x += xx;
    y += yy;
    z += zz;
}

inline void Vec3::subtract(const Vec3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}
inline void Vec3::negate()
{
    x = -x;
    y = -y;
    z = -z;
}
inline void Vec3::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

inline const Vec3 Vec3::operator+(const Vec3& v) const
{
    Vec3 result(*this);
    result.add(v);
    return result;
}

inline Vec3& Vec3::operator+=(const Vec3& v)
{
    add(v);
    return *this;
}

inline const Vec3 Vec3::operator-(const Vec3& v) const
{
    Vec3 result(*this);
    result.subtract(v);
    return result;
}

inline Vec3& Vec3::operator-=(const Vec3& v)
{
    subtract(v);
    return *this;
}

inline const Vec3 Vec3::operator-() const
{
    Vec3 result(*this);
    result.negate();
    return result;
}

inline const Vec3 Vec3::operator*(float s) const
{
    Vec3 result(*this);
    result.scale(s);
    return result;
}

inline Vec3& Vec3::operator*=(float s)
{
    scale(s);
    return *this;
}

inline const Vec3 Vec3::operator/(const float s) const
{
    return Vec3(this->x / s, this->y / s, this->z / s);
}

inline float Vec3::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

inline float Vec3::lengthSquared() const
{
    return (x * x + y * y + z * z);
}